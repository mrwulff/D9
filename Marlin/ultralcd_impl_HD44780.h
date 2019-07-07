#ifndef ULTRALCD_IMPL_HD44780_H
#define ULTRALCD_IMPL_HD44780_H
#include "utility.h"
#include "duration_t.h"
#if ENABLED(AUTO_BED_LEVELING_UBL)
  #include "ubl.h"
#endif
extern volatile uint8_t buttons;  
#if ENABLED(ULTIPANEL)
  #if ENABLED(LCD_I2C_VIKI)
    #define B_I2C_BTN_OFFSET 3 
    #define B_LE (BUTTON_LEFT<<B_I2C_BTN_OFFSET)    
    #define B_UP (BUTTON_UP<<B_I2C_BTN_OFFSET)
    #define B_MI (BUTTON_SELECT<<B_I2C_BTN_OFFSET)
    #define B_DW (BUTTON_DOWN<<B_I2C_BTN_OFFSET)
    #define B_RI (BUTTON_RIGHT<<B_I2C_BTN_OFFSET)
    #if BUTTON_EXISTS(ENC)
      #define B_ST (EN_C)                            
      #undef LCD_CLICKED
      #define LCD_CLICKED (buttons&(B_MI|B_RI|B_ST)) 
    #else
      #undef LCD_CLICKED
      #define LCD_CLICKED (buttons&(B_MI|B_RI))
    #endif
    #define LCD_HAS_SLOW_BUTTONS
  #elif ENABLED(LCD_I2C_PANELOLU2)
    #if !BUTTON_EXISTS(ENC) 
      #define B_I2C_BTN_OFFSET 3 
      #define B_MI (PANELOLU2_ENCODER_C<<B_I2C_BTN_OFFSET) 
      #undef LCD_CLICKED
      #define LCD_CLICKED (buttons & B_MI)
      #define LCD_HAS_SLOW_BUTTONS
    #endif
  #elif DISABLED(NEWPANEL) 
    #define BL_LE 7   
    #define BL_UP 6   
    #define BL_MI 5   
    #define BL_DW 4   
    #define BL_RI 3   
    #define BL_ST 2   
    #define B_LE (_BV(BL_LE))
    #define B_UP (_BV(BL_UP))
    #define B_MI (_BV(BL_MI))
    #define B_DW (_BV(BL_DW))
    #define B_RI (_BV(BL_RI))
    #define B_ST (_BV(BL_ST))
    #define LCD_CLICKED ((buttons & B_MI) || (buttons & B_ST))
  #endif
#endif 
#if ENABLED(LCD_I2C_TYPE_PCF8575)
  #define LCD_I2C_PIN_BL  3
  #define LCD_I2C_PIN_EN  2
  #define LCD_I2C_PIN_RW  1
  #define LCD_I2C_PIN_RS  0
  #define LCD_I2C_PIN_D4  4
  #define LCD_I2C_PIN_D5  5
  #define LCD_I2C_PIN_D6  6
  #define LCD_I2C_PIN_D7  7
  #include <Wire.h>
  #include <LCD.h>
  #include <LiquidCrystal_I2C.h>
  #define LCD_CLASS LiquidCrystal_I2C
  LCD_CLASS lcd(LCD_I2C_ADDRESS, LCD_I2C_PIN_EN, LCD_I2C_PIN_RW, LCD_I2C_PIN_RS, LCD_I2C_PIN_D4, LCD_I2C_PIN_D5, LCD_I2C_PIN_D6, LCD_I2C_PIN_D7);
#elif ENABLED(LCD_I2C_TYPE_MCP23017)
  #define LED_A 0x04 
  #define LED_B 0x02 
  #define LED_C 0x01 
  #define LCD_HAS_STATUS_INDICATORS
  #include <Wire.h>
  #include <LiquidTWI2.h>
  #define LCD_CLASS LiquidTWI2
  #if ENABLED(DETECT_DEVICE)
    LCD_CLASS lcd(LCD_I2C_ADDRESS, 1);
  #else
    LCD_CLASS lcd(LCD_I2C_ADDRESS);
  #endif
#elif ENABLED(LCD_I2C_TYPE_MCP23008)
  #include <Wire.h>
  #include <LiquidTWI2.h>
  #define LCD_CLASS LiquidTWI2
  #if ENABLED(DETECT_DEVICE)
    LCD_CLASS lcd(LCD_I2C_ADDRESS, 1);
  #else
    LCD_CLASS lcd(LCD_I2C_ADDRESS);
  #endif
