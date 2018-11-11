#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3
#define _SUPER 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOUSE,
  SUPER,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define EISU LALT(KC_GRV)
#define LNG_TOG LM(_SUPER, MOD_LGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------------------------------------------
   * |  Esc |  Tab |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   |  ]   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------|------|
   * | MOUSE| Ctrl |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  "   | Enter|
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------|------|
   * | LOWER| Shift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  | Shift| RAISE|
   * |--------------------+------+------+------+------+------+------+------+------+------+------+------+-------------|------|
   * |ADJUST|      |      |  ALt ||||||||  GUI | Space|      ||||||||      | Bksp | LOWER||||||||  ALt | Down |  Up  | Right|
   * ,---------------------------------------------------------------------------------------------------------------.------.
   */
  [_QWERTY] = LAYOUT( \
     KC_ESC,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, \
     LOWER,   KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
     _______, KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, RAISE,   \
     ADJUST,  MOUSE  ,  _______, KC_LALT,          LNG_TOG, KC_SPC, _______,       _______,KC_BSPC, LOWER,            KC_RALT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |                    |   &  |   *  |   (  |   )  |   _  |   +  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   -  |   =  |  \   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   F6 |   F7 |   F8 |   F9 |  F10 |  F11 |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_TILD,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,                        KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_PIPE, \
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                           KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_BSLS,  \
    KC_LSFT,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_RSFT,  \
    KC_LCTL,  KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|   F6 |   F7 |   F8 |   F9 |  F10 | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
  * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
  * | Ctrl |  F11 |  F12 | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQT , \
    KC_LSFT, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_SPC ,                        KC_ENT , KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT, \
    KC_LCTL, KC_F11 , KC_F12,  EISU,             LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
    ),

  /* MOUSE
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_MOUSE] = LAYOUT(
    KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LCBR,                        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_RCBR, KC_COLN, KC_DQT , \
    KC_LSFT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SPC ,                        KC_ENT , KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_BTN1 ,KC_BTN2,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* SUPER
   * ,-----------------------------------------------------------------------------------------------------------------------
   * |  Esc |  Tab |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   |  ]   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------|------|
   * | MOUSE| Ctrl |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  "   | Enter|
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------|------|
   * |      | Shift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  | Shift| RAISE|
   * |--------------------+------+------+------+------+------+------+------+------+------+------+------+-------------|------|
   * |ADJUST|      |      |  ALt ||||||||  GUI | Space|      |||||||| LOWER| Space |  GUI ||||||||  ALt | Down |  Up  | Right|
   * ,---------------------------------------------------------------------------------------------------------------.------.
   */
  [_SUPER] = LAYOUT( \
     KC_ESC,  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, \
     MOUSE,   KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
     _______, KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, RAISE,   \
     ADJUST,  _______,  _______, KC_LALT,          LNG_TOG, KC_SPC, _______,       KC_SPC, LOWER,  KC_RGUI,          KC_RALT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_MOUSE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SUPER:
      if (record->event.pressed) {
        layer_on(_SUPER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_SUPER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
