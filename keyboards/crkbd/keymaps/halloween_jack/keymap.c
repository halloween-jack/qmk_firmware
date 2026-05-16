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

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE
};

//#define RAISE LT(_RAISE, KC_SPC)
#define LOWER MO(_LOWER)
#define GUI LGUI_T(KC_ESC)
#define WINDOW LALT_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(

  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           WINDOW,     GUI,   RAISE,    KC_BSPC,  KC_ENT,   LOWER
                                      //`--------------------------'  `--------------------------'

  ),

    [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_TILD, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           WINDOW,     GUI,   RAISE,    KC_BSPC,  KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_F11,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           WINDOW,     GUI, XXXXXXX,    XXXXXXX, MS_BTN1, MS_BTN2
                                      //`--------------------------'  `--------------------------'
  )
};

// LT(_RAISE, KC_SPC)ではCTRL+SpaceによるIME切り替えでラグが発生する
// CTRLキー押下時にRAISEキーが押されたときにはTAPPING_TERMの秒数を待たずにSpaceを入力するように設定している
// 状態管理用の変数
static uint16_t raise_timer = 0;
static bool raise_pressed = false;
static bool raise_is_ctrl_mode = false;
static bool raise_interrupted = false;

// 1. 常時監視：TAPPING_TERMを超えたら即座にレイヤーON
void matrix_scan_user(void) {
    if (raise_pressed && !raise_is_ctrl_mode && !raise_interrupted) {
        if (!layer_state_is(_RAISE) && timer_elapsed(raise_timer) > TAPPING_TERM) {
            layer_on(_RAISE);
        }
    }
}

// 2. キー入力処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RAISE:
      if (record->event.pressed) {
        raise_timer = timer_read();
        raise_pressed = true;
        raise_interrupted = false;

        if (get_mods() & MOD_MASK_CTRL) {
          register_code(KC_SPC);
          raise_is_ctrl_mode = true;
        } else {
          raise_is_ctrl_mode = false;
        }
        return false;
      } else {
        raise_pressed = false;
        if (raise_is_ctrl_mode) {
          unregister_code(KC_SPC);
        } else {
          bool was_layer_on = layer_state_is(_RAISE);
          layer_off(_RAISE);
          // 「他キーを打っていない」かつ「時間内」かつ「レイヤーになっていない」ならSpace
          if (!was_layer_on && !raise_interrupted && timer_elapsed(raise_timer) < TAPPING_TERM) {
            tap_code(KC_SPC);
          }
        }
        return false;
      }

    default:
      // RAISE押下中に他のキーが打たれた場合
      if (record->event.pressed && raise_pressed && !raise_is_ctrl_mode) {
        if (timer_elapsed(raise_timer) > TAPPING_TERM) {
          layer_on(_RAISE); // 長押し確定
          raise_interrupted = true;
        } else {
          tap_code(KC_SPC); // 高速タイピング時はSpaceを入力
          raise_interrupted = true;
        }
      }
      break;
  }
  return true;
}
