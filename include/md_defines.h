#ifndef _MD_DEFINES_H_
  #define _MD_DEFINES_H_

  #ifndef CFG_DEFS
    #define CFG_DEFS
    // **********************************************
    // --- generic constants
      #define NN      -1  // undefined
      #define NU      -1  // not used
      #define NC      -1  // not connected
      #define OFF      0  // not active
      #define ON       1  // active

      #define TRUE     1
      #define FALSE    0

      #define ISERR   TRUE   // function call
      #define ISOK    FALSE

      #define FIRST   TRUE   // function call
      #define LAST    FALSE

      #define SWITCH  TRUE

      #define CR   13 // carrige return
      #define LF   10 // line feed
      #define LN   LF
      #define U3V3  3
      #define U5V   5

      #define NOKEY 0

      #define UTC_TIMEZONE      3600           // +1 hour
      #define UTC_SUMMERTIME    1
      #define UTC_WINTERTIME    0

      #define DEBUG   TRUE
      #define NODEBUG FALSE

      #define CFG_DEBUG_NONE    0
      #define CFG_DEBUG_STARTUP 1
      #define CFG_DEBUG_ACTIONS 2
      #define CFG_DEBUG_DETAILS 3
    //
    // **********************************************
    // --- macros
      #define SET(b)      (b = true)
      #define RESET(b)    (b = false)

      #define SOUT(c)     (Serial.print(c))
      #define SOUTHEX(c)  (Serial.print(c, HEX))
      #define SOUTLN(c)   (Serial.println(c))
      #define SOUTHEXLN(c)(Serial.println(c, HEX))
    //
    // **********************************************
    // --- internal coding of HW defines
      //--------------------------------------------
      // --- MC_: 16 bit coded numbering of controller and periferal boards
        //bin xx xxxx xxxxxx xxxx
        //    || |||| |||||| ++++ individual number (type spezific)
        //    || |||| |||||| ---- module type
        //    || |||| |||||+ user output (optical, acustic)
        //    || |||| ||||+  user input  (grafical/text, acustic, keys)
        //    || |||| |||+   periferal input  (sensor)
        //    || |||| ||+    periferal output (relay)
        //    || |||| |+     system / interface
        //    || |||| +      reserved
        //    || |||| ---- controller family
        //    || |||+ STM32
        //    || ||+  ESP32
        //    || |+   ESP8266
        //    || +    Arduino
        //    || ---- voltage used
        //    |+ 5 V
        //    +  3.3 V

      //
      // --- voltage defines
        #define  MC_PW_3V3   0x8000
        #define  MC_PW_5V    0x4000
        #define  MC_PW       0xa000 // mask for voltage

      //
      // --- controller types
        #define  MC_UC_AV       0x2000 // arduino
        #define  MC_UC_ESP8266  0x1000 // ESP8266
        #define  MC_UC_ESP32    0x0800 // ESP32
        #define  MC_UC_STM      0x0400 // STM32
        #define  MC_UC          0x3c00 // mask for 'is controller

      //
      // --- module types
        #define MC_MOD_RES      0x0200 // reserved
        #define MC_MOD_SYS      0x0100 // system internal or interface
        #define MC_MOD_POUT     0x0080 // periferal output
        #define MC_MOD_PIN      0x0040 // periferal input
        #define MC_MOD_UOUT     0x0020 // user output
        #define MC_MOD_UIN      0x0010 // user input

      //
      // --- controller boards
        // --- arduino boards
          #define  MC_AV_NANO_V3    0x0003 + MC_PW_5V + MC_UC_AV
          #define  MC_AV_UNO_V3     0x0007 + MC_PW_5V + MC_UC_AV
          #define  MC_AV_MEGA_V3    0x000f + MC_PW_5V + MC_UC_AV
        //
        // --- ESP32 boards
          #define  MC_ESP_DUAL      0x0008 // dual core controller
          #define  MC_ESP32S_Node   0x0000 +               MC_PW_3V3 + MC_UC_ESP32 + MC_MOD_SYS
          #define  MC_ESP32_Node    0x0001 + MC_ESP_DUAL + MC_PW_3V3 + MC_UC_ESP32 + MC_MOD_SYS
          #define  MC_ESP32_D1_R32  0x0002 +               MC_PW_3V3 + MC_UC_ESP32 + MC_MOD_SYS
          #define  MC_ESP32_LORA    0x0003 + MC_ESP_DUAL + MC_PW_3V3 + MC_UC_ESP32 + MC_MOD_SYS
      //
      // --- displays
        // --- TFT displays
          #define  MC_UO_TFT1602_IIC_XA   0x0000 + MC_MOD_UOUT + MC_PW_3V3
          #define  MC_UO_TFT1602_GPIO_RO  0x0001 + MC_MOD_UOUT + MC_PW_3V3 + MC_PW_5V  // used by KEYPADSHIELD
          #define  MC_UO_TOUCHXPT2046_AZ  0x0002 + MC_MOD_UOUT + MC_PW_3V3 // used by Arduino-touch-case
        //
        // --- OLED displays
          #define  MC_UO_OLED_091_AZ      0x0008 + MC_MOD_UOUT + MC_PW_3V3 // IIC adress 0x3C
            #define OLED_091_MAXCOLS      20
            #define OLED_091_MAXROWS      4

          #define  MC_UO_OLED_096_AZ      0x0008 + MC_MOD_UOUT + MC_PW_3V3
            #define OLED_096_MAXCOLS      20
            #define OLED_096_MAXROWS      6

          #define  MC_UO_OLED_130_AZ      0x0008 + MC_MOD_UOUT + MC_PW_3V3
            #define OLED_130_MAXCOLS      20
            #define OLED_130_MAXROWS      6
      //
      // --- user input parts
          #define  MC_UI_Keypad_ANA0_RO   0x0000 + MC_MOD_UIN + MC_PW_3V3 + MC_PW_5V // used by KEYPADSHIELD
          #define  MC_UI_TOUCHXPT2046_AZ  0x0002 + MC_MOD_UIN + MC_PW_3V3  // used by Arduino-touch-case

      //
      // --- active outputs
          #define  AOUT_PAS_BUZZ_3V5V       U_3V5V + 0  // used by Arduino-touch-case

    //
    // **********************************************
    // --- configuration and HW spezific defines
      // --- I2C devices
          #define  I2C1                     1           // I2C device 1
          #define  I2C2                     2           // I2C device 2
          #define  I2C_TFT1602_IIC_XA_3V3   U_3V3  + 0
          #define  I2C_OLED                 0x3C
          #define  I2C_FRAM                 0x50
          #define  I2C_BME280               0x76
          #define  I2C_FRAM_ALT             0x7C
          #define  I2C_DEV_NN               0xFF
      //
      // --- music defines
        //
        // --- structures
          typedef struct {
            int8_t   note;     // NOTE_C .. NOTE_B
            int8_t   octa;     // oktave 0 .. 7
            uint64_t beat;     // MB1 = base
          } tone_t;
        //
        // --- music units
          //
          // --- beat units --------------------
            #define MUSIC_BASEBEAT_US       250000ul  // base beat of 1/4 note = 250 ms
            #define MUSIC_RATIO_P100        80          // 80% ON / 20% OFF
            #define MB44  MUSIC_BASEBEAT_US * 4  // 4/4
            #define MB43  MUSIC_BASEBEAT_US * 3  // 3/4
            #define MB42  MUSIC_BASEBEAT_US * 2  // 2/4
            #define MB4   MUSIC_BASEBEAT_US * 1  // 1/4 note = basebeat
            #define MB8   MUSIC_BASEBEAT_US / 2  // 1/8
            #define MB16  MUSIC_BASEBEAT_US / 4  // 1/16
            #define MB32  MUSIC_BASEBEAT_US / 8  // 1/32
          //
          // --- octave units ------------------
            #ifndef MUSIC_BASE_OCTA
              #define MUSIC_BASE_OCTA  5
            #endif // MUSIC_BASE_OCTA
            #define ON3   MUSIC_BASE_OCTA + 3  // octave negative 1
            #define ON2   MUSIC_BASE_OCTA + 2  // octave negative 1
            #define ON1   MUSIC_BASE_OCTA + 1  // octave negative 1
            #define OP0   MUSIC_BASE_OCTA      // (base-) octave positiv 0
            #define OP1   MUSIC_BASE_OCTA - 1  // octave positiv 1
            #define OP2   MUSIC_BASE_OCTA - 2  // octave positiv 1
            #define OP3   MUSIC_BASE_OCTA - 3  // octave positiv 1
            #define OP4   MUSIC_BASE_OCTA - 4  // octave positiv 1
          //
          // --- notes -------------------------
            #define PAUSE   -1
          //
        //
        // --- songs
    	    #define SONG_HAENSCHEN_KLEIN  0
            const uint64_t SONG0_BEAT_US = MUSIC_BASEBEAT_US;
            const tone_t   SONG0_NOTES[] =
                { // Haenschen klein
                  {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                  {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_C ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },
                  {NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                  {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
                  {NOTE_C ,OP0,MB42},                    { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{NOTE_D ,OP0, MB4 },
                  {NOTE_D ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_F ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_E ,OP0, MB4 },
                  {NOTE_E ,OP0,MB4 },{NOTE_F ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_G ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{ PAUSE ,OP0, MB4 },
                  {NOTE_F ,OP0,MB4 },{NOTE_D ,OP0, MB4 },{NOTE_D ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
                  {NOTE_C ,OP0,MB42},                    { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 }
                };
              const uint16_t SONG0_LEN     = sizeof(SONG0_NOTES)/sizeof(tone_t);    //62;
          #define SONG_ALLE_VOEGLEIN    1
            const uint64_t SONG1_BEAT_US = MUSIC_BASEBEAT_US;
            const tone_t   SONG1_NOTES[] =
                { // Haenschen klein
                  {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_C ,OP1, MB4 },
                  {NOTE_B ,OP0,MB4 },{NOTE_C ,OP1, MB4 },{NOTE_B ,OP0,MB4 },{NOTE_G ,OP0, MB4 },

                  {NOTE_E ,OP0,MB4 },{NOTE_G ,OP0, MB4 },{NOTE_E ,OP0,MB4 },{NOTE_C ,OP0, MB4 },
                  {NOTE_D ,OP0,MB4 },{NOTE_C ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{ PAUSE ,OP0, MB4 },

                  {NOTE_C ,OP0,MB4 },{NOTE_E ,OP0, MB4 },{NOTE_G ,OP0,MB4 },{NOTE_G ,OP0, MB4 },
                  {NOTE_C ,OP0,MB42},                    { PAUSE ,OP0,MB4 },{ PAUSE ,OP0, MB4 }
                };
              const uint16_t SONG1_LEN     = sizeof(SONG1_NOTES)/sizeof(tone_t);    //62;
          //#define SONG_ALLE_ENTCHEN     2
    //
    // **********************************************
  #endif // CFG_DEFS

#endif   // _MD_DEFINES_H_