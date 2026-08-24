/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    keyball_set_scroll_mode(false);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef COMBO_ENABLE
enum combos {
    // マウス操作
    CMB_LCLICK,   // J+K -> 左クリック
    CMB_RCLICK,   // K+L -> 右クリック
    CMB_MCLICK,   // J+L -> 中クリック
    CMB_SCRL_V,   // M+, -> 押下中スクロール（縦）
    CMB_SCRL_H,   // ,+. -> 押下中スクロール（横）
    CMB_BACK,     // U+I -> 戻る
    CMB_FWD,      // I+O -> 進む

    // 括弧ペア入力＋1文字戻る（一時的に無効化）
    // CMB_PAIR_BRACKET,   // E+R -> [] 内側へ
    // CMB_PAIR_PAREN,     // D+F -> () 内側へ
    // CMB_PAIR_BRACE,     // C+V -> {} 内側へ

    // IME切替
    CMB_JP_OFF,   // F+左親指2 -> 英数
    CMB_JP_ON,    // J+右親指2 -> かな
};

// ---- キー組み合わせ ----
const uint16_t PROGMEM cmb_lclick[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM cmb_rclick[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM cmb_mclick[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM cmb_scrl_v[] = {KC_M, MT(MOD_RSHIFT, KC_COMM), COMBO_END};                 // M + ,
const uint16_t PROGMEM cmb_scrl_h[] = {MT(MOD_RSHIFT, KC_COMM), MT(MOD_RALT, KC_DOT), COMBO_END}; // , + .
const uint16_t PROGMEM cmb_back[]   = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cmb_fwd[]    = {KC_I, KC_O, COMBO_END};

// 括弧ペア（一時的に無効化）
// const uint16_t PROGMEM cmb_pair_bracket[] = {KC_E, KC_R, COMBO_END};
// const uint16_t PROGMEM cmb_pair_paren[]   = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM cmb_pair_brace[]   = {KC_C, KC_V, COMBO_END};

// IME切替（親指キーは内側から2番目 = Space/LT(2), Enter/LT(3)）
const uint16_t PROGMEM cmb_jp_off[] = {KC_F, MT(MOD_LSHIFT, KC_SPC), COMBO_END};   // 英数
const uint16_t PROGMEM cmb_jp_on[]  = {KC_J, LT(3, KC_ENT), COMBO_END};   // かな

// ---- コンボ本体 ----
combo_t key_combos[] = {
    [CMB_LCLICK] = COMBO(cmb_lclick, KC_BTN1),
    [CMB_RCLICK] = COMBO(cmb_rclick, KC_BTN2),
    [CMB_MCLICK] = COMBO(cmb_mclick, KC_BTN3),
    [CMB_SCRL_V] = COMBO_ACTION(cmb_scrl_v),
    [CMB_SCRL_H] = COMBO_ACTION(cmb_scrl_h),
    [CMB_BACK]   = COMBO(cmb_back,   KC_BTN4),
    [CMB_FWD]    = COMBO(cmb_fwd,    KC_BTN5),

    // 括弧ペア（一時的に無効化）
    // [CMB_PAIR_BRACKET] = COMBO(cmb_pair_bracket, KC_NO),m
    // [CMB_PAIR_PAREN]   = COMBO(cmb_pair_paren,   KC_NO),
    // [CMB_PAIR_BRACE]   = COMBO(cmb_pair_brace,   KC_NO),

    [CMB_JP_OFF] = COMBO(cmb_jp_off, KC_LNG2),   // 英数
    [CMB_JP_ON]  = COMBO(cmb_jp_on,  KC_LNG1),   // かな
};

// スクロール方向を指定してスクロールモードを切り替える
static void scroll_with_snap(keyball_scrollsnap_mode_t snap, bool pressed) {
    if (pressed) {
        keyball_set_scrollsnap_mode(snap);
        keyball_set_scroll_mode(true);
    } else {
        keyball_set_scroll_mode(false);
    }
}

// ===================================================================
// JIS配列のキー対応（US配列とは [ ] の位置が1つずれる）
//   (  = Shift + X_8
//   )  = Shift + X_9
//   {  = Shift + X_RBRC
//   }  = Shift + X_BSLS
//   [  = X_RBRC
//   ]  = X_BSLS
// ===================================================================
void process_combo_event(uint16_t combo_index, bool pressed) {
    // 押下・離上の両方を扱うもの
    switch (combo_index) {
        case CMB_SCRL_V:   // 縦スクロール
            scroll_with_snap(KEYBALL_SCROLLSNAP_MODE_VERTICAL, pressed);
            return;
        case CMB_SCRL_H:   // 横スクロール
            scroll_with_snap(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL, pressed);
            return;
    }

    // 括弧ペア（一時的に無効化）
    // if (!pressed) return;
    // switch (combo_index) {
    //     case CMB_PAIR_BRACE:   // {}
    //         SEND_STRING(SS_LSFT(SS_TAP(X_RBRC)) SS_LSFT(SS_TAP(X_BSLS)) SS_TAP(X_LEFT));
    //         break;
    //     case CMB_PAIR_PAREN:   // ()
    //         SEND_STRING(SS_LSFT(SS_TAP(X_8)) SS_LSFT(SS_TAP(X_9)) SS_TAP(X_LEFT));
    //         break;
    //     case CMB_PAIR_BRACKET: // []
    //         SEND_STRING(SS_TAP(X_RBRC) SS_TAP(X_BSLS) SS_TAP(X_LEFT));
    //         break;
    // }
}
#endif