#elif ENABLED(LCD_I2C_TYPE_PCA8574)
  #include <LiquidCrystal_I2C.h>
  #define LCD_CLASS LiquidCrystal_I2C
  LCD_CLASS lcd(LCD_I2C_ADDRESS, LCD_WIDTH, LCD_HEIGHT);
#elif ENABLED(SR_LCD_2W_NL)
  extern "C" void __cxa_pure_virtual() { while (1); }
  #include <LCD.h>
  #include <LiquidCrystal_SR.h>
  #define LCD_CLASS LiquidCrystal_SR
  #if PIN_EXISTS(SR_STROBE)
    LCD_CLASS lcd(SR_DATA_PIN, SR_CLK_PIN, SR_STROBE_PIN);
  #else
    LCD_CLASS lcd(SR_DATA_PIN, SR_CLK_PIN);
  #endif
#elif ENABLED(LCM1602)
  #include <Wire.h>
  #include <LCD.h>
  #include <LiquidCrystal_I2C.h>
  #define LCD_CLASS LiquidCrystal_I2C
  LCD_CLASS lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#else
  #include <LiquidCrystal.h>
  #define LCD_CLASS LiquidCrystal
  LCD_CLASS lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7); 
#endif
#include "utf_mapper.h"
#if ENABLED(LCD_PROGRESS_BAR)
  static millis_t progress_bar_ms = 0;
  #if PROGRESS_MSG_EXPIRE > 0
    static millis_t expire_status_ms = 0;
  #endif
  #define LCD_STR_PROGRESS  "\x03\x04\x05"
#endif
#if ENABLED(LCD_HAS_STATUS_INDICATORS)
  static void lcd_implementation_update_indicators();
