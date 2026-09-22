/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MEDIA 3
#define _SLEFT 4
#define _SRIGHT 5

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define LHAND MO(_SLEFT)
#define RHAND MO(_SRIGHT)
#define OCR LCG(KC_PSCR)
#define ATAJOS LGUI(KC_A)

enum unicode_names {
    ENEMIN,   // ñ
    ENEMAY  // Ñ (mayúscula)
};

// Asignamos el valor hexadecimal Unicode
const uint32_t PROGMEM unicode_map[] = {
    [ENEMIN] = 0x00F1, // ñ
    [ENEMAY] = 0x00D1  // Ñ
};

// Definimos la tecla que hace el cambio automático con Shift
#define KEY_ENE UP(ENEMIN, ENEMAY)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LGUI,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_LCTL
                                      //|--------------------------|  |--------------------------|
  ),

[_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LHAND,LGUI(KC_A),LGUI(KC_S), LGUI(KC_D),LGUI(KC_F), LGUI(KC_G),             KC_LEFT,  KC_DOWN,  KC_UP,KC_RIGHT, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
KC_LSFT, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B),            KEY_ENE, KC_CAPS, KC_APP , KC_GRV, KC_TILD, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, _______,  KC_SPC,     KC_ENT,   RAISE, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

[_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC , KC_EXLM, KC_AT  , KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB , KC_PSCR, KC_INS , KC_HOME, KC_PGUP, KC_WBAK,                      KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  RHAND,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT , OCR    , KC_DEL , KC_END , KC_PGDN, KC_WFWD,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER,  KC_SPC,     KC_ENT, _______, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

 [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX,                      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, XXXXXXX,                       KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, KC_MUTE,                       KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

 [_SLEFT] = LAYOUT_split_3x6_3( // Esta capa  es para usar la parte Izquierda a una mano
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
XXXXXXX, LGUI(KC_Q), LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), LGUI(KC_T),             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   _______, LGUI(KC_TAB),KC_LT, KC_GT, KC_MPLY,ATAJOS,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, LCG(KC_L),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_ENT, _______, KC_ENT,    XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

 [_SRIGHT] = LAYOUT_split_3x6_3( // Esta capa  es para usar la parte Derecha a una mano
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, LGUI(KC_W), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     ATAJOS, KC_MPLY, KC_LT, KC_GT, LGUI(KC_TAB), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     LCG(KC_L), KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    KC_ENT, _______,  KC_ENT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [_LOWER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [_RAISE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [_MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [_SLEFT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [_SRIGHT] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_clear(); // Borrar toda la estática/puntitos de arranque
    return OLED_ROTATION_270;
}

void render_matrix_text(void) {
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(" M\n"), false);
    oled_write_P(PSTR(" A\n"), false);
    oled_write_P(PSTR(" T\n"), false);
    oled_write_P(PSTR(" R\n"), false);
    oled_write_P(PSTR(" I\n"), false);
    oled_write_P(PSTR(" X\n"), false);
}

bool oled_task_user(void) {
    render_matrix_text();
    return false;
}

#endif

void keyboard_post_init_user(void) {
    set_unicode_input_mode(UNICODE_MODE_LINUX);
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv_noeeprom(0, 0, 100); // Color blanco configurado
        rgblight_disable_noeeprom();          // Pero inicia APAGADO
    #endif

    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_enable_noeeprom();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(0, 0, 100); // Color blanco configurado
        rgb_matrix_disable_noeeprom();          // Pero inicia APAGADO
    #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Si _LOWER y _RAISE están activos a la vez -> activa_MEDIA
    return update_tri_layer_state(state, _LOWER, _RAISE, _MEDIA);
}

// TODO LO SIGUIENTE  ES PARA MANDAR LA LETRA ENE Y ENEMAY EN LINUX
// Definimos los nombres para los caracteres

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case KEY_ENE:
//             if (record->event.pressed) {
//                 uint8_t mods = get_mods();
//                 if (mods & MOD_MASK_SHIFT) {
//                     del_mods(MOD_MASK_SHIFT); // Quita shift temporalmente
//                     send_unicode_hex_string("00D1"); // Código de 'Ñ'
//                     set_mods(mods); // Restaura shift
//                 } else {
//                     send_unicode_hex_string("00F1"); // Código de 'ñ'
//                 }
//             }
//             return false;
//     }
//     return true;
// }

