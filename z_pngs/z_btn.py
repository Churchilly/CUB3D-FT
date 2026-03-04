from PIL import Image, ImageDraw, ImageFont

def create_hover_button(
    background_path,
    output_path,
    text,
    font_path,
    font_size=32,
    # Normal (unhovered) state
    normal_text_color=(255, 255, 255),
    normal_outline_color=(0, 0, 0),
    normal_outline_width=2,
    # Hovered state
    hover_text_color=(255, 50, 50),
    hover_outline_color=(139, 0, 0),
    hover_outline_width=2
):
    """
    Arkaplan resmi üzerine yan yana 2 state (normal + hover) buton oluşturur
    
    Sol yarı: Normal state
    Sağ yarı: Hover state
    """
    # Arkaplanı yükle
    background = Image.open(background_path)
    bg_width, bg_height = background.size
    
    # 2x genişlikte yeni image oluştur
    final_image = Image.new('RGBA', (bg_width * 2, bg_height))
    
    # Font yükle
    try:
        font = ImageFont.truetype(font_path, font_size)
    except:
        print(f"Font yüklenemedi: {font_path}")
        font = ImageFont.load_default()
    
    # Geçici draw ile text boyutunu hesapla
    temp_draw = ImageDraw.Draw(background)
    bbox = temp_draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    
    # Ortalama pozisyonunu hesapla (her iki state için aynı)
    x = (bg_width - text_width) // 2
    y = (bg_height - text_height) // 2
    
    # STATE 1: Normal (sol yarı)
    normal_bg = background.copy()
    draw_normal = ImageDraw.Draw(normal_bg)
    
    # Normal outline
    if normal_outline_width > 0:
        for offset_x in range(-normal_outline_width, normal_outline_width + 1):
            for offset_y in range(-normal_outline_width, normal_outline_width + 1):
                draw_normal.text(
                    (x + offset_x, y + offset_y),
                    text,
                    font=font,
                    fill=normal_outline_color
                )
    
    # Normal text
    draw_normal.text((x, y), text, font=font, fill=normal_text_color)
    
    # Sol tarafa yapıştır
    final_image.paste(normal_bg, (0, 0))
    
    # STATE 2: Hover (sağ yarı)
    hover_bg = background.copy()
    draw_hover = ImageDraw.Draw(hover_bg)
    
    # Hover outline
    if hover_outline_width > 0:
        for offset_x in range(-hover_outline_width, hover_outline_width + 1):
            for offset_y in range(-hover_outline_width, hover_outline_width + 1):
                draw_hover.text(
                    (x + offset_x, y + offset_y),
                    text,
                    font=font,
                    fill=hover_outline_color
                )
    
    # Hover text
    draw_hover.text((x, y), text, font=font, fill=hover_text_color)
    
    # Sağ tarafa yapıştır
    final_image.paste(hover_bg, (bg_width, 0))
    
    # Kaydet
    final_image.save(output_path)
    print(f"Hover buton kaydedildi: {output_path} ({bg_width * 2}x{bg_height})")
    return final_image

# KULLANIM ÖRNEĞİ:
if __name__ == "__main__":
    # Birden fazla buton için
    buttons = [
        ("CAMPAIGN", "btn_campaign.png"),
        ("MAPS", "btn_maps.png"),
        ("CONTINUE", "btn_continue.png"),
        ("EXIT", "btn_exit.png"),
    ]
    
    for text, output in buttons:
        create_hover_button(
            background_path="z_button_bg.png",
            output_path=output,
            text=text,
            font_path="font.ttf",
            font_size=40,
            normal_text_color=(180, 180, 180),
            normal_outline_color=(40, 40, 40),
            normal_outline_width=2,
            hover_text_color=(255, 255, 100),  # Sarımsı hover
            hover_outline_color=(150, 0, 0),
            hover_outline_width=2
        )