#endif
static void createChar_P(const char c, const byte * const ptr) {
  byte temp[8];
  for (uint8_t i = 0; i < 8; i++)
    temp[i] = pgm_read_byte(&ptr[i]);
  lcd.createChar(c, temp);
}
static void lcd_set_custom_characters(
  #if ENABLED(LCD_PROGRESS_BAR)
    const bool info_screen_charset = true
  #endif
) {
  const static PROGMEM byte bedTemp[8] = {
    B00000,
    B11111,
    B10101,
    B10001,
    B10101,
    B11111,
    B00000,
    B00000
  };
  const static PROGMEM byte degree[8] = {
    B01100,
    B10010,
    B10010,
    B01100,
    B00000,
    B00000,
    B00000,
    B00000
  };
  const static PROGMEM byte thermometer[8] = {
    B00100,
    B01010,
    B01010,
    B01010,
    B01010,
    B10001,
    B10001,
    B01110
  };
  const static PROGMEM byte uplevel[8] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B11100,
    B00000,
    B00000,
    B00000
  };
  const static PROGMEM byte feedrate[8] = {
    B11100,
    B10000,
    B11000,
    B10111,
    B00101,
    B00110,
    B00101,
    B00000
  };
  const static PROGMEM byte clock[8] = {
    B00000,
    B01110,
    B10011,
    B10101,
    B10001,
    B01110,
    B00000,
    B00000
  };
  #if ENABLED(SDSUPPORT)
    const static PROGMEM byte refresh[8] = {
      B00000,
      B00110,
      B11001,
      B11000,
      B00011,
      B10011,
      B01100,
      B00000,
    };
    const static PROGMEM byte folder[8] = {
      B00000,
      B11100,
      B11111,
      B10001,
      B10001,
      B11111,
      B00000,
      B00000
    };
    #if ENABLED(LCD_PROGRESS_BAR)
      const static PROGMEM byte progress[3][8] = { {
        B00000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B10000,
        B00000
      }, {
        B00000,
        B10100,
        B10100,
        B10100,
        B10100,
        B10100,
        B10100,
        B00000
      }, {
        B00000,
        B10101,
        B10101,
        B10101,
        B10101,
        B10101,
        B10101,
        B00000
      } };
    #endif
  #endif
  createChar_P(LCD_BEDTEMP_CHAR, bedTemp);
  createChar_P(LCD_DEGREE_CHAR, degree);
  createChar_P(LCD_STR_THERMOMETER[0], thermometer);
  createChar_P(LCD_FEEDRATE_CHAR, feedrate);
  createChar_P(LCD_CLOCK_CHAR, clock);
  #if ENABLED(SDSUPPORT)
    #if ENABLED(LCD_PROGRESS_BAR)
      static bool char_mode = false;
      if (info_screen_charset != char_mode) {
        char_mode = info_screen_charset;
        if (info_screen_charset) { 
          for (int16_t i = 3; i--;) createChar_P(LCD_STR_PROGRESS[i], progress[i]);
        }
        else { 
          createChar_P(LCD_UPLEVEL_CHAR, uplevel);
          createChar_P(LCD_STR_REFRESH[0], refresh);
          createChar_P(LCD_STR_FOLDER[0], folder);
        }
      }
    #else
      createChar_P(LCD_UPLEVEL_CHAR, uplevel);
      createChar_P(LCD_STR_REFRESH[0], refresh);
      createChar_P(LCD_STR_FOLDER[0], folder);
    #endif
  #else
    createChar_P(LCD_UPLEVEL_CHAR, uplevel);
  #endif
}
static void lcd_implementation_init(
  #if ENABLED(LCD_PROGRESS_BAR)
    const bool info_screen_charset = true
  #endif
) {
  #if ENABLED(LCD_I2C_TYPE_PCF8575)
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    #ifdef LCD_I2C_PIN_BL
      lcd.setBacklightPin(LCD_I2C_PIN_BL, POSITIVE);
      lcd.setBacklight(HIGH);
    #endif
  #elif ENABLED(LCD_I2C_TYPE_MCP23017)
    lcd.setMCPType(LTI_TYPE_MCP23017);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    lcd_implementation_update_indicators();
  #elif ENABLED(LCD_I2C_TYPE_MCP23008)
    lcd.setMCPType(LTI_TYPE_MCP23008);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  #elif ENABLED(LCD_I2C_TYPE_PCA8574)
    lcd.init();
    lcd.backlight();
  #else
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  #endif
  lcd_set_custom_characters(
    #if ENABLED(LCD_PROGRESS_BAR)
      info_screen_charset
    #endif
  );
  lcd.clear();
}
void lcd_implementation_clear() { lcd.clear(); }
void lcd_print(const char c) { charset_mapper(c); }
void lcd_print(const char *str) { while (*str) lcd.print(*str++); }
void lcd_printPGM(const char *str) { while (const char c = pgm_read_byte(str)) lcd.print(c), ++str; }
void lcd_print_utf(const char *str, uint8_t n=LCD_WIDTH) {
  char c;
  while (n && (c = *str)) n -= charset_mapper(c), ++str;
}
void lcd_printPGM_utf(const char *str, uint8_t n=LCD_WIDTH) {
  char c;
  while (n && (c = pgm_read_byte(str))) n -= charset_mapper(c), ++str;
}
#if ENABLED(SHOW_BOOTSCREEN)
  void lcd_erase_line(const int16_t line) {
    lcd.setCursor(0, line);
    for (uint8_t i = LCD_WIDTH + 1; --i;)
      lcd.write(' ');
  }
  void lcd_scroll(const int16_t col, const int16_t line, const char* const text, const int16_t len, const int16_t time) {
    char tmp[LCD_WIDTH + 1] = {0};
    int16_t n = max(lcd_strlen_P(text) - len, 0);
    for (int16_t i = 0; i <= n; i++) {
      strncpy_P(tmp, text + i, min(len, LCD_WIDTH));
      lcd.setCursor(col, line);
      lcd_print(tmp);
      delay(time / max(n, 1));
    }
  }
  static void logo_lines(const char* const extra) {
    int16_t indent = (LCD_WIDTH - 8 - lcd_strlen_P(extra)) / 2;
    lcd.setCursor(indent, 0); lcd.print('\x00'); lcd_printPGM(PSTR( "------" ));  lcd.write('\x01');
    lcd.setCursor(indent, 1);                    lcd_printPGM(PSTR("|Marlin|"));  lcd_printPGM(extra);
    lcd.setCursor(indent, 2); lcd.write('\x02'); lcd_printPGM(PSTR( "------" ));  lcd.write('\x03');
  }
  void lcd_bootscreen() {
    const static PROGMEM byte corner[4][8] = { {
      B00000,
      B00000,
      B00000,
      B00000,
      B00001,
      B00010,
      B00100,
      B00100
    }, {
      B00000,
      B00000,
      B00000,
      B11100,
      B11100,
      B01100,
      B00100,
      B00100
    }, {
      B00100,
      B00010,
      B00001,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    }, {
      B00100,
      B01000,
      B10000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000
    } };
    for (uint8_t i = 0; i < 4; i++)
      createChar_P(i, corner[i]);
    lcd.clear();
    #define LCD_EXTRA_SPACE (LCD_WIDTH-8)
    #define CENTER_OR_SCROLL(STRING,DELAY) \
      lcd_erase_line(3); \
      if (strlen(STRING) <= LCD_WIDTH) { \
        lcd.setCursor((LCD_WIDTH - lcd_strlen_P(PSTR(STRING))) / 2, 3); \
        lcd_printPGM(PSTR(STRING)); \
        safe_delay(DELAY); \
      } \
      else { \
        lcd_scroll(0, 3, PSTR(STRING), LCD_WIDTH, DELAY); \
      }
    #ifdef STRING_SPLASH_LINE1
      if (LCD_EXTRA_SPACE >= strlen(STRING_SPLASH_LINE1) + 1) {
        logo_lines(PSTR(" " STRING_SPLASH_LINE1));
        #ifdef STRING_SPLASH_LINE2
          CENTER_OR_SCROLL(STRING_SPLASH_LINE2, 2000);
        #else
          safe_delay(2000);
        #endif
      }
      else {
        #ifdef STRING_SPLASH_LINE2
          #define _SPLASH_WAIT_1 1500
        #else
          #define _SPLASH_WAIT_1 2000
        #endif
        logo_lines(PSTR(""));
        CENTER_OR_SCROLL(STRING_SPLASH_LINE1, _SPLASH_WAIT_1);
        #ifdef STRING_SPLASH_LINE2
          CENTER_OR_SCROLL(STRING_SPLASH_LINE2, 1500);
        #endif
      }
    #elif defined(STRING_SPLASH_LINE2)
      if (LCD_EXTRA_SPACE >= strlen(STRING_SPLASH_LINE2) + 1) {
        logo_lines(PSTR(" " STRING_SPLASH_LINE2));
        safe_delay(2000);
      }
      else {
        logo_lines(PSTR(""));
        CENTER_OR_SCROLL(STRING_SPLASH_LINE2, 2000);
      }
    #else
      logo_lines(PSTR(""));
      safe_delay(2000);
    #endif
    lcd.clear();
    safe_delay(100);
    lcd_set_custom_characters(
      #if ENABLED(LCD_PROGRESS_BAR)
        false
      #endif
    );
  }
