import argparse
import json
import re
from datetime import date
from pathlib import Path

TOKEN_MAP = {
    "XXXXXXX": "KC_NO",
    "_______": "KC_TRNS",
}

ALIAS_MAP = {
    "KC_ESCAPE": "KC_ESC",
    "KC_BSPACE": "KC_BSPC",
    "KC_SPACE": "KC_SPC",
    "KC_ENTER": "KC_ENT",
    "KC_DELETE": "KC_DEL",
    "KC_RIGHT": "KC_RGHT",
    "KC_CAPSLOCK": "KC_CAPS",
    "KC_SCROLLLOCK": "KC_SLCK",
    "KC_NUMLOCK": "KC_NLCK",
    "KC_LCTRL": "KC_LCTL",
    "KC_RCTRL": "KC_RCTL",
    "KC_LSHIFT": "KC_LSFT",
    "KC_RSHIFT": "KC_RSFT",
    "KC_LCMD": "KC_LGUI",
    "KC_LWIN": "KC_LGUI",
    "KC_RCMD": "KC_RGUI",
    "KC_RWIN": "KC_RGUI",
    "KC_PSCREEN": "KC_PSCR",
    "KC_INSERT": "KC_INS",
    "KC_PAGEUP": "KC_PGUP",
    "KC_PAGEDOWN": "KC_PGDN",
    "KC_SEMICOLON": "KC_SCLN",
    "KC_QUOTE": "KC_QUOT",
    "KC_MINUS": "KC_MINS",
    "KC_EQUAL": "KC_EQL",
    "KC_COMMA": "KC_COMM",
    "KC_SLASH": "KC_SLSH",
    "KC_BSLASH": "KC_BSLS",
    "KC_LBRACKET": "KC_LBRC",
    "KC_RBRACKET": "KC_RBRC",
    "KC_GRAVE": "KC_GRV",
    "KC_TILDE": "KC_TILD",
    "KC_MEDIA_NEXT_TRACK": "KC_MNXT",
    "KC_MEDIA_PREV_TRACK": "KC_MPRV",
    "KC_MEDIA_STOP": "KC_MSTP",
    "KC_MEDIA_PLAY_PAUSE": "KC_MPLY",
    "KC_MEDIA_SELECT": "KC_MSEL",
    "KC_MEDIA_EJECT": "KC_EJCT",
    "KC_MEDIA_FAST_FORWARD": "KC_MFFD",
    "KC_MEDIA_REWIND": "KC_MRWD",
    "KC_VOLUME_MUTE": "KC_MUTE",
    "KC_VOLUME_UP": "KC_VOLU",
    "KC_VOLUME_DOWN": "KC_VOLD",
    "KC_PAUSE": "KC_PAUS",
    "KC_KP_SLASH": "KC_PSLS",
    "KC_KP_ASTERISK": "KC_PAST",
    "KC_KP_MINUS": "KC_PMNS",
    "KC_KP_PLUS": "KC_PPLS",
    "KC_KP_ENTER": "KC_PENT",
    "KC_KP_DOT": "KC_PDOT",
    "KC_KP_EQUAL": "KC_PEQL",
    "KC_KP_COMMA": "KC_PCMM",
    "KC_KP_0": "KC_P0",
    "KC_KP_1": "KC_P1",
    "KC_KP_2": "KC_P2",
    "KC_KP_3": "KC_P3",
    "KC_KP_4": "KC_P4",
    "KC_KP_5": "KC_P5",
    "KC_KP_6": "KC_P6",
    "KC_KP_7": "KC_P7",
    "KC_KP_8": "KC_P8",
    "KC_KP_9": "KC_P9",
}

DOCUMENTATION = (
    '"This file is a QMK Configurator export. You can import this at '
    "<https://config.qmk.fm>. It can also be used directly with QMK's "
    "source code.\n\nTo setup your QMK environment check out the tutorial: "
    "<https://docs.qmk.fm/#/newbs>\n\nYou can convert this file to a "
    "keymap.c using this command: `qmk json2c {keymap}`\n\nYou can compile "
    'this keymap using this command: `qmk compile {keymap}`"\n'
)


def strip_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    src = re.sub(r"//[^\n]*", "", src)
    src = re.sub(r"(?m)^\s*#.*$", "", src)
    return src


