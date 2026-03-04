# Invalid Map Test Cases for Cub3D

Bu klasör, Cub3D projesinin mandatory kısmı için tüm invalid durumları test eden map dosyalarını içerir.

## Test Kategorileri

### Player Validasyonu
- **01_no_player.cub** - Haritada hiç player yok
- **02_multiple_players.cub** - Haritada birden fazla player var (N ve S)
- **21_player_on_edge.cub** - Player haritanın kenarında (duvarın üstünde)
- **38_mixed_player_orientations.cub** - Birden fazla farklı yönlü player (N ve W)
- **39_player_lowercase.cub** - Player karakteri küçük harf (n yerine N olmalı)

### Harita Kapalılık Kontrolü
- **03_map_not_closed_top.cub** - Harita üstten kapalı değil
- **04_map_not_closed_bottom.cub** - Harita alttan kapalı değil
- **05_map_not_closed_left.cub** - Harita soldan kapalı değil
- **06_map_not_closed_right.cub** - Harita sağdan kapalı değil
- **20_space_in_map_not_closed.cub** - Haritadaki boşluklar düzgün kapatılmamış
- **29_irregular_walls.cub** - Düzensiz duvarlar (boşluklarla başlayan satırlar)
- **37_space_border_exposed.cub** - Boşluk karakterlerinin sınırı açıkta

### Harita İçeriği ve Formatı
- **07_invalid_character.cub** - Geçersiz karakter (X) haritada
- **08_empty_map.cub** - Boş harita
- **22_map_with_newlines_inside.cub** - Harita içinde boş satırlar var
- **23_no_map.cub** - Hiç harita yok
- **25_map_before_textures.cub** - Harita texture tanımlamalarından önce (yanlış sıralama)
- **28_hole_in_map.cub** - Haritada delik var (bu aslında valid olabilir, kontrol edilmeli)
- **30_empty_line_in_map.cub** - Harita içinde boş satır
- **35_only_walls.cub** - Sadece duvarlardan oluşan harita (player yok)
- **36_too_small_map.cub** - Çok küçük harita (1x3)

### Texture Validasyonu
- **09_missing_north_texture.cub** - North texture eksik
- **10_missing_south_texture.cub** - South texture eksik
- **11_missing_west_texture.cub** - West texture eksik
- **12_missing_east_texture.cub** - East texture eksik
- **15_duplicate_north_texture.cub** - North texture iki kez tanımlanmış
- **33_texture_path_empty.cub** - Texture path'i boş

### Renk Validasyonu
- **13_missing_floor_color.cub** - Floor color eksik
- **14_missing_ceiling_color.cub** - Ceiling color eksik
- **16_invalid_floor_color_range.cub** - Floor color değeri 255'ten büyük (256)
- **17_invalid_ceiling_color_range.cub** - Ceiling color değeri 255'ten büyük (300)
- **18_negative_color_value.cub** - Negatif renk değeri (-1)
- **19_invalid_color_format.cub** - Yanlış renk formatı (2 değer, 3 olmalı)
- **26_color_with_spaces.cub** - Renk değerlerinde boşluklar var
- **27_non_numeric_color.cub** - Renk değeri sayısal değil (abc)
- **31_tabs_in_color.cub** - Renk değerlerinde tab karakteri
- **40_color_too_many_values.cub** - Çok fazla renk değeri (4 değer, 3 olmalı)

### Format ve Parsing
- **24_wrong_extension.cu** - Yanlış dosya uzantısı (.cu yerine .cub olmalı)
- **32_extra_text_after_color.cub** - Renk tanımından sonra fazladan text
- **34_wrong_identifier.cub** - Yanlış identifier (CEILING yerine C olmalı)

## Kullanım

Test script'ini çalıştırmak için:

```bash
# Önce projenizi derleyin
make

# Test script'ini çalıştırın
./test_invalid_maps.sh
```

Script her invalid map için programınızı çalıştıracak ve aşağıdakileri kontrol edecek:
1. Program sıfırdan farklı bir exit code ile çıkmalı
2. Program "Error" içeren bir mesaj yazdırmalı

## Beklenen Davranış

Subject'e göre:
> If any misconfiguration of any kind is encountered in the file, the program
> must exit properly and return "Error\n" followed by an explicit error message
> of your choice.

Tüm bu test dosyaları için programınız:
- "Error\n" yazdırmalı
- Ardından açıklayıcı bir hata mesajı göstermeli
- Sıfırdan farklı bir exit code ile sonlanmalı

## Notlar

- Bazı edge case'ler implementasyonunuza göre valid veya invalid olabilir
- Örneğin: Harita içindeki tab karakterleri, ekstra boşluklar vb.
- Bu testler mandatory kısmı içindir, bonus testler ayrı olmalıdır