#endif 
void lcd_kill_screen() {
  lcd.setCursor(0, 0);
  lcd_print_utf(lcd_status_message);
  #if LCD_HEIGHT < 4
    lcd.setCursor(0, 2);
  #else
    lcd.setCursor(0, 2);
    lcd_printPGM(PSTR(MSG_HALTED));
    lcd.setCursor(0, 3);
  #endif
  lcd_printPGM(PSTR(MSG_PLEASE_RESET));
}
FORCE_INLINE void _draw_axis_label(const AxisEnum axis, const char* const pstr, const bool blink) {
  if (blink)
    lcd_printPGM(pstr);
  else {
    if (!axis_homed[axis])
      lcd.write('?');
    else {
      #if DISABLED(DISABLE_REDUCED_ACCURACY_WARNING)
        if (!axis_known_position[axis])
          lcd.write(' ');
        else
      #endif
      lcd_printPGM(pstr);
    }
  }
}
FORCE_INLINE void _draw_heater_status(const int8_t heater, const char prefix, const bool blink) {
  const bool isBed = heater < 0;
  const float t1 = (isBed ? thermalManager.degBed()       : thermalManager.degHotend(heater)),
              t2 = (isBed ? thermalManager.degTargetBed() : thermalManager.degTargetHotend(heater));
  if (prefix >= 0) lcd.print(prefix);
  lcd.print(itostr3(t1 + 0.5));
  lcd.write('/');
  #if HEATER_IDLE_HANDLER
    const bool is_idle = (!isBed ? thermalManager.is_heater_idle(heater) :
      #if HAS_TEMP_BED
        thermalManager.is_bed_idle()
      #else
        false
      #endif
    );
    if (!blink && is_idle) {
      lcd.write(' ');
      if (t2 >= 10) lcd.write(' ');
      if (t2 >= 100) lcd.write(' ');
    }
    else
  #endif
      lcd.print(itostr3left(t2 + 0.5));
  if (prefix >= 0) {
    lcd.print((char)LCD_DEGREE_CHAR);
    lcd.write(' ');
    if (t2 < 10) lcd.write(' ');
  }
}
#if ENABLED(LCD_PROGRESS_BAR)
  inline void lcd_draw_progress_bar(const uint8_t percent) {
    const int16_t tix = (int16_t)(percent * (LCD_WIDTH) * 3) / 100,
              cel = tix / 3,
              rem = tix % 3;
    uint8_t i = LCD_WIDTH;
    char msg[LCD_WIDTH + 1], b = ' ';
    msg[LCD_WIDTH] = '\0';
    while (i--) {
      if (i == cel - 1)
        b = LCD_STR_PROGRESS[2];
      else if (i == cel && rem != 0)
        b = LCD_STR_PROGRESS[rem - 1];
      msg[i] = b;
    }
    lcd.print(msg);
  }
