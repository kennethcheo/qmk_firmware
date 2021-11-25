/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define _QW 0
#define _LS 1
#define _RS 2
#define _WM 3


// Current Features
// 1. Tap dance L-shift and caps lock
// 2. Triple tap dance brackets (,[,{
// 3. Hold: Raise, lower; Press: Enter, backspace
// 4. Ctrl and Alt keys swapped

// TODO:
// super key -> TG(layer) or TT(layer) for _WM layer
// more tap dance keys for shifted pairs
// remove "App" key and move alt there

// Tap Dance
enum {
    SFT_CPS = 0,
    TD_BRC_L,
    TD_BRC_R,
};

void triple_tap_L(qk_tap_dance_state_t *state, void *user_data);
void triple_tap_R(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPSLOCK),
    [TD_BRC_L] = ACTION_TAP_DANCE_FN(triple_tap_L),
    [TD_BRC_R] = ACTION_TAP_DANCE_FN(triple_tap_R),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _QW
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt  | App  | Ctrl | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QW] = LAYOUT_planck_grid(
    KC_ESC,      KC_Q,   KC_W,    KC_E,    KC_R,         KC_T,   KC_Y,   KC_U,          KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,      KC_A,   KC_S,    KC_D,    LT(3,KC_F),   KC_G,   KC_H,   KC_J,          KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TD(SFT_CPS), KC_Z,   KC_X,    KC_C,    KC_V,         KC_B,   KC_N,   KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LALT,     KC_APP, KC_LCTL, KC_LGUI, LT(1,KC_ENT), KC_SPC, KC_SPC, LT(2,KC_BSPC), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* _LS
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  |,\ |   0  |   1  |   2  |   3  | INS  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |  F5  |  F6  |  F7  |  F8  |(,[,{ | ),],}|   4  |   5  |   6  | PGUP | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F9  |  F10 |  F11 |  F12 | +,=  |  -,_ |   7  |   8  |   9  | PGDN | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt  | Del  | Ctrl | GUI  |Lower |    Space    |Raise |   0  |      |  B-  |  B+  |
 * `-----------------------------------------------------------------------------------'
 */
[_LS] = LAYOUT_planck_grid(
    KC_ESC,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_NO,        KC_P0,        KC_P1,   KC_P2, KC_P3, KC_INS,  KC_BSPC,
    KC_GRV,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   TD(TD_BRC_L), TD(TD_BRC_R), KC_P4,   KC_P5, KC_P6, KC_PGUP, KC_HOME,
    KC_LSFT, KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_NO ,       KC_NO,        KC_P7,   KC_P8, KC_P9, KC_PGDN, KC_END,
    KC_LALT, KC_DEL, KC_LCTL, KC_LGUI, KC_TRNS, KC_SPC,       KC_SPC,       KC_TRNS, KC_P0, KC_NO, KC_BRID, KC_BRIU
),

/* _RS
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |  *   |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   (  |   )  |   +  |   _  |   {  |   }  |      |      |      | PGUP | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   [  |   ]  |   =  |   -  |   |  |   \  |      |      |      | PGDN | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt  | Del  | Ctrl | GUI  |Lower |    Space    |Raise | Mute | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RS] = LAYOUT_planck_grid(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,   KC_TRNS, KC_BSPC,
    KC_GRV,  KC_LPRN, KC_RPRN, KC_PLUS, KC_UNDS, KC_LCBR,       KC_RCBR, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_LSFT, KC_LBRC, KC_RBRC, KC_EQL,  KC_MINS, LSFT(KC_BSLS), KC_BSLS, KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,
    KC_LALT, KC_DEL,  KC_LCTL, KC_LGUI, KC_TRNS, KC_SPC,        KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY
),

/* _WM
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |  *   |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   (  |   )  |   +  |   _  |   {  |   }  |      |      |      | PGUP | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   [  |   ]  |   =  |   -  |   |  |   \  |      |      |      | PGDN | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt  | Del  | Ctrl | GUI  |Lower |    Space    |Raise | Mute | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_WM] = LAYOUT_planck_grid(
    KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
    KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO
)

};


// tap dance

void triple_tap_L (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_LPRN);
    } else if (state->count == 2) {
        tap_code16 (KC_LBRC);
    } else if (state->count == 3) {
        tap_code16(KC_LCBR);
    } else {
        reset_tap_dance(state);
    }
}

void triple_tap_R (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_RPRN);
    } else if (state->count == 2) {
        tap_code16 (KC_RBRC);
    } else if (state->count == 3) {
        tap_code16(KC_RCBR);
    } else {
        reset_tap_dance(state);
    }
}

// SHIFT + BACKSPACE -> DELETE
// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        static bool delkey_registered;
        if (record->event.pressed) {

            if (mod_state & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                delkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        return true;
        }
    }
    return true;
};
