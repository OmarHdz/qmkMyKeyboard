/* A standard layout for the Dactyl Manuform 5x6 Keyboard */                                                                                                                
                                                                                                                                                                            
#include QMK_KEYBOARD_H                                                                                                                                                     
                                                                                                                                                                            
#define _QWERTY 0                                                                                                                                                           
#define _NUM 1                                                                                                                                                              
#define _PROG 2                                                                                                                                                             
#define _MOVE 3                                                                                                                                                             
#define _SIMBOL 4                                                                                                                                                           
#define _ESPEJO 5                                                                                                                                                           
                                                                                                                                                                            
#define CPUNO MO(_NUM)                                                                                                                                                      
#define CPDOS MO(_PROG)                                                                                                                                                     
#define CPTRE MO(_MOVE)                                                                                                                                                     
#define CPCUA MO(_SIMBOL)                                                                                                                                                   
#define CPCIN MO(_ESPEJO)                                                                                                                                                   
                                                                                                                                                                            
bool is_alt_tab_active = false; // ADD this near the begining of keymap.c                                                                                                   
                                                                                                                                                                            
enum custom_keycodes {                                                                                                                                                      
  QWERTY = SAFE_RANGE,                                                                                                                                                      
  FNDGIT,                                                                                                                                                                   
  SNDCMD,                                                                                                                                                                   
  IPY,                                                                                                                                                                      
  GIT,                                                                                                                                                                      
  NOTES,                                                                                                                                                                    
  ENEMIN,                                                                                                                                                                   
  ENEMAY,                                                                                                                                                                   
};                                                                                                                                                                          
                                                                                                                                                                            
                                                                                                                                                                            
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {                                                                                                              
                                                                                                                                                                            
  [_QWERTY] = LAYOUT_5x6(                                                                                                                                                   
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,            KC_6  , KC_7  , KC_8  , KC_9  , KC_0,  KC_BSPC,                                                            
     KC_CAPS, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,            KC_Y  , KC_U  , KC_I  , KC_O  , KC_P,  KC_DEL,                                                             
     KC_TAB , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,            KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,                                                            
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,            KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,                                                            
                      KC_LCTL,KC_LALT,                                          KC_RALT, KC_RCTL,                                                                           
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
  [_NUM] = LAYOUT_5x6(                                                                                                                                                      
     KC_ESC ,_______,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,            _______, KC_NLCK, KC_PSLS,KC_PAST , KC_PMNS, KC_BSPC,                                                      
     KC_CAPS,_______, KC_P7 , KC_P8 , KC_P9 ,_______,            _______, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_DEL,                                                       
     CPCIN  ,KC_AGIN, KC_P4 , KC_P5 , KC_P6 ,_______,            _______, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_COMM,                                                      
     KC_LSFT,KC_UNDO, KC_P1 , KC_P2 , KC_P3 ,_______,            _______, KC_P1  , KC_P2  , KC_P3  , KC_PENT, KC_RSFT,                                                      
                     KC_PDOT, KC_P0 ,                                          KC_P0, KC_PDOT,                                                                              
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
  [_PROG] = LAYOUT_5x6(                                                                                                                                                     
     KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,                                                               
     KC_CAPS, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRIU, KC_BRID,       LGUI(KC_UP), SGUI(KC_LEFT), SGUI(KC_RIGHT), LCTL(KC_W), LALT(KC_F4), KC_WHOM,                              
     KC_TAB , KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_WREF,       KC_F5, LCTL(KC_PGDN), LCTL(KC_PGUP), KC_TAB, KC_LALT, LCTL(KC_HOME),                                       
     KC_LSFT, KC_WHOM, KC_WSCH, KC_WBAK, KC_WFWD, KC_WFAV,       RCS(KC_P), LCTL(KC_N), LCTL(KC_T), LCTL(KC_L), NOTES, LCTL(KC_END),                                        
                      KC_LCTL,KC_LALT,                                          KC_RALT, KC_RCTL,                                                                           
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
  [_MOVE] = LAYOUT_5x6(                                                                                                                                                     
     _______,KC_INS, KC_PSCR,KC_SLCK,KC_PAUS,_______,            KC_BTN4,KC_BTN1,KC_BTN2,KC_BTN5,_______,KC_BSPC,                                                           
     _______,_______,_______,_______,_______,_______,            KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,KC_DEL ,                                                           
     _______,_______,KC_CALC,KC_MYCM,_______,_______,            KC_LEFT,KC_DOWN, KC_UP,KC_RIGHT,_______,_______,                                                           
     _______,_______,_______,_______,_______,_______,            ENEMIN , ENEMAY, KC_APP,    IPY, FNDGIT, SNDCMD,                                                           
                      KC_LCTL,KC_LALT,                                           KC_RALT, KC_RCTL,                                                                          
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
  [_SIMBOL] = LAYOUT_5x6(                                                                                                                                                   
     _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,KC_BSPC,                                                           
     _______,_______,_______,_______,_______,_______,            _______,_______,_______,_______,_______,KC_DEL ,                                                           
     _______,_______,_______,_______,_______,_______,            KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,KC_GRV ,                                                           
     _______,_______,_______,_______,_______,_______,            KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_TILD,                                                           
                      KC_LCTL,KC_LALT,                                          KC_RALT, KC_RCTL,                                                                           
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
  [_ESPEJO] = LAYOUT_5x6(                                                                                                                                                   
     KC_ESC , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,            KC_6  , KC_7  , KC_8  , KC_9  , KC_0,  KC_BSPC,                                                            
     KC_DEL , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,            KC_Y  , KC_U  , KC_I  , KC_O  , KC_P,  KC_DEL,                                                             
     _______, KC_H  , KC_J  , KC_K  , KC_L  , KC_SCLN,           KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,                                                            
     KC_LSFT, KC_N  , KC_M  ,KC_COMM, KC_DOT, KC_SLSH,           KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,                                                            
                      KC_LCTL,KC_LALT,                                          KC_RALT, KC_RCTL,                                                                           
                                      CPUNO,   CPDOS,            CPTRE,   CPCUA,                                                                                            
                                      KC_SPC,  KC_HOME,          KC_END,  KC_ENT,                                                                                           
                                      KC_LGUI, KC_PGUP,          KC_PGDN, KC_RGUI                                                                                           
  ),                                                                                                                                                                        
                                                                                                                                                                            
};                                                                                                                                                                          
                                                                                                                                                                            
                                                                                                                                                                            
bool process_record_user(uint16_t keycode, keyrecord_t *record) {                                                                                                           
                                                                                                                                                                            
bool is_alt_tab_active = false; // ADD this near the begining of keymap.c                                                                                                   
                                                                                                                                                                            
 switch (keycode) {                                                                                                                                                         
    case FNDGIT:                                                                                                                                                            
        if (record->event.pressed) {                                                                                                                                        
            tap_code(KC_Y);                                                                                                                                                 
            wait_ms(100);                                                                                                                                                   
            tap_code(KC_ESC);                                                                                                                                               
            wait_ms(150);                                                                                                                                                   
            SEND_STRING(":!");                                                                                                                                              
            wait_ms(300);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            wait_ms(300);                                                                                                                                                   
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LCTL);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LCTL);                                                                                                                                       
            wait_ms(100);                                                                                                                                                   
            tap_code16(LCTL(KC_V));                                                                                                                                         
            wait_ms(200);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            is_alt_tab_active = false;                                                                                                                                      
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LALT);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LALT);                                                                                                                                       
            wait_ms(100);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
        } else {                                                                                                                                                            
            unregister_code(KC_TAB);                                                                                                                                        
        }                                                                                                                                                                   
        return false;                                                                                                                                                       
    case SNDCMD:                                                                                                                                                            
        if (record->event.pressed) {                                                                                                                                        
            tap_code(KC_Y);                                                                                                                                                 
            wait_ms(100);                                                                                                                                                   
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LALT);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LALT);                                                                                                                                       
            wait_ms(100);                                                                                                                                                   
            tap_code16(LCTL(KC_V));                                                                                                                                         
            wait_ms(200);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            is_alt_tab_active = false;                                                                                                                                      
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LALT);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LALT);                                                                                                                                       
        } else {                                                                                                                                                            
            unregister_code(KC_TAB);                                                                                                                                        
        }                                                                                                                                                                   
        return false;                                                                                                                                                       
    case IPY:                                                                                                                                                               
        if (record->event.pressed) {                                                                                                                                        
            tap_code(KC_ESC);                                                                                                                                               
            wait_ms(300);                                                                                                                                                   
            SEND_STRING(":!");                                                                                                                                              
            wait_ms(300);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            wait_ms(300);                                                                                                                                                   
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LCTL);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LCTL);                                                                                                                                       
            wait_ms(100);                                                                                                                                                   
            tap_code16(LCTL(KC_D));                                                                                                                                         
            wait_ms(200);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            wait_ms(500);                                                                                                                                                   
            SEND_STRING("ipython");                                                                                                                                         
            wait_ms(100);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
            is_alt_tab_active = false;                                                                                                                                      
            if (!is_alt_tab_active) {                                                                                                                                       
            is_alt_tab_active = true;                                                                                                                                       
            register_code(KC_LCTL);                                                                                                                                         
            }                                                                                                                                                               
            tap_code(KC_TAB);                                                                                                                                               
            unregister_code(KC_LCTL);                                                                                                                                       
            tap_code(KC_ENT);                                                                                                                                               
        } else {                                                                                                                                                            
            unregister_code(KC_TAB);                                                                                                                                        
        }                                                                                                                                                                   
        return false;                                                                                                                                                       
    case ENEMIN:                                                                                                                                                            
      if (record->event.pressed) {                                                                                                                                          
            SEND_STRING(SS_LALT(SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_4) ));                                                                                            
      } else {                                                                                                                                                              
       }                                                                                                                                                                    
          return true;                                                                                                                                                      
    case ENEMAY:                                                                                                                                                            
      if (record->event.pressed) {                                                                                                                                          
            SEND_STRING(SS_LALT(SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_5) ));                                                                                            
      } else {                                                                                                                                                              
       }                                                                                                                                                                    
          return true;                                                                                                                                                      
    case NOTES:                                                                                                                                                             
        if (record->event.pressed) {                                                                                                                                        
            tap_code(KC_LGUI);                                                                                                                                              
            wait_ms(300);                                                                                                                                                   
            SEND_STRING("sticky");                                                                                                                                          
            wait_ms(300);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
        } else {                                                                                                                                                            
            unregister_code(KC_LGUI);                                                                                                                                       
        }                                                                                                                                                                   
        return false;                                                                                                                                                       
    case GIT:                                                                                                                                                               
        if (record->event.pressed) {                                                                                                                                        
            tap_code(KC_LGUI);                                                                                                                                              
            wait_ms(300);                                                                                                                                                   
            SEND_STRING("git");                                                                                                                                             
            wait_ms(300);                                                                                                                                                   
            tap_code(KC_ENT);                                                                                                                                               
        } else {                                                                                                                                                            
            unregister_code(KC_LGUI);                                                                                                                                       
        }                                                                                                                                                                   
        return false;                                                                                                                                                       
                                                                                                                                                                            
      break;                                                                                                                                                                
  }                                                                                                                                                                         
  return true;                                                                                                                                                              
}                                                                                                                                                                           
