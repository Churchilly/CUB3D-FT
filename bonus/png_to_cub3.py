#!/usr/bin/env python3
"""
PNG to .cub3 converter with white threshold (no dependencies)
Usage: python3 png_to_cub3.py input.png output.cub3 [threshold]
Example: python3 png_to_cub3.py sprite.png sprite.cub3 5
"""

import sys
import struct
import zlib

def read_chunk(f):
    """Read a PNG chunk"""
    length_data = f.read(4)
    if len(length_data) < 4:
        return None, None, None

    length = struct.unpack('>I', length_data)[0]
    chunk_type = f.read(4).decode('ascii')
    chunk_data = f.read(length)
    crc = f.read(4)

    return chunk_type, chunk_data, length

def parse_ihdr(data):
    """Parse IHDR chunk"""
    width, height, bit_depth, color_type, compression, filter_method, interlace = struct.unpack('>IIBBBBB', data)
    return width, height, bit_depth, color_type

def paeth_predictor(a, b, c):
    """Paeth filter predictor"""
    p = a + b - c
    pa = abs(p - a)
    pb = abs(p - b)
    pc = abs(p - c)

    if pa <= pb and pa <= pc:
        return a
    elif pb <= pc:
        return b
    else:
        return c

def unfilter_scanline(filter_type, scanline, prev_scanline, bytes_per_pixel):
    """Unfilter a scanline"""
    result = bytearray(len(scanline))

    for i in range(len(scanline)):
        if filter_type == 0:  # None
            result[i] = scanline[i]
        elif filter_type == 1:  # Sub
            left = result[i - bytes_per_pixel] if i >= bytes_per_pixel else 0
            result[i] = (scanline[i] + left) % 256
        elif filter_type == 2:  # Up
            up = prev_scanline[i] if prev_scanline else 0
            result[i] = (scanline[i] + up) % 256
        elif filter_type == 3:  # Average
            left = result[i - bytes_per_pixel] if i >= bytes_per_pixel else 0
            up = prev_scanline[i] if prev_scanline else 0
            result[i] = (scanline[i] + (left + up) // 2) % 256
        elif filter_type == 4:  # Paeth
            left = result[i - bytes_per_pixel] if i >= bytes_per_pixel else 0
            up = prev_scanline[i] if prev_scanline else 0
            up_left = prev_scanline[i - bytes_per_pixel] if prev_scanline and i >= bytes_per_pixel else 0
            result[i] = (scanline[i] + paeth_predictor(left, up, up_left)) % 256

    return bytes(result)

def decode_image_data(width, height, bit_depth, color_type, idat_data):
    """Decode PNG image data"""
    # Determine bytes per pixel
    if color_type == 6:  # RGBA
        bytes_per_pixel = 4
    elif color_type == 2:  # RGB
        bytes_per_pixel = 3
    elif color_type == 0:  # Grayscale
        bytes_per_pixel = 1
    elif color_type == 4:  # Grayscale + Alpha
        bytes_per_pixel = 2
    else:
        raise ValueError(f"Unsupported color type: {color_type}")

    # Decompress
    decompressed = zlib.decompress(idat_data)

    # Unfilter scanlines
    pixels = []
    stride = width * bytes_per_pixel + 1  # +1 for filter byte
    prev_scanline = None

    for y in range(height):
        offset = y * stride
        filter_type = decompressed[offset]
        scanline = decompressed[offset + 1:offset + stride]

        unfiltered = unfilter_scanline(filter_type, scanline, prev_scanline, bytes_per_pixel)

        # Convert to RGBA
        row = []
        for x in range(width):
            pixel_offset = x * bytes_per_pixel

            if color_type == 6:  # RGBA
                r, g, b, a = unfiltered[pixel_offset:pixel_offset + 4]
            elif color_type == 2:  # RGB
                r, g, b = unfiltered[pixel_offset:pixel_offset + 3]
                a = 255
            elif color_type == 0:  # Grayscale
                gray = unfiltered[pixel_offset]
                r = g = b = gray
                a = 255
            elif color_type == 4:  # Grayscale + Alpha
                gray, a = unfiltered[pixel_offset:pixel_offset + 2]
                r = g = b = gray

            row.append((r, g, b, a))

        pixels.append(row)
        prev_scanline = unfiltered

    return pixels

def is_near_white(r, g, b, threshold):
    """Check if RGB values are within threshold of white"""
    return (255 - r <= threshold and
            255 - g <= threshold and
            255 - b <= threshold)

def convert_png_to_cub3(input_path, output_path, threshold=0):
    """Convert PNG to .cub3 format"""
    try:
        with open(input_path, 'rb') as f:
            # Check PNG signature
            signature = f.read(8)
            if signature != b'\x89PNG\r\n\x1a\n':
                raise ValueError("Not a valid PNG file")

            # Read chunks
            width = height = bit_depth = color_type = None
            idat_data = bytearray()

            while True:
                chunk_type, chunk_data, length = read_chunk(f)
                if chunk_type is None:
                    break

                if chunk_type == 'IHDR':
                    width, height, bit_depth, color_type = parse_ihdr(chunk_data)
                elif chunk_type == 'IDAT':
                    idat_data.extend(chunk_data)
                elif chunk_type == 'IEND':
                    break

            if width is None:
                raise ValueError("Invalid PNG: missing IHDR")

            # Decode pixels
            pixels = decode_image_data(width, height, bit_depth, color_type, bytes(idat_data))

        # Write .cub3 file
        with open(output_path, 'w') as f:
            f.write(f".cub3:{width}:{height}\n")

            for row in pixels:
                row_data = []
                for r, g, b, a in row:
                    # Apply white threshold
                    if is_near_white(r, g, b, threshold):
                        r = g = b = 255

                    hex_color = f"0x{r:02x}{g:02x}{b:02x}{a:02x}"
                    row_data.append(hex_color)

                f.write('.'.join(row_data) + '\n')

        print(f"✓ Converted {input_path} -> {output_path}")
        print(f"  Size: {width}x{height}")
        print(f"  Threshold: {threshold}")

    except FileNotFoundError:
        print(f"Error: File '{input_path}' not found")
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 png_to_cub3.py input.png output.cub3 [threshold]")
        print("Example: python3 png_to_cub3.py sprite.png sprite.cub3 5")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]
    threshold = int(sys.argv[3]) if len(sys.argv) > 3 else 0

    convert_png_to_cub3(input_path, output_path, threshold)

if __name__ == "__main__":
    main()
