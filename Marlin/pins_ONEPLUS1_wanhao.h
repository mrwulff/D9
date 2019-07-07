#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu.
#endif
#define LARGE_FLASH true
#ifdef IS_RAMPS_13
#define SERVO0_PIN        7 
#else
#define SERVO0_PIN       11
#endif
#define SERVO1_PIN          6
#define SERVO2_PIN          5
#define SERVO3_PIN          4
#define X_STEP_PIN         22
#define X_DIR_PIN          23
#define X_ENABLE_PIN       57
#define X_MIN_PIN          19
#define Y_STEP_PIN         25
#define Y_DIR_PIN          26
#define Y_ENABLE_PIN       24
#define Y_MIN_PIN          18
#define Z_STEP_PIN         29
#define Z_DIR_PIN          39
#define Z_ENABLE_PIN       28
#define Z_MIN_PIN          38
#define E0_STEP_PIN        55
#define E0_DIR_PIN         56
#define E0_ENABLE_PIN      54
#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13
#define HEATER_0_PIN      4
#define HEATER_BED_PIN    44    
#define TEMP_0_PIN        13   
#define TEMP_BED_PIN      14   
#define FAN_PIN           12 
#define BEEPER_PIN 37
#define DOGLCD_A0  40
#define DOGLCD_CS  41
#define LCD_BACKLIGHT_PIN 65 
#define LCD_RESET_PIN  27
#define SDSS   53
#define KILL_PIN 64
#define LCD_CONTRAST 200
#define BTN_EN1 2
#define BTN_EN2 3
#define BTN_ENC 5  
#define     SD_DETECT_BYMYSELF
#define     SD_DETECT_PIN_INIT  DDRD &= ~_BV(PIND6)
#define     SD_DETECT_SET(x)    if(x)PORTD|=_BV(PIND6);else PORTD&=~_BV(PIND6)
#define     SD_DETECT_PIN_VAL   (!(bool)(PIND&_BV(PIND6)))
#define BEEPER_PIN 37