#endif 
static void lcd_implementation_status_screen() {
  const bool blink = lcd_blink();
  lcd.setCursor(0, 0);
  #if LCD_WIDTH < 20
    _draw_heater_status(0, -1, blink);
    #if HOTENDS > 1 || TEMP_SENSOR_BED != 0
      lcd.setCursor(8, 0);
      #if HOTENDS > 1
        lcd.print((CHAR)LCD_STR_THERMOMETER[0]);
        _draw_heater_status(1, -1, blink);
      #else
        lcd.print((CHAR)LCD_BEDTEMP_CHAR);
        _draw_heater_status(-1, -1, blink);
      #endif
    #endif 
  #else 
    _draw_heater_status(0, LCD_STR_THERMOMETER[0], blink);
    #if HOTENDS > 1 || TEMP_SENSOR_BED != 0
      lcd.setCursor(10, 0);
      #if HOTENDS > 1
        _draw_heater_status(1, LCD_STR_THERMOMETER[0], blink);
      #else
        _draw_heater_status(-1, LCD_BEDTEMP_CHAR, blink);
      #endif
    #endif 
  #endif 
  #if LCD_HEIGHT > 2
    #if LCD_WIDTH < 20
      #if ENABLED(SDSUPPORT)
        lcd.setCursor(0, 2);
        lcd_printPGM(PSTR("SD"));
        if (IS_SD_PRINTING)
          lcd.print(itostr3(card.percentDone()));
        else
          lcd_printPGM(PSTR("---"));
          lcd.write('%');
      #endif 
    #else 
      lcd.setCursor(0, 1);
      #if HOTENDS > 1 && TEMP_SENSOR_BED != 0
      _draw_heater_status(-1, LCD_BEDTEMP_CHAR, blink);
      #else
        _draw_axis_label(X_AXIS, PSTR(MSG_X), blink);
        lcd.print(ftostr4sign(current_position[X_AXIS]));
        lcd.write(' ');
        _draw_axis_label(Y_AXIS, PSTR(MSG_Y), blink);
        lcd.print(ftostr4sign(current_position[Y_AXIS]));
      #endif 
    #endif 
    lcd.setCursor(LCD_WIDTH - 8, 1);
    _draw_axis_label(Z_AXIS, PSTR(MSG_Z), blink);
    lcd.print(ftostr52sp(FIXFLOAT(current_position[Z_AXIS])));
  #endif 
  #if LCD_HEIGHT > 3
    lcd.setCursor(0, 2);
    lcd.print((char)LCD_FEEDRATE_CHAR);
    lcd.print(itostr3(feedrate_percentage));
    lcd.write('%');
    #if LCD_WIDTH >= 20 && ENABLED(SDSUPPORT)
      lcd.setCursor(7, 2);
      lcd_printPGM(PSTR("SD"));
      if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
      else
        lcd_printPGM(PSTR("---"));
      lcd.write('%');
    #endif 
    char buffer[10];
    duration_t elapsed = print_job_timer.duration();
    uint8_t len = elapsed.toDigital(buffer);
    lcd.setCursor(LCD_WIDTH - len - 1, 2);
    lcd.print((char)LCD_CLOCK_CHAR);
    lcd_print(buffer);
  #endif 
  lcd.setCursor(0, LCD_HEIGHT - 1);
  #if ENABLED(LCD_PROGRESS_BAR)
    if (card.isFileOpen() && (ELAPSED(millis(), progress_bar_ms + PROGRESS_BAR_MSG_TIME) || !lcd_status_message[0])) {
      const uint8_t percent = card.percentDone();
      if (percent) return lcd_draw_progress_bar(percent);
    }
  #elif ENABLED(FILAMENT_LCD_DISPLAY) && ENABLED(SDSUPPORT)
    if (ELAPSED(millis(), previous_lcd_status_ms + 5000UL)) {
      lcd_printPGM(PSTR("Dia "));
      lcd.print(ftostr12ns(filament_width_meas));
      lcd_printPGM(PSTR(" V"));
      lcd.print(itostr3(100.0 * volumetric_multiplier[FILAMENT_SENSOR_EXTRUDER_NUM]));
      lcd.write('%');
      return;
    }
  #endif 
  #if ENABLED(STATUS_MESSAGE_SCROLLING)
    static bool last_blink = false;
    const uint8_t slen = lcd_strlen(lcd_status_message);
    const char *stat = lcd_status_message + status_scroll_pos;
    if (slen <= LCD_WIDTH)
      lcd_print_utf(stat);                                      
    else {
      if (status_scroll_pos <= slen - LCD_WIDTH)
        lcd_print_utf(stat);                                    
      else {
        uint8_t chars = LCD_WIDTH;
        if (status_scroll_pos < slen) {                         
          lcd_print_utf(stat);                                  
          chars -= slen - status_scroll_pos;                    
        }
        lcd.write('.');                                         
        if (--chars) {
          if (status_scroll_pos < slen + 1)                     
            --chars, lcd.write('.');
          if (chars) lcd_print_utf(lcd_status_message, chars);  
        }
      }
      if (last_blink != blink) {
        last_blink = blink;
        if (status_scroll_pos < slen) while (!PRINTABLE(lcd_status_message[status_scroll_pos])) status_scroll_pos++;
        if (++status_scroll_pos >= slen + 2) status_scroll_pos = 0;
      }
    }
  #else
    lcd_print_utf(lcd_status_message);
  #endif
}
#if ENABLED(ULTIPANEL)
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    static void lcd_implementation_hotend_status(const uint8_t row) {
      if (row < LCD_HEIGHT) {
        lcd.setCursor(LCD_WIDTH - 9, row);
        _draw_heater_status(active_extruder, LCD_STR_THERMOMETER[0], lcd_blink());
      }
    }
  #endif 
  static void lcd_implementation_drawmenu_static(const uint8_t row, const char* pstr, const bool center=true, const bool invert=false, const char *valstr=NULL) {
    UNUSED(invert);
    char c;
    int8_t n = LCD_WIDTH;
    lcd.setCursor(0, row);
    if (center && !valstr) {
      int8_t pad = (LCD_WIDTH - lcd_strlen_P(pstr)) / 2;
      while (--pad >= 0) { lcd.write(' '); n--; }
    }
    while (n > 0 && (c = pgm_read_byte(pstr))) {
      n -= charset_mapper(c);
      pstr++;
    }
    if (valstr) while (n > 0 && (c = *valstr)) {
      n -= charset_mapper(c);
      valstr++;
    }
    while (n-- > 0) lcd.write(' ');
  }
  static void lcd_implementation_drawmenu_generic(const bool sel, const uint8_t row, const char* pstr, const char pre_char, const char post_char) {
    char c;
    uint8_t n = LCD_WIDTH - 2;
    lcd.setCursor(0, row);
    lcd.print(sel ? pre_char : ' ');
    while ((c = pgm_read_byte(pstr)) && n > 0) {
      n -= charset_mapper(c);
      pstr++;
    }
    while (n--) lcd.write(' ');
    lcd.print(post_char);
  }
  static void lcd_implementation_drawmenu_setting_edit_generic(const bool sel, const uint8_t row, const char* pstr, const char pre_char, const char* const data) {
    char c;
    uint8_t n = LCD_WIDTH - 2 - lcd_strlen(data);
    lcd.setCursor(0, row);
    lcd.print(sel ? pre_char : ' ');
    while ((c = pgm_read_byte(pstr)) && n > 0) {
      n -= charset_mapper(c);
      pstr++;
    }
    lcd.write(':');
    while (n--) lcd.write(' ');
    lcd_print(data);
  }
  static void lcd_implementation_drawmenu_setting_edit_generic_P(const bool sel, const uint8_t row, const char* pstr, const char pre_char, const char* const data) {
    char c;
    uint8_t n = LCD_WIDTH - 2 - lcd_strlen_P(data);
    lcd.setCursor(0, row);
    lcd.print(sel ? pre_char : ' ');
    while ((c = pgm_read_byte(pstr)) && n > 0) {
      n -= charset_mapper(c);
      pstr++;
    }
    lcd.write(':');
    while (n--) lcd.write(' ');
    lcd_printPGM(data);
  }
  #define DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(_type, _name, _strFunc) \
    inline void lcd_implementation_drawmenu_setting_edit_ ## _name (const bool sel, const uint8_t row, const char* pstr, const char* pstr2, _type * const data, ...) { \
      lcd_implementation_drawmenu_setting_edit_generic(sel, row, pstr, '>', _strFunc(*(data))); \
    } \
    inline void lcd_implementation_drawmenu_setting_edit_callback_ ## _name (const bool sel, const uint8_t row, const char* pstr, const char* pstr2, _type * const data, ...) { \
      lcd_implementation_drawmenu_setting_edit_generic(sel, row, pstr, '>', _strFunc(*(data))); \
    } \
    inline void lcd_implementation_drawmenu_setting_edit_accessor_ ## _name (const bool sel, const uint8_t row, const char* pstr, const char* pstr2, _type (*pget)(), void (*pset)(_type), ...) { \
      lcd_implementation_drawmenu_setting_edit_generic(sel, row, pstr, '>', _strFunc(pget())); \
    } \
    typedef void _name##_void
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(int16_t, int3, itostr3);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(uint8_t, int8, i8tostr3);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float3, ftostr3);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float32, ftostr32);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float43, ftostr43sign);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float5, ftostr5rj);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float51, ftostr51sign);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float52, ftostr52sign);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(float, float62, ftostr62rj);
  DEFINE_LCD_IMPLEMENTATION_DRAWMENU_SETTING_EDIT_TYPE(uint32_t, long5, ftostr5rj);
  #define lcd_implementation_drawmenu_setting_edit_bool(sel, row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(sel, row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
  #define lcd_implementation_drawmenu_setting_edit_callback_bool(sel, row, pstr, pstr2, data, callback) lcd_implementation_drawmenu_setting_edit_generic_P(sel, row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
  #define lcd_implementation_drawmenu_setting_edit_accessor_bool(sel, row, pstr, pstr2, pget, pset, callback) lcd_implementation_drawmenu_setting_edit_generic_P(sel, row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
  void lcd_implementation_drawedit(const char* pstr, const char* const value=NULL) {
    lcd.setCursor(1, 1);
    lcd_printPGM(pstr);
    if (value != NULL) {
      lcd.write(':');
      const uint8_t valrow = (lcd_strlen_P(pstr) + 1 + lcd_strlen(value) + 1) > (LCD_WIDTH - 2) ? 2 : 1;  
      lcd.setCursor((LCD_WIDTH - 1) - (lcd_strlen(value) + 1), valrow);                                   
      lcd.write(' ');                                                                                     
      lcd_print(value);
    }
  }
  #if ENABLED(SDSUPPORT)
    static void lcd_implementation_drawmenu_sd(const bool sel, const uint8_t row, const char* const pstr, const char* filename, char* const longFilename, const uint8_t concat, const char post_char) {
      UNUSED(pstr);
      char c;
      uint8_t n = LCD_WIDTH - concat;
      lcd.setCursor(0, row);
      lcd.print(sel ? '>' : ' ');
      if (longFilename[0]) {
        filename = longFilename;
        longFilename[n] = '\0';
      }
      while ((c = *filename) && n > 0) {
        n -= charset_mapper(c);
        filename++;
      }
      while (n--) lcd.write(' ');
      lcd.print(post_char);
    }
    static void lcd_implementation_drawmenu_sdfile(const bool sel, const uint8_t row, const char* pstr, const char* filename, char* const longFilename) {
      lcd_implementation_drawmenu_sd(sel, row, pstr, filename, longFilename, 2, ' ');
    }
    static void lcd_implementation_drawmenu_sddirectory(const bool sel, const uint8_t row, const char* pstr, const char* filename, char* const longFilename) {
      lcd_implementation_drawmenu_sd(sel, row, pstr, filename, longFilename, 2, LCD_STR_FOLDER[0]);
    }
  #endif 
  #define lcd_implementation_drawmenu_back(sel, row, pstr, dummy) lcd_implementation_drawmenu_generic(sel, row, pstr, LCD_UPLEVEL_CHAR, LCD_UPLEVEL_CHAR)
  #define lcd_implementation_drawmenu_submenu(sel, row, pstr, data) lcd_implementation_drawmenu_generic(sel, row, pstr, '>', LCD_STR_ARROW_RIGHT[0])
  #define lcd_implementation_drawmenu_gcode(sel, row, pstr, gcode) lcd_implementation_drawmenu_generic(sel, row, pstr, '>', ' ')
  #define lcd_implementation_drawmenu_function(sel, row, pstr, data) lcd_implementation_drawmenu_generic(sel, row, pstr, '>', ' ')
  #if ENABLED(LCD_HAS_SLOW_BUTTONS)
    extern millis_t next_button_update_ms;
    static uint8_t lcd_implementation_read_slow_buttons() {
      #if ENABLED(LCD_I2C_TYPE_MCP23017)
        uint8_t slow_bits = lcd.readButtons() << B_I2C_BTN_OFFSET;
        #if ENABLED(LCD_I2C_VIKI)
          if ((slow_bits & (B_MI | B_RI)) && PENDING(millis(), next_button_update_ms)) 
            slow_bits &= ~(B_MI | B_RI); 
        #endif 
        return slow_bits;
      #endif 
    }
  #endif 
