from PIL import Image, ImageDraw, ImageFont

FONT_PATH = "./font.ttf"
FONT_SIZE = 32
SPACING = 0
DRAW_COLOR = (0, 0, 0)

CHARS_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXSYZ"
CHARS_LOWER = "abcdefghijklmnopqrstuvwxsyz"
CHARS_NUMBER = "0123456789:;<=>?"
CHARS_SYMBOL = " !\"#$%&'()*+,-./"
# dont add or remove characters, they are accorded to ASCII

sections = [CHARS_UPPER, CHARS_LOWER, CHARS_NUMBER, CHARS_SYMBOL]
font = ImageFont.truetype(FONT_PATH, FONT_SIZE)
widths = {}
max_widths = {}
curr_section = 0

image = Image.new('RGB', (len(CHARS_UPPER) * FONT_SIZE, len(sections) * FONT_SIZE), (255, 255, 255))

for curr_section, section in enumerate(sections):
    for char in sections[curr_section]:
        temp_img = Image.new('RGB', (FONT_SIZE, FONT_SIZE), (255, 255, 255))
        ImageDraw.Draw(temp_img).text((0, 0), char, font = font, fill = DRAW_COLOR)

        pixels = temp_img.load()
        width = 0
        for x in range(FONT_SIZE):
            for y in range(FONT_SIZE):
                if (pixels[x, y] == DRAW_COLOR):
                    width = max(width, x)
        widths[char] = width + 1

    max_width = max(widths.values())

    draw_x = 0
    for char in section:
        draw_y = curr_section * FONT_SIZE
        ImageDraw.Draw(image).text((draw_x, draw_y), char, font = font, fill = DRAW_COLOR)

        pixels = image.load()
        draw_x_backup = draw_x
        curr_x = 0
        curr_y = 0

        for x in range(widths[char]):
            for y in range(FONT_SIZE):
                curr_x = draw_x_backup + x 
                curr_y = y + curr_section * FONT_SIZE
                if (pixels[curr_x, curr_y] != DRAW_COLOR):
                    if (x == 0):
                        pixels[curr_x, curr_y] = (0, 0, 255)
                    else:
                        pixels[curr_x, curr_y] = (255, 0, 0)
        
        draw_x = draw_x_backup + max_width + SPACING

    curr_section += 1

image.save("font.png")
print("OK")