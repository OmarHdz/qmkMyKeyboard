qmkcreator/guiaAtajosTeclado.pdf

qmkMyKeyboard main    ? ❯ python keymap_converter.py -h
usage: keymap_converter.py [-h] [-k KEYBOARD] [-l LAYOUT] [-o OUTPUT] [-d DATE] inputs [inputs ...]

Convierte keymap.c de QMK al formato keymap.json de QMK Configurator.

Que hace:
  1. Lee el .c y elimina comentarios y directivas del preprocesador
     (#ifdef, #include, etc.), incluido el bloque del encoder_map.
  2. Extrae las capas de keymaps[][ROWS][COLS]: cada '[N] = LAYOUT_x(...)'
     es una capa y su contenido son los keycodes en orden.
  3. Normaliza keycodes: XXXXXXX -> KC_NO, _______ -> KC_TRNS y alias
     largos a cortos (KC_RIGHT -> KC_RGHT, KC_ESCAPE -> KC_ESC, ...).
  4. Escribe el JSON de QMK Configurator con las llaves documentation,
     notes, version, keyboard, keymap, layout, layers y author.

El layout y el teclado se deducen del propio .c (macro LAYOUT_x y nombre
del archivo); puedes fijarlos manualmente con -k y -l. El nombre de salida
por defecto es {teclado}_{layout_minusculas}_{fecha}.json

positional arguments:
  inputs                archivos .c de entrada

options:
  -h, --help            show this help message and exit
  -k, --keyboard KEYBOARD
                        nombre del teclado, ej. crkbd/rev1
  -l, --layout LAYOUT   fuerza el nombre del layout en la salida (por defecto se deduce del macro LAYOUT_x del .c)
  -o, --output OUTPUT   archivo .json de salida (solo con un archivo de entrada)
  -d, --date DATE       fecha para el nombre de salida (YYYY-MM-DD)

ejemplos:
  Conversion basica (teclado y layout deducidos automaticamente):
      python3 keymap_converter.py keymap.c

  Especificar teclado y layout explicitamente:
      python3 keymap_converter.py keymap.c -k crkbd/rev1 -l LAYOUT_split_3x6_3

  Elegir archivo y fecha de salida:
      python3 keymap_converter.py keymap.c -k crkbd/rev1 -o mi_keymap.json -d 2026-09-03

  Convertir varios archivos de golpe (el nombre de salida se genera solo):
      python3 keymap_converter.py keymap1.c keymap2.c -k crkbd/rev1

  Ver la salida generada para importarla en <https://config.qmk.fm>:
      qmk json2c mi_keymap.json    # la convierte de vuelta a keymap.c
      qmk compile mi_keymap.json   # la compila directamente