#endif 
#if ENABLED(LCD_HAS_STATUS_INDICATORS)
  static void lcd_implementation_update_indicators() {
    static uint8_t ledsprev = 0;
    uint8_t leds = 0;
    if (thermalManager.degTargetBed() > 0) leds |= LED_A;
    if (thermalManager.degTargetHotend(0) > 0) leds |= LED_B;
    #if FAN_COUNT > 0
      if (0
        #if HAS_FAN0
          || fanSpeeds[0]
        #endif
        #if HAS_FAN1
          || fanSpeeds[1]
        #endif
        #if HAS_FAN2
          || fanSpeeds[2]
        #endif
      ) leds |= LED_C;
    #endif 
    #if HOTENDS > 1
      if (thermalManager.degTargetHotend(1) > 0) leds |= LED_C;
    #endif
    if (leds != ledsprev) {
      lcd.setBacklight(leds);
      ledsprev = leds;
    }
  }
#endif 
#if ENABLED(AUTO_BED_LEVELING_UBL)
  void lcd_set_ubl_map_plot_chars() {
    #if LCD_HEIGHT > 3
      const static byte _lcd_box_top[8] PROGMEM = {
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
      };
      const static byte _lcd_box_bottom[8] PROGMEM = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111
      };
      createChar_P(LCD_UBL_BOXTOP_CHAR, _lcd_box_top);
      createChar_P(LCD_UBL_BOXBOT_CHAR, _lcd_box_bottom);
    #endif
  }
  void lcd_implementation_ubl_plot(const uint8_t x_plot, const uint8_t y_plot) {
    #if LCD_WIDTH >= 20
      #define _LCD_W_POS 12
      #define _PLOT_X 1
      #define _MAP_X 3
      #define _LABEL(C,X,Y) lcd.setCursor(X, Y); lcd.print(C)
      #define _XLABEL(X,Y) _LABEL("X:",X,Y)
      #define _YLABEL(X,Y) _LABEL("Y:",X,Y)
      #define _ZLABEL(X,Y) _LABEL("Z:",X,Y)
    #else
      #define _LCD_W_POS 8
      #define _PLOT_X 0
      #define _MAP_X 1
      #define _LABEL(X,Y,C) lcd.setCursor(X, Y); lcd.write(C)
      #define _XLABEL(X,Y) _LABEL('X',X,Y)
      #define _YLABEL(X,Y) _LABEL('Y',X,Y)
      #define _ZLABEL(X,Y) _LABEL('Z',X,Y)
    #endif
    #if LCD_HEIGHT <= 3   
      _XLABEL(_PLOT_X, 0);
      lcd.print(ftostr32(LOGICAL_X_POSITION(pgm_read_float(&ubl._mesh_index_to_xpos[x_plot]))));
      _YLABEL(_LCD_W_POS, 0);
      lcd.print(ftostr32(LOGICAL_Y_POSITION(pgm_read_float(&ubl._mesh_index_to_ypos[y_plot]))));
      lcd.setCursor(_PLOT_X, 0);
    #else                 
      uint8_t m;
      lcd.setCursor(_MAP_X, 0); for (m = 0; m < 5; m++) lcd.write(LCD_UBL_BOXTOP_CHAR); 
      lcd.setCursor(_MAP_X, 3); for (m = 0; m < 5; m++) lcd.write(LCD_UBL_BOXBOT_CHAR); 
      for (m = 0; m <= 3; m++) {
        lcd.setCursor(2, m); lcd.write('|'); 
        lcd.setCursor(8, m); lcd.write('|'); 
      }
      lcd.setCursor(_LCD_W_POS, 0);
    #endif
    lcd.write('(');
    lcd.print(x_plot);
    lcd.write(',');
    lcd.print(y_plot);
    lcd.write(')');
    #if LCD_HEIGHT <= 3   
      _ZLABEL(_LCD_W_POS, 1);
      if (!isnan(ubl.z_values[x_plot][y_plot]))
        lcd.print(ftostr43sign(ubl.z_values[x_plot][y_plot]));
      else
        lcd_printPGM(PSTR(" -----"));
    #else                 
      _XLABEL(_LCD_W_POS, 1);
      lcd.print(ftostr32(LOGICAL_X_POSITION(pgm_read_float(&ubl._mesh_index_to_xpos[x_plot]))));
      _YLABEL(_LCD_W_POS, 2);
      lcd.print(ftostr32(LOGICAL_Y_POSITION(pgm_read_float(&ubl._mesh_index_to_ypos[y_plot]))));
      _ZLABEL(_LCD_W_POS, 3);
      if (!isnan(ubl.z_values[x_plot][y_plot]))
        lcd.print(ftostr43sign(ubl.z_values[x_plot][y_plot]));
      else
        lcd_printPGM(PSTR(" -----"));
    #endif 
  }
#endif 
#endif 
