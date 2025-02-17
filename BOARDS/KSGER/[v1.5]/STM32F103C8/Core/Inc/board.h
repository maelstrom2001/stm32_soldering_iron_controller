
#ifndef SETUP_H_
#define SETUP_H_
/*
 * Setup.h file
*/

/*
    BOARD PROFILE FOR KSGER v1.5
*/

#define HWSTRING "HW: KSGER v1.5"

/********************************
 *       Display Settings    *
 ********************************/
#define OLED_SPI                                              // SPI display
//#define OLED_I2C                                            // I2C display
//#define I2C_TRY_HW                                          // Try I2C HW first, use I2C SW if not detected
//#define OLED_ADDRESS      (0x3c<<1)                         // Only used for i2c
#define OLED_DEVICE         hspi1                             // SPI / I2C handler if used. Enables HW mode, otherwise SW mode is used
#define FILL_DMA            hdma_memtomem_dma1_channel2       // DMA mem2mem for filling
#define USE_RST                                               // Reset pin is used
#define USE_DC                                                // DC pin is used
#define USE_CS                                                // CS pin is used


/********************************
 *       PWM Settings        *
 ********************************/
//#define PWM_TIMER_HALFCLOCK                                 // Timer runs at FCY/2
//#define READ_TIMER_HALFCLOCK                                // Timer runs at FCY/2
#define READ_TIMER          htim3                             // Timer for the dead time
#define PWM_TIMER           htim4                             // PWM Timer
#define PWM_CHANNEL         TIM_CHANNEL_3                     // PWM Timer Channel
//#define PWM_CHxN                                            // Using CHxN Output type
#define PWM_CHx                                               // Using CHx Output type
//#define DEBUG_PWM                                           // To enable a test signal and some printing through SWO (Create a output GPIO called PWM_DBG)


/********************************
 *       ADC Settings        *
 ********************************/
#define ADC_DEVICE          hadc1                             // ADC device
#define ADC_BFSIZ           (16+2)                            // ADC DMA buffer size Buffer[ADC_BFSIZ][Adc_Buffer_Elements](+2 to compensate min/max value discard in filtering)

// Order for secondary measurements, ADC channels not requiring sampling in the PWM low period. Order as ADC rank order (usually ch0-ch18)
#define ADC_1st             TIP                               // ADC 1st used channel (CH1)
#define ADC_2nd             NTC                               // ADC 2nd used channel (CH3)
#define ADC_3rd             VIN                               // ADC 3nd used channel (CH4)
//#define ADC_4th           ---                               // ADC 4th used channel
#define ADC_Num             3                                 // Number of channels

// Channel assignment
#define ADC_CH_1ST          ADC_CHANNEL_1                     // CH1 = IRON TIP
#define ADC_CH_2ND          ADC_CHANNEL_3                     // CH3 = NTC
#define ADC_CH_3RD          ADC_CHANNEL_4                     // CH4 = VIN
//#define ADC_CH_4TH        ADC_CHANNEL__                     //

// To enable specific functions in code
//#define USE_VREF
#define USE_VIN
#define USE_NTC


/********************************
 *       TIP calibration    *
 ********************************/
//#define PROFILE_VALUES                                        // Enable profile values

#ifdef PROFILE_VALUES
#define T12_Cal250        1100
#define T12_Cal350        1200
#define T12_Cal450        1300

#define C210_Cal250       300
#define C210_Cal350       400
#define C210_Cal450       500

#define C245_Cal250       900
#define C245_Cal350       1000
#define C245_Cal450       1100

#endif


/********************************
 *       Buzzer        *
 ********************************/
#define BUZZER_ON           HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET)
#define BUZZER_OFF          HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET)
#define BUZZER_TOGGLE       HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin)


/********************************
 *       Misc    *
 ********************************/
#define FLASH_SZ            64                                // Flash Size (KB)
//#define NOSAVESETTINGS                                      // Don't use flash to save or load settings. Always use defaults (for debugging purposes)
//#define SWO_PRINT                                           // To enable printing through SWO


/********************************
 *       NTC TABLE      *
 ********************************/
/*
  Table of ADC sum value, corresponding to temperature. Starting from higher value to lower.
  Next parameters had been used to build table:
  R1: 10K pullup to 3.3V
  R/T characteristics table used: EPCOS R/T:7003; B25/100:3625K
  In the temperature range from -20°C to 125°C the error caused by the usage of a table is 0.135°C

  This must be adjusted if the board uses different circuit

  Source: http://www.sebulli.com/ntc/index.php
*/
#ifdef USE_NTC
#define NTC_TABLE   NTC_Table[257] = {                                                                    \
  3525, 2945, 2365, 2077, 1891, 1755, 1650, 1565, 1493, 1431, 1377, 1330, 1287, 1248, 1213, 1181,         \
  1151, 1123, 1097, 1072, 1050, 1028, 1007, 988, 969, 952, 935, 919, 903, 888, 874, 860,                  \
  847, 834, 821, 809, 797, 786, 775, 764, 754, 743, 733, 724, 714, 705, 696, 687,                         \
  678, 670, 662, 653, 645, 638, 630, 622, 615, 608, 601, 593, 587, 580, 573, 566,                         \
  560, 553, 547, 541, 535, 528, 522, 516, 511, 505, 499, 493, 488, 482, 477, 471,                         \
  466, 461, 455, 450, 445, 440, 435, 430, 425, 420, 415, 410, 405, 401, 396, 391,                         \
  386, 382, 377, 373, 368, 364, 359, 355, 350, 346, 341, 337, 333, 328, 324, 320,                         \
  316, 311, 307, 303, 299, 295, 291, 286, 282, 278, 274, 270, 266, 262, 258, 254,                         \
  250, 246, 242, 238, 234, 230, 226, 222, 218, 214, 211, 207, 203, 199, 195, 191,                         \
  187, 183, 179, 176, 172, 168, 164, 160, 156, 152, 148, 144, 141, 137, 133, 129,                         \
  125, 121, 117, 113, 109, 105, 101, 97, 93, 90, 86, 82, 78, 73, 69, 65,                                  \
  61, 57, 53, 49, 45, 41, 37, 32, 28, 24, 20, 15, 11, 7, 2, -2,                                           \
  -6, -11, -15, -20, -25, -29, -34, -38, -43, -48, -53, -58, -63, -68, -73, -78,                          \
  -83, -88, -93, -99, -104, -109, -115, -121, -126, -132, -138, -144, -150, -157, -163, -169,             \
  -176, -183, -190, -197, -204, -212, -219, -227, -235, -244, -252, -261, -270, -280, -290, -301,         \
  -311, -323, -335, -348, -362, -376, -392, -409, -428, -449, -472, -499, -531, -571, -624, -710, -796 };

#endif

// To stop peripherals when debugging
#define DebugOpts()         __HAL_DBGMCU_FREEZE_IWDG(); \
                            __HAL_DBGMCU_FREEZE_TIM3(); \
                            __HAL_DBGMCU_FREEZE_TIM4()

#endif
