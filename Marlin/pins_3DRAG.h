#ifndef BOARD_NAME
  #define BOARD_NAME "3Drag"
#endif
#ifndef DEFAULT_MACHINE_NAME
  #define DEFAULT_MACHINE_NAME "3Drag"
#endif
#ifndef DEFAULT_SOURCE_CODE_URL
  #define DEFAULT_SOURCE_CODE_URL "http://3dprint.elettronicain.it/"
#endif
//
// Heaters / Fans
//
#define RAMPS_D8_PIN 9
#define RAMPS_D9_PIN 8
#define MOSFET_D_PIN 12
#define CASE_LIGHT_PIN -1     // MUST BE HARDWARE PWM but one is not available on expansion header
#include "pins_RAMPS.h"
//
// Limit Switches
//
#undef Z_MAX_PIN
#define Z_MAX_PIN          -1
//
// Steppers
//
#undef Z_ENABLE_PIN
#define Z_ENABLE_PIN       63
//
// Heaters / Fans
//
#define HEATER_2_PIN        6
//
// Misc. Functions
//
#undef SDSS
#define SDSS               25
#undef SD_DETECT_PIN
#define SD_DETECT_PIN      53
//
// LCD / Controller
//
#if ENABLED(ULTRA_LCD) && ENABLED(NEWPANEL)
  #undef BEEPER_PIN
  #define BEEPER_PIN       -1
  #undef LCD_PINS_RS
  #undef LCD_PINS_ENABLE
  #undef LCD_PINS_D4
  #undef LCD_PINS_D5
  #undef LCD_PINS_D6
  #undef LCD_PINS_D7
  #define LCD_PINS_RS      27
  #define LCD_PINS_ENABLE  29
  #define LCD_PINS_D4      37
  #define LCD_PINS_D5      35
  #define LCD_PINS_D6      33
  #define LCD_PINS_D7      31
  // Buttons
  #undef BTN_EN1
  #undef BTN_EN2
  #undef BTN_ENC
  #define BTN_EN1          16
  #define BTN_EN2          17
  #define BTN_ENC          23
#else
  #define BEEPER_PIN       33
#endif // ULTRA_LCD && NEWPANEL
/**
 *  M3/M4/M5 - Spindle/Laser Control
 *
 *  If you want to control the speed of your spindle then you'll have
 *  have to sacrifce the Extruder and pull some signals off the Z stepper
 *  driver socket.
 *
 *  The following assumes:
 *   - the Z stepper driver socket is empty
 *   - the extruder driver socket has a driver board plugged into it
 *   - the Z stepper wires are attached the the extruder connector
 *
 *  If you want to keep the extruder AND don't have a LCD display then
 *  you can still control the power on/off and spindle direction.
 *
 *  Where to get spindle signals
 *
 *      stepper signal           socket name       socket name
 *                                          -------
 *       SPINDLE_LASER_ENABLE_PIN /ENABLE  O|     |O  VMOT
 *                                    MS1  O|     |O  GND
 *                                    MS2  O|     |O  2B
 *                                    MS3  O|     |O  2A
 *                                 /RESET  O|     |O  1A
 *                                 /SLEEP  O|     |O  1B
 *          SPINDLE_LASER_PWM_PIN    STEP  O|     |O  VDD
 *                SPINDLE_DIR_PIN     DIR  O|     |O  GND
 *                                          -------
 *
 *  Note: Socket names vary from vendor to vendor
 */
#undef SPINDLE_LASER_PWM_PIN    // Definitions in pins_RAMPS.h are not good with 3DRAG
#undef SPINDLE_LASER_ENABLE_PIN
#undef SPINDLE_DIR_PIN
#if ENABLED(SPINDLE_LASER_ENABLE)
  #if !EXTRUDERS
    #undef E0_DIR_PIN
    #undef E0_ENABLE_PIN
    #undef E0_STEP_PIN
    #undef Z_DIR_PIN
    #undef Z_ENABLE_PIN
    #undef Z_STEP_PIN
    #define Z_DIR_PIN                28
    #define Z_ENABLE_PIN             24
    #define Z_STEP_PIN               26
    #define SPINDLE_LASER_PWM_PIN    46  // MUST BE HARDWARE PWM
    #define SPINDLE_LASER_ENABLE_PIN 62  // Pin should have a pullup!
    #define SPINDLE_DIR_PIN          48
  #elif !(ENABLED(ULTRA_LCD) && ENABLED(NEWPANEL)) 
    #define SPINDLE_LASER_ENABLE_PIN 16  
    #define SPINDLE_DIR_PIN          17
  #endif
#endif