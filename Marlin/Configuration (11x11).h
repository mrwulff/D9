#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#define CONFIGURATION_H_VERSION 010100
#define WANHAO_ONEPLUS_201707VAR        1  
#define WANHAO_MELZI_201707VAR          2  
#define WANHAO_UTIMAKER_201705VAR       3  
#define WANHAO_UTIMAKER_201711VAR       4  
#define I3PLUS_201705VAR                5  
#define I3PLUS_201710VAR                6  
#define MINIRAMBO_VAR                   7  
#define MEGATRONICS_TEST                8  
#define MKS_BASE_NewArea                9  
#define MKS_BASE_LMYSTAR                10 
#define DINGYINGFENG_DY_H9              11 
#define MKS_BASE_BlueModel              12 
#define MKS_BASE_NewFuture              13 
#define ONEPLUS_GOOFOO                  14 
#define DINGYINGFENG_DY_H10             15 
#define MEGATRONICS3_DULX               16 
#define FLYING_BEAR                     17 
#define WANHAO_D9_201804VER             18 
#define TRONXY_X3                       19
#define NEW_FUNCTION_yszTEST            99 
#ifndef CLIENT_VAR
#define   CLIENT_VAR  WANHAO_D9_201804VER
#endif
#ifndef MOTHERBOARD
#define MOTHERBOARD BOARD_I3PLUS3030
#endif
#define MOTHERBOARD BOARD_I3PLUS3030
#define DISABLED_SERIAL_RXISR   2
#define mySERIAL_Nums   1
#define mySERIAL_Array 0
#define mySERIAL_Bauderate 115200
#define mySERIAL_PublicCOM  true
#define mySERIAL_gcodeCmd   true
#define MACRO_var_V010
#define MACRO_var_V00F
#define STRING_VERSION_CONFIG_H __DATE__ " " __TIME__  
#define STRING_CONFIG_H_AUTHOR "(none, default config)" 
#define SHOW_BOOTSCREEN
#define STRING_SPLASH_LINE1 "" 
#define STRING_SPLASH_LINE2 ""
#ifndef mySERIAL_Nums
#define SERIAL_PORT 0
#endif
#ifndef mySERIAL_Nums
#define BAUDRATE 115200
#endif
#define CUSTOM_MACHINE_NAME "I3PLUS"
#define EXTRUDERS 1
#if ENABLED(MK2_MULTIPLEXER)
#endif
#if ENABLED(SWITCHING_EXTRUDER)
  #define SWITCHING_EXTRUDER_SERVO_NR 0
  #define SWITCHING_EXTRUDER_SERVO_ANGLES { 0, 90 } 
  #if EXTRUDERS > 3
    #define SWITCHING_EXTRUDER_E23_SERVO_NR 1
  #endif
#endif
#if ENABLED(SWITCHING_NOZZLE)
  #define SWITCHING_NOZZLE_SERVO_NR 0
  #define SWITCHING_NOZZLE_SERVO_ANGLES { 0, 90 }   
#endif
#if ENABLED(MIXING_EXTRUDER)
  #define MIXING_STEPPERS 2        
  #define MIXING_VIRTUAL_TOOLS 16  
#endif
#define BREAK_Z_UNMOVE
#define POWER_SUPPLY 0
#if POWER_SUPPLY > 0
#endif
#define TEMP_SENSOR_0 1
#define TEMP_SENSOR_1 0
#define TEMP_SENSOR_2 0
#define TEMP_SENSOR_3 0
#define TEMP_SENSOR_4 0
#define TEMP_SENSOR_BED 1
#define DUMMY_THERMISTOR_998_VALUE 25
#define DUMMY_THERMISTOR_999_VALUE 100
#define MAX_REDUNDANT_TEMP_SENSOR_DIFF 10
#define TEMP_RESIDENCY_TIME 10  
#define TEMP_HYSTERESIS 5       
#define TEMP_WINDOW     1       
#define TEMP_BED_RESIDENCY_TIME 10  
#define TEMP_BED_HYSTERESIS 3       
#define TEMP_BED_WINDOW     1       
#define HEATER_0_MINTEMP -5
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_3_MINTEMP 5
#define HEATER_4_MINTEMP 5
#define BED_MINTEMP -5
#define HEATER_0_MAXTEMP 315
#define HEATER_1_MAXTEMP 280
#define HEATER_2_MAXTEMP 280
#define HEATER_3_MAXTEMP 280
#define HEATER_4_MAXTEMP 280
#define BED_MAXTEMP 115
#define PIDTEMP
#define BANG_MAX 255 
#define PID_MAX BANG_MAX 
#if ENABLED(PIDTEMP)
    #ifdef CLIENT_VAR
        #define PID_FUNCTIONAL_RANGE 20 
    #else 
        #define PID_FUNCTIONAL_RANGE 20 
    #endif
    #define K1 0.95 
#define  DEFAULT_Kp 33.41
#define  DEFAULT_Ki 1.47
#define  DEFAULT_Kd 189.27
#endif 
#define MAX_BED_POWER 255 
#if ENABLED(PIDTEMPBED)
  #define  DEFAULT_bedKp 10.00
  #define  DEFAULT_bedKi .023
  #define  DEFAULT_bedKd 305.4
#endif 
#ifdef CLIENT_VAR
#else
#define PREVENT_COLD_EXTRUSION
#endif
#define EXTRUDE_MINTEMP 170
#define PREVENT_LENGTHY_EXTRUDE
#define EXTRUDE_MAXLENGTH   200
#define THERMAL_PROTECTION_HOTENDS 
#define THERMAL_PROTECTION_BED     
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG
#define ENDSTOPPULLUPS 
#if DISABLED(ENDSTOPPULLUPS)
#endif
#define X_MIN_ENDSTOP_INVERTING true 
#define Y_MIN_ENDSTOP_INVERTING true 
#define Z_MIN_ENDSTOP_INVERTING true 
#define X_MAX_ENDSTOP_INVERTING true 
#define Y_MAX_ENDSTOP_INVERTING true 
#define Z_MAX_ENDSTOP_INVERTING true 
#define Z_MIN_PROBE_ENDSTOP_INVERTING true 
#define DEFAULT_AXIS_STEPS_PER_UNIT   {81,81,400.5,94.3}
#define DEFAULT_MAX_FEEDRATE          { 300, 300, 5, 25 }
#define DEFAULT_MAX_ACCELERATION      {500,500,100,500}
#define DEFAULT_ACCELERATION          500    
#define DEFAULT_RETRACT_ACCELERATION  800    
#define DEFAULT_TRAVEL_ACCELERATION   500    
#define DEFAULT_XJERK                 10.0
#define DEFAULT_YJERK                 10.0
#define DEFAULT_ZJERK                  0.4
#define DEFAULT_EJERK                  1.0
#define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
#define FIX_MOUNTED_PROBE
#if ENABLED(BLTOUCH)
#endif
#define X_PROBE_OFFSET_FROM_EXTRUDER 15
#define Y_PROBE_OFFSET_FROM_EXTRUDER 0
#define Z_PROBE_OFFSET_FROM_EXTRUDER 0 
#define XY_PROBE_SPEED 8000
#define Z_PROBE_SPEED_FAST HOMING_FEEDRATE_Z
#define Z_PROBE_SPEED_SLOW (Z_PROBE_SPEED_FAST / 2)
#define Z_CLEARANCE_BETWEEN_PROBES  4
#define Z_CLEARANCE_DEPLOY_PROBE    4
#define Z_PROBE_OFFSET_RANGE_MIN -20
#define Z_PROBE_OFFSET_RANGE_MAX 20
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0 
#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z false
#define DISABLE_E false 
#define DISABLE_INACTIVE_EXTRUDER true 
#define INVERT_X_DIR true
#define INVERT_Y_DIR false 
#define INVERT_Z_DIR false
#define INVERT_E0_DIR false
#define INVERT_E1_DIR false
#define INVERT_E2_DIR false
#define INVERT_E3_DIR false
#define INVERT_E4_DIR false
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#define X_MAX_POS 300
#define Y_MAX_POS 300
#define Z_MAX_POS 400
#define MIN_SOFTWARE_ENDSTOPS
#define MAX_SOFTWARE_ENDSTOPS
#if ENABLED(FILAMENT_RUNOUT_SENSOR) 
#endif
#if ENABLED(FILAMENT_RUNOUT_SENSOR)
    #define FIL_RUNOUT_INVERTING false 
  #define ENDSTOPPULLUP_FIL_RUNOUT 
  #define FILAMENT_RUNOUT_SCRIPT "M600"
#endif
  #define AUTO_BED_LEVELING_BILINEAR
  #define MESH_INSET 10 
#if ENABLED(MESH_BED_LEVELING) || ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(AUTO_BED_LEVELING_UBL)
#endif
#if ENABLED(AUTO_BED_LEVELING_LINEAR) || ENABLED(AUTO_BED_LEVELING_BILINEAR)
  #ifdef CLIENT_VAR
    #define GRID_MAX_POINTS_X 11 
    #define GRID_MAX_POINTS_Y 5 
    #define LEFT_PROBE_BED_POSITION (MIN_PROBE_X+MESH_INSET) 
    #define RIGHT_PROBE_BED_POSITION (MAX_PROBE_X-MESH_INSET)
    #define FRONT_PROBE_BED_POSITION (MIN_PROBE_Y+MESH_INSET)
    #define BACK_PROBE_BED_POSITION (MAX_PROBE_Y-MESH_INSET)
  #else 
    #define GRID_MAX_POINTS_X 11 
    #define GRID_MAX_POINTS_Y 5 
    #define LEFT_PROBE_BED_POSITION 15
    #define RIGHT_PROBE_BED_POSITION 170
    #define FRONT_PROBE_BED_POSITION 20
    #define BACK_PROBE_BED_POSITION 170
  #endif
  #define MIN_PROBE_EDGE 10
  #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
    #if ENABLED(ABL_BILINEAR_SUBDIVISION)
      #define BILINEAR_SUBDIVISIONS 3
    #endif
  #endif
#elif ENABLED(AUTO_BED_LEVELING_3POINT)
  #define ABL_PROBE_PT_1_X 15
  #define ABL_PROBE_PT_1_Y 180
  #define ABL_PROBE_PT_2_X 15
  #define ABL_PROBE_PT_2_Y 20
  #define ABL_PROBE_PT_3_X 170
  #define ABL_PROBE_PT_3_Y 20
#elif ENABLED(AUTO_BED_LEVELING_UBL)
  #define UBL_MESH_INSET 1          
  #define GRID_MAX_POINTS_X 3      
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X
  #define UBL_PROBE_PT_1_X 39       
  #define UBL_PROBE_PT_1_Y 180
  #define UBL_PROBE_PT_2_X 39
  #define UBL_PROBE_PT_2_Y 20
  #define UBL_PROBE_PT_3_X 180
  #define UBL_PROBE_PT_3_Y 20
  #define UBL_G26_MESH_VALIDATION   
  #define UBL_MESH_EDIT_MOVES_Z     
#elif ENABLED(MESH_BED_LEVELING)
  #define MESH_INSET 20          
  #define GRID_MAX_POINTS_X 2
  #define GRID_MAX_POINTS_Y GRID_MAX_POINTS_X
#endif 
#if ENABLED(LCD_BED_LEVELING)
    #define MBL_Z_STEP 0.025    
    #define LCD_PROBE_Z_RANGE 4 
#endif
#if ENABLED(Z_SAFE_HOMING)
  #define Z_SAFE_HOMING_X_POINT ((X_MIN_POS + X_MAX_POS) / 2)    
  #define Z_SAFE_HOMING_Y_POINT ((Y_MIN_POS + Y_MAX_POS) / 2)    
#endif
#define HOMING_FEEDRATE_XY (60*60) 
#define HOMING_FEEDRATE_Z  (40*60)
#define EEPROM_SETTINGS 
#define EEPROM_CHITCHAT   
#define HOST_KEEPALIVE_FEATURE        
#define DEFAULT_KEEPALIVE_INTERVAL 2  
#define PREHEAT_1_TEMP_HOTEND 200
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_FAN_SPEED     0 
#define PREHEAT_2_TEMP_HOTEND 240
#define PREHEAT_2_TEMP_BED    80
#define PREHEAT_2_FAN_SPEED     0 
#if ENABLED(NOZZLE_PARK_FEATURE)
  #define NOZZLE_PARK_POINT { (X_MIN_POS + 10), (Y_MAX_POS - 10), 20 }
#endif
#if ENABLED(NOZZLE_CLEAN_FEATURE)
  #define NOZZLE_CLEAN_STROKES  12
  #define NOZZLE_CLEAN_TRIANGLES  3
  #define NOZZLE_CLEAN_START_POINT { 30, 30, (Z_MIN_POS + 1)}
  #define NOZZLE_CLEAN_END_POINT   {100, 60, (Z_MIN_POS + 1)}
  #define NOZZLE_CLEAN_CIRCLE_RADIUS 6.5
  #define NOZZLE_CLEAN_CIRCLE_FN 10
  #define NOZZLE_CLEAN_CIRCLE_MIDDLE NOZZLE_CLEAN_START_POINT
  #define NOZZLE_CLEAN_GOBACK
#endif
#ifndef CLIENT_VAR
#define PRINTJOB_TIMER_AUTOSTART
#endif
#define LCD_LANGUAGE en
#define DISPLAY_CHARSET_HD44780 JAPANESE
#ifdef CLIENT_VAR
#define SDSUPPORT
#else 
#endif
#define FYSTLCD_V1 
#if ENABLED(SAV_3DGLCD)
  #define U8GLIB_SH1106
#endif
#define SOFT_PWM_SCALE 0
#if ENABLED(RGB_LED) || ENABLED(RGBW_LED)
  #define RGB_LED_R_PIN 34
  #define RGB_LED_G_PIN 43
  #define RGB_LED_B_PIN 35
  #define RGB_LED_W_PIN -1
#endif
#if ENABLED(BLINKM) || ENABLED(RGB_LED) || ENABLED(RGBW_LED) || ENABLED(PCA9632)
  #define PRINTER_EVENT_LEDS
#endif
#define SERVO_DELAY 300
#define DEFAULT_NOMINAL_FILAMENT_DIA 3.00   
#if ENABLED(FILAMENT_WIDTH_SENSOR)
  #define FILAMENT_SENSOR_EXTRUDER_NUM 0    
  #define MEASUREMENT_DELAY_CM        14    
  #define MEASURED_UPPER_LIMIT         3.30 
  #define MEASURED_LOWER_LIMIT         1.90 
  #define MAX_MEASUREMENT_DELAY       20    
  #define DEFAULT_MEASURED_FILAMENT_DIA DEFAULT_NOMINAL_FILAMENT_DIA 
#endif
#endif 