def extract_balanced(src, open_pos):
    open_ch = src[open_pos]
    close_ch = {"(": ")", "{": "}", "[": "]"}[open_ch]
    depth = 0
    for i in range(open_pos, len(src)):
        c = src[i]
        if c == open_ch:
            depth += 1
        elif c == close_ch:
            depth -= 1
            if depth == 0:
                return src[open_pos + 1 : i]
    raise ValueError(f"delimitador {open_ch!r} sin cerrar en posicion {open_pos}")


def split_top_level(text):
    parts = []
    depth = 0
    cur = []
    for c in text:
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        if c == "," and depth == 0:
            parts.append("".join(cur).strip())
            cur = []
        else:
            cur.append(c)
    tail = "".join(cur).strip()
    if tail:
        parts.append(tail)
    return parts


def parse_layers(src):
    decl = re.search(
        r"keymaps\s*\[[^\]]*\]\s*\[[^\]]*\]\s*\[[^\]]*\]\s*=\s*\{", src
    )
    if not decl:
        raise ValueError("no se encontro la declaracion keymaps[][ROWS][COLS]")
    body = extract_balanced(src, decl.end() - 1)
    layers = []
    for m in re.finditer(r"\[([^\]]+)\]\s*=\s*(\w+)\s*\(", body):
        args = extract_balanced(body, m.end() - 1)
        keys = []
        for tok in split_top_level(args):
            tok = re.sub(r"\s+", "", tok)
            if tok:
                tok = TOKEN_MAP.get(tok, tok)
                keys.append(ALIAS_MAP.get(tok, tok))
        layers.append({"index": m.group(1), "macro": m.group(2), "keys": keys})
    if not layers:
        raise ValueError("no se encontraron capas dentro de keymaps")
    return layers


def convert(c_file, keyboard, out_path, day, layout_arg=None):
    src = Path(c_file).read_text(encoding="utf-8")
    layers = parse_layers(strip_comments(src))

    layout = layers[0]["macro"]
    others = {l["macro"] for l in layers} - {layout}
    if others:
        print(f"aviso: macros de layout distintos {others}; se usa {layout}")

    if layout_arg and layout_arg != layout:
        print(
            f"aviso: layout indicado '{layout_arg}' difiere del macro "
            f"'{layout}' del codigo; se usa '{layout_arg}'"
        )
        layout = layout_arg

    sizes = sorted({len(l["keys"]) for l in layers})
    if len(sizes) > 1:
        print(f"aviso: capas con distinto numero de teclas: {sizes}")

    if keyboard is None:
        stem = Path(c_file).stem
        keyboard = stem.split("_layout")[0]
        print(f"aviso: keyboard deducido como '{keyboard}'; usa --keyboard para fijarlo")

    keymap_name = f"{keyboard.replace('/', '_')}_{layout.lower()}_{day}"
    data = {
        "documentation": DOCUMENTATION,
        "notes": "",
        "version": 1,
        "keyboard": keyboard,
        "keymap": keymap_name,
        "layout": layout,
        "layers": [l["keys"] for l in layers],
        "author": "",
    }

    if out_path is None:
        out_path = Path(f"{keymap_name}.json")
    out_path = Path(out_path)
    out_path.write_text(
        json.dumps(data, indent=2, ensure_ascii=False), encoding="utf-8"
    )

    print(f"entrada : {c_file}")
    print(f"teclado : {keyboard}")
    print(f"layout  : {layout}")
    print(f"capas   : {len(layers)} ({', '.join(str(s) for s in sizes)} teclas)")
    print(f"salida  : {out_path}")


DESCRIPTION = """\
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
"""

EPILOG = """\
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
"""


def main():
    ap = argparse.ArgumentParser(
        description=DESCRIPTION,
        epilog=EPILOG,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument("inputs", nargs="+", help="archivos .c de entrada")
    ap.add_argument(
        "-k", "--keyboard", default=None, help="nombre del teclado, ej. crkbd/rev1"
    )
    ap.add_argument(
        "-l",
        "--layout",
        default=None,
        help="fuerza el nombre del layout en la salida "
        "(por defecto se deduce del macro LAYOUT_x del .c)",
    )
    ap.add_argument(
        "-o",
        "--output",
        default=None,
        help="archivo .json de salida (solo con un archivo de entrada)",
    )
    ap.add_argument(
        "-d",
        "--date",
        default=date.today().isoformat(),
        help="fecha para el nombre de salida (YYYY-MM-DD)",
    )
    args = ap.parse_args()

    if args.output and len(args.inputs) > 1:
        ap.error("--output solo se puede usar con un archivo de entrada")

    for c_file in args.inputs:
        convert(c_file, args.keyboard, args.output, args.date, args.layout)


if __name__ == "__main__":
    main()
