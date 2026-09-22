
# Asegúrate de estar en el entorno virtual
cd ~/qmk_firmware
source .venv/bin/activate

# Crear tu keymap a partir del estándar del Corne rev1 (el más común para Pro Micro)
# marchy es el nombre del teclado
qmk new-keymap -kb crkbd/rev1 -km marchy 

~/qmk_firmware/keyboards/crkbd/keymaps/marchy/

¡Excelente elección! El **Corne (crkbd)** es probablemente el teclado dividido más popular.

Al ser un teclado dividido (*split*) que usa dos placas Pro Micro, el proceso tiene unos pasos específicos para que no tengas problemas entre la mitad izquierda y la derecha.

Aquí tienes la guía paso a paso para crear tu propia modificación y flashearlo:

---

### Paso 1: Crear tu propio keymap (No modifiques el `default`)

La mejor práctica en QMK es copiar el mapa por defecto a una carpeta con tu nombre (por ejemplo, `marchy`):

```bash
# Asegúrate de estar en el entorno virtual
cd ~/qmk_firmware
source .venv/bin/activate

# Crear tu keymap a partir del estándar del Corne rev1 (el más común para Pro Micro)
qmk new-keymap -kb crkbd/rev1 -km marchy
```
*(Si te pregunta algo, confirma con Enter).*

Esto habrá creado una carpeta en:
`~/qmk_firmware/keyboards/crkbd/keymaps/marchy/`

---

### Paso 2: Editar tu configuración

Dentro de esa carpeta encontrarás principalmente:

1.  **`keymap.c`**: Aquí es donde defines qué hace cada tecla, las capas (layers), combinaciones, etc. Puedes abrirlo con tu editor favorito (VS Code, Neovim, Nano):
    ```bash
    nano keyboards/crkbd/keymaps/marchy/keymap.c
    ```
2.  **`rules.mk`** (Opcional): Aquí activas o desactivas funciones para ahorrar memoria (muy útil en el Pro Micro, que tiene poca memoria flash). Por ejemplo:
    *   `OLED_ENABLE = yes` (si le pusiste pantallitas OLED).
    *   `RGBLIGHT_ENABLE = yes` (si le pusiste luces LED).

---

### Paso 3: Probar la compilación

Antes de conectar nada, compila para asegurarte de que tu código no tiene errores de sintaxis en C:

```bash
qmk compile -kb crkbd/rev1 -km marchy
```
Si al final dice `[OK]`, tu firmware está listo para ser quemado en el microcontrolador.

---

### Paso 4: Flashear las DOS mitades

Al ser un teclado dividido, **debes flashear ambos Arduinos** por separado con el mismo archivo.

#### A) Mitad Izquierda (Master por defecto):
1. Conecta **únicamente la mitad izquierda** por USB a tu PC (desconecta el cable TRRS/Jack entre las dos mitades por seguridad).
2. Lanza el comando de flasheo:
   ```bash
   qmk flash -kb crkbd/rev1 -km marchy
   ```
3. Cuando la terminal muestre `Waiting for USB serial port to appear...`, haz el **doble puente rápido entre RST y GND** en el Arduino izquierdo.
4. Espera a que termine de subir el archivo.

#### B) Mitad Derecha:
1. Desconecta la mitad izquierda.
2. Conecta **únicamente la mitad derecha** por USB a tu PC.
3. Vuelve a ejecutar el mismo comando:
   ```bash
   qmk flash -kb crkbd/rev1 -km marchy
   ```
4. Haz el **doble puente entre RST y GND** en el Arduino derecho.

---

### Paso 5: Conexión final (¡Cuidado aquí!)

> ⚠️ **Regla de oro de los teclados split:** **NUNCA conectes ni desconectes el cable TRRS (el cable que une las dos mitades) mientras el teclado esté enchufado al PC por USB.** Podrías hacer un cortocircuito y quemar los pines del Pro Micro o las pantallas OLED.

1. Desconecta todo del PC.
2. Conecta el cable TRRS uniendo la mitad izquierda con la derecha.
3. Conecta el cable USB del ordenador a la **mitad izquierda** (el lado izquierdo suele ser el maestro por defecto).
4. ¡Listo! Ya tienes tu Corne funcionando con tu configuración personalizada.

### Paso 6: 

python keymap_converter.py keymapSplitv8.c -k crkbd/rev1 -l LAYOUT_split_3x6_3

se generara un archivo .json listo para subir a la pagina qmk configurator para generar el pdf con las teclas programadas.

### Paso 7:

Atajos con omarchy, aqui esta la direccion donde debe de estar el pdf con la guia
cat ~/.local/bin/guia-teclado.sh

