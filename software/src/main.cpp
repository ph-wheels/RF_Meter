#include <Arduino.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstring>
#include <SPI.h>
#include <stdint.h>
#include <MAX11270.h>
#include <Ticker.h>
#include <Preferences.h>
#include <Clickencoder.h>
#include <main.h>
#include <Menu.h>
#include <TFT_eSPI.h>     // Hardware-specific library for TFT
#include <Free_Fonts.h>
#include "WiFi.h" 
#include <esp_wifi.h>
#include <esp_bt.h>
#include <SerialCommand.h>
#include <ArduinoJson.h>
#include <stdlib.h>

/* Usefull links & software & general info partially used for this application
 * Link to usefull max11214 driver : https://github.com/LucasEtchezuri/Arduino-MAX11214
 * How to flash esp32: https://www.espressif.com/en/support/download/other-toolsS
 * Usefull link on flash usage: https://github.com/espressif/arduino-esp32/blob/
 * https://forum.arduino.cc/t/serial-input-basics-updated/382007/3
 * master/libraries/Preferences/examples/StartCounter/StartCounter.ino
 * Usefull link on TFT usage: https://www.youtube.com/watch?v=rq5yPJbX_uk
 * Usefull link on dual SPI usage: https://github.com/espressif/arduino-esp32/blob/
 * Usefull link on battery capacity level for Li-Ion type 16820: https://www.youtube.com/watch?v=mfiRJ1qgToc
 * master/libraries/SPI/examples/SPI_Multiple_Buses/SPI_Multiple_Buses.ino
 * master/examples/SerialCommandHardwareOnlyExample/SerialCommandHardwareOnlyExample.ino
 * https://www.allaboutcircuits.com/technical-articles/getting-started-with-openocd-using-ft2232h-adapter-for-swd-debugging/
 * Usefull link on https://community.platformio.org/t/debugging-esp32-how/4499
 * Usefull link on Polymomial Regression https://www.statology.org/polynomial-regression-excel/
 * Usefull link on rotary encoder and menu:
 * https://github.com/im-pro-at/ESP32_ReflowOvenController/tree/master/ReflowController
 * potentially patch C:\Users\paul\.platformio\packages => esp32-hal-timer.c -> add volatile keyword to structs
 * for now timer interrupt is set @ 10ms interval
 * an alternative encoder implementation: https://github.com/RalphBDacon/226-Better-Rotary-Encoder---no-switch-bounce
 * /blob/main/YetAnotherRotaryEncoder/YetAnotherRotaryEncoder.ino
 * but it's laking an push button 
 * https://savjee.be/2019/12/esp32-tips-to-increase-battery-life/
 * https://github.com/kroimon/Arduino-SerialCommand/tree/master/examples
 * https://github.com/ppedro74/Arduino-SerialCommands
 * for personal reference only:
 * python  esptool.py --chip esp32 --port com6 erase_flash
 * python  esptool.py --chip esp32 --port com6 --baud 460800 write_flash -z 0x1000 C:\Users\paul\Downloads\esp32-idf3-20191220-v1.12.bin
 * 
 */

/*
 * SW history:
 * 1.5b2  Added internal calibration at startup
 *        added labels for 0 / 1 flags
 * 
 * 1.6b   release for inital test to J.A.
 * 
 * 1.7    release for test based on 3 range setup
 * 
 * 1.8    release for test 3 chan, altered menu
 *        in progress
 *    b3  adding logic as to be able to switch between units
 * 
 * 2.0b1  switched to dual value display, removed menu items, added uW
 *    b2  adjusted chan # from 0-2 to 1-3 & feedback
 *    b3  corrections as per feedback 11-12
 *    b4  enhancement on input termination
 *        corrections as per feedback 15-12
 *        ToDo => alternative method for dBm offset value
 *    b7  changed channel select to A, B, C
 *        added partial coding for B - A
 *    b8  completed B - A/C - A coding, modified selection / menu behaviour
 *        released for test by Jacques.
 *    b9  change as to avoid flickering on battery status update
 * 2.1b1  fixed some issue's on B-A/C-A, introduced dual click and term value
 *    b2  some more issue on dual channel, problems with correct readout of B
 *        send to Jacques for confirmation of either sw or hw problem
 *    b3  replace range 1 constants provided by Jacques
 * 2.2b1  changed adc handling to be interrupt driven as to elliminates delays
 *    b2  adjusted range of scanadc value, min = 100, max 500
 *    b3  finally, finally got the dual chan mode to work, reason wrong update of r_val
 *    b4  added support for second click to zero out B-A / C-A & disabled double click
 *    b5  move refence value r_val[] to global space, fixed A0 table issue
 *    b6  added a NoiseFloor parameter option as be able to stop displaying noise
 * 2.3b1  added attenuator controle
 *    b3  hw change -> changed r29 to 0 Ohm to reduce noise at very low levels
 *        added attenuator value compensation -> measure value * 5 = 14dBm
 *    b4  Updated the TFT_eSPI library as to obtain proper eSprite support
 *        implemented eSprite for Meter area
 *        Improved Helper function to utilize array instead of switch statement
 *    b5  Changed Battery voltage indication to remaining charge percentage
 *        & improved battery symbol
 *        Added bulk data upload routine to init nvs flash (L cmd)
 *    b6  Changed to PGA mode only and Vref to be 1.3 V
 * 
 *    ToDo: Implement usage of Sprite as to reduce screen flickering -> Done
 *          split usage of correction polynome / channel
 *          import option of data file to init flash_nvr for rf-meter
 *          general cleanup & remove unused coding parts
 * 2.4b1  We finally found odd range switching issue and move over to json load
 *        file for polynome values as to allow for more flexibility 
 *    b2  removed * 5 on high level as it will be compensated by polynome
 *    b3  aligned attenuator, so attenuator is enabled over full range 1
 *    b4  reduced spi clk from 20 to 18 MHz
 *    b5  redesign adc sampling to be event drive by interrupt sps 1.9 -> 508 mS
 *    b6  adjusted polynome array's size to be 5 elements, conversion routine will test
 *        for zero values to be skipped, improved flash screen to show proper version
 *        found issue on 13.01 dBm display --> no proper import of polynome jason file.
 *  2.5.0 version naming changed from 2.4b6 to 2.5.0
 *        revised auto_ranging as to deal with multi chan, multi range
 *        dual channel sample delay's been removed, some cleanup unused stuff
 *        naming for channels unified
 *  2.5.1 added test on flash data for polynomial, correctiopn data etc
 *        initial version for test & feedback
 *     .2 scanadc parameter remove as it became obsolete due to interrupt drive adc sampling
 *        renamed 'L' to 'LP' and added the 'LS' option to load Vref and battery ratio and sample rate
 *     .3 fixed range output to serial, added 'Flash Incorrect' notification on display, 
 *        removed dual channel debug messages, improved json load error message
 *     .4 increased serial timeout to 10sec, renamed variable flg / init at setup
 *     .5 Fixed odd behaviour on A0 corrections, re-arranged function requence solved issue
 *        todo -> zero button implementation
 *     .6 fixed issue with INF at startup with low level input (finally found it, value in array not defined !)
 *        added internal cal at startup and scan for average with no input signal
 *     .7 fixed min displayed value to be 30 adc counts, doing average offset for active channel
 *        added missing coding part on monitor output in case of averaging is active
 *     .8 fixed incorrect data issue on serial output, zero duration is now 10 sec, 0.0 is displayed as LOW
 *     .9 could same as .8 which was internal test usage, .9 released for off site tests
 *  2.6.0 added optio to tune # of samples vor zero offset operation
 *     .1 made several changes to the chk_autoRage function which was causing hangs and irratic data to display
 *     .2 removed dummy read delay on B - A / C - A as to speedup readout, seems to work ok.
 *     .3 back to dummy read delay as fast mode  didn't work properly, fixed some issue, startup with gain 1 / att on
 *     .4 adjusted channel selection timing for dual channel mode
 *     .5 corrected the issue of wrongly driving the attenuator
 *     .6 resolved issue of wrongly implementing correction factors over a reboot
 *     .7 forgot to track changes ... and lost them
 *     .8 changed implementation of chk_autorage function but still issue in a/b mode
 *     .9 changed chn_arr_init() to it's function default => lvl 2, att off
 */

#define M_Bar_Gain      25
#define MTR_FONT FSSB24
#define STS_FONT FSS9
#define splash_delay    2000
#define ADC_CLK         18        // ADC SPI pins in use
#define ADC_MISO        19        //
#define ADC_MOSI        23        //
#define ADC_CS          5         //
#define ADC_DRDY        4         // also used forhw interrupt on ADC ready
#define SDA             21        // I2C bus option pins, not used
#define CLK             22        //
#define ADC_SYNC        17        // added, define pin used by adc sync input, should be grounded
#define ADC_PIN         27        // used to measure battery voltage
#define ADC_RESOLUTION  16777215  // 
#define ADC_UNI_MAX     16700100  // used to signal upcoming overload
//#define ATT_HIGH        7334000   // attenuator switch points
//#define ATT_LOW         1312000   //
#define JSON_TIMEOUT  10000
#define VERSION 5
#define CHAN_A  0
#define CHAN_B  1
#define CHAN_C  2
#define off_size 60
#define avg_Max 6
#define json_size 2000  //1536
#define ADC_DELTA 1
// auto ranger switching points
#define r1_r2_dn 129900
#define r2_r3_dn 74000
#define r2_r1_up 4130000
#define r3_r2_up 2959000

//#define nvs_erase 1
//#define nvr_debug 1       // used for profile value display
//#define mnu_debug 1       // used for menu render time display
//#define lcd_debug 1       // used touch screen calibration values
//#define raw_mode  1       // used to bypass polynome corrections
//#define dbm_debug 1
//#define cal_debug 1
//#define ply_debug 1       // polynome test / debug
//#define dch_debug 1
//#define chk_debug 1
//#define car_debug 1       // chk_autorange function

#if (nvs_erase)
  #include <nvs_flash.h>
#endif

hw_timer_t * encodertimer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

MAX11270 adc;                 // get max11270 object instance
Preferences PREF;

int32_t AdcResp = 0;

bool sampling = false;
bool pga_ena  = false;
bool cmd_echo = false;
bool dbg_mon  = false;
bool dsp_cln  = false;
bool secClick = false;
bool conv_rdy = false;
bool adc_rdy  = false;
bool cal_int  = false;
bool avg_Act  = false;
bool smp_Fast = false;
bool dm_debug = false;
int8_t cal_stp = 0;
int8_t avg_Val = 4;
int8_t avg_idx = 0;
int32_t avg_smp[6][3] = {0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0};
uint16_t sps_delay[4] = {0,0,0,0};
static bool att_sts[3] = {false, false, false};
int8_t ADC_S_Chan  = 0;
int8_t ADC_M_Chan  = 0;
int8_t dsp_cnt     = 30;
int8_t single_mode = 0;

double Bat_lvl = 0.0;
float  Bat_Ratio = 3.21;

double off_value = 0.0;
int16_t low_lvl = 0;

double vac = 0.0;
double dbm = 0.0;
volatile static double dbm_a = 0.0;
volatile static double dbm_b = 0.0;
uint32_t Adc_a = 0;
uint32_t Adc_x = 0;

float    ltx = 0;                         // Saved x coord of bottom of needle
uint16_t osx = 160, osy = 160;            // Saved x & y coords

char helper_arr[18][10] = {
      "dBm", "Vac", "mVac", "uVac", "mW", "uW", "dB Rel", "dBm Off", "mW Off",
      "uW", "", "dB", "CH: A", "CH: B", "CH: C", "CH: B - A", "CH: C - A", "?????"};

int gains[3] = {0, 2, 7};                 // gain range to actual gain
int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = {-1, -1, -1, -1, -1, -1};
uint32_t off_val[3] = {0, 0, 0};
int d = 0;

static uint32_t lastAdc[3] = {};          // previous adc value for channel
static int r_val[3] = {};                 // range value for chan
static int R[3] = {1, 2, 3};              // range translation
//static bool N[3] = {false, false, false}; // noisy signal flag
static uint16_t dly_cnt;

double Radc = 2.1529198976e-7;    // Resolution = Vavdd / 16777215
int S = 0;                        // status / controle registers on/off
int C = 0;                        // calibration registers on/off

volatile bool Disable_flg;
volatile uint8_t dual_step;
volatile static bool a_x_mode = false;
volatile bool rotaryEncoder = false;
volatile bool rotaryPush = false;
int rotationCounter = 1;
unsigned long lastButtonPress = 0;

char hw_ver[] = "5.0";
char sw_ver[] = "2.6.9";

char start[]  =  {'-', '0', 1 }; 
char end[]    =  {'.', '9', 2 };
int y[]       =  {176, 176, 200};
int x[]       =  {222, 242, 222 };
int spacing[] =  {12,  12,  80};

char start_2[]  =  {'0', 1 }; 
char end_2[]    =  {'9', 2 };
int y_2[]       =  {176, 200};
int x_2[]       =  {222, 222};
int spacing_2[] =  {12,  80};

const byte numChars = 64;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char groupFromPC[numChars] = {0};
char nameFromPC[numChars] = {0};
char stringFromPC[numChars] = {0};
int idFromPC = 0;
int integerFromPC = 0;
float floatFromPC = 0.0;
double doubleFromPC = 0.0;
bool newData = false;

//***** main *****
  int scale = 0;
  int *g; // r as pointer to int
  //g = G;  // r now points to array G

  uint64_t time_ms = 0;

  static uint64_t lastreadadc = time_ms;
  static uint64_t lastreadencoder = time_ms;
  static uint64_t lastreadButton = time_ms;
  static uint64_t lastreadtouch = time_ms;
  static uint64_t lastreadbattery = time_ms;
  static uint64_t lastdelayedadc = time_ms;
  static uint16_t act_cnt = 0;
  static uint16_t adc_cnt = 0;                // used for adc being inactive too long
  static uint16_t lst_cnt = 0;
  volatile static double dbm_x = 0.0;
  volatile static double dbm_y = 0.0;
//***** chk_auto *****
  bool chgd;
  int32_t tmp_delta;

  int r_n = 9;
  int r_l = 9;
  int d_m = 9;
  int r_o;
  bool a_o;
//***** end *****
/* interrupt service routine for encoder */
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  isr_encoder();
  portEXIT_CRITICAL_ISR(&timerMux);
}

/* interrupt service routine for ADC */
void IRAM_ATTR onAdc() {
  portENTER_CRITICAL_ISR(&mux);
  adc_rdy =  true;
  portEXIT_CRITICAL_ISR(&mux);
}

/* get adjusted battery supply voltage */
double getBattery(int pin) {

  float vin = 0.0;
  float chg = 0.0;

  vin = (analogRead(pin) * Bat_Ratio) / 1000 / 2;
  chg = -96.63 * pow(vin,3) + 999.34 * pow(vin,2) - 3278.71 * vin + 3400.59;

  if (vin < 3.4) {
    chg = 0;
  }
  return chg;
  //return (analogRead(pin) * Bat_Ratio) / 1000;
}

typedef enum {
  None      = 0,
  Idle      = 1,
  Settings  = 2,
  Edit      = 3,
  UIMenuEnd = 9,
  Complete  = 20
} State;

Menu::Engine rfMenu;

int16_t  encMovement;
int16_t  encAbsolute;
uint8_t  currentState = Idle;
bool     lastEncoderAccelerationState = true;
bool     menuUpdateRequest = false;

int activeProfileId = 0;

// todo 3x volatitle added 2.6.4
volatile uint8_t   gainValue   = 2;
volatile uint8_t   rangeValue  = 2;
uint8_t   rangeMax    = 2;
uint8_t   spsRate     = 1;
volatile uint8_t   actChan     = 0;
int16_t   setTerm     = 50;
int8_t    setUnit     = 0;
int16_t   AdcCorr     = 0x0c;
int16_t   AdcZero     = 35;
int8_t    relMode     = 0;
int8_t    zeroStep    = 0;

bool runable    = true;
bool autoRun    = true;
bool autoRng    = true;
bool cmd_Run    = false;
bool cmd_Step   = false;
bool mode_B_A   = false;
bool mode_C_A   = false;

double relBase_vac;
double relBase_dbm;
double rel_off_vac;
double rel_off_dbm;

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library for TFT
TFT_eSprite imp = TFT_eSprite(&tft);
TFT_eSprite bat = TFT_eSprite(&tft);

/* define our rotary encoder io pins (Note CS_3 is now at 32*/
#if VERSION <= 4
ClickEncoder Encoder(33, 32, 35, 4, false);
#elif VERSION > 4
ClickEncoder Encoder(34, 33, 35, 4, false);
#endif

/* track menu item state to improve render preformance */
LastItemState_t currentlyRenderedItems[MENU_ITEMS_VISIBLE];

Sett_t setBase;       // the one and only instances for
Poly_t polyBase;
Back_t backBase;
Corr_t corrBase;
Menu_t menuBase;
Switch_t switchBase;

static int G[8] = {1, 2, 4, 8, 16, 32, 64, 128};

static char param[PROFILE_LENGTH];

SerialCommand sCmd; // This seems to be place critical !!

void clearLastMenuItemRenderState() {
  for (uint8_t i = 0; i < MENU_ITEMS_VISIBLE; i++) {
    currentlyRenderedItems[i].mi = NULL;
    currentlyRenderedItems[i].pos = 0xff;
    currentlyRenderedItems[i].current = false;
  }
  /* clear comm left area */
  tft.fillRect(218, MENU_BASE_Y - 2, 160, MENU_ITEM_HEIGHT * MENU_ITEMS_VISIBLE, TFT_BLACK);
  menuUpdateRequest = true;
}

bool menuExit(const Menu::Action_t a) {
  clearLastMenuItemRenderState();
  return false;
}

bool menuDummy(const Menu::Action_t a) {
  if(a!=Menu::actionLabel) {    
    clearLastMenuItemRenderState();
  }
  return true;
}

bool editFloatSetting_1(const Menu::Action_t action) {
  /* block Offset mode for Vac measurements */
  if ((action == Menu::actionTrigger || action == Menu::actionDisplay) && (setTerm != 0)) {
    bool trigger = false;
    bool init = false;  
    if (action == Menu::actionTrigger && currentState != Edit) {
      init = true;
      currentState = Edit;
      param[0] = 0;
      Encoder.setAccelerationEnabled(true);
      tft.fillRect(218, MENU_BASE_Y - 2, 160, MENU_ITEM_HEIGHT * (MENU_ITEMS_VISIBLE - 1), TFT_BLACK); // changed to -1
    } else if (action == Menu::actionTrigger) {
      trigger = true;
    }
    if(kbd_set_1("dBm Offset", param, PROFILE_LENGTH, init, trigger)) {
      /* Done! */
      rel_off_dbm = atof(param);
      menuBase.off_dbm = rel_off_dbm;
      relMode =  (rel_off_dbm == 0.0) ? 0 : 2;
      //printf("val %e state %d\n", rel_off_dbm, relMode);
      currentState = Settings;
      Encoder.setAccelerationEnabled(false);
      clearLastMenuItemRenderState();      
    }    
  } else if (action == Menu::actionParent && currentState == Edit) {
    Encoder.setAccelerationEnabled(false);
    currentState = Settings;
    clearLastMenuItemRenderState();
  }
  return true;  
}

bool editFloatSetting_2(const Menu::Action_t action) {
  /* block Offset mode for Vac measurements */
  if (action == Menu::actionTrigger || action == Menu::actionDisplay) {
    bool trigger = false;
    bool init = false;  
    if (action == Menu::actionTrigger && currentState != Edit) {
      init = true;
      currentState = Edit;
      param[0] = 0;
      Encoder.setAccelerationEnabled(true);
      tft.fillRect(218, MENU_BASE_Y - 2, 160, MENU_ITEM_HEIGHT * (MENU_ITEMS_VISIBLE - 1), TFT_BLACK); // changed to -1
    } else if (action == Menu::actionTrigger) {
      trigger = true;
    }
    if(kbd_set_2("Reference Z", param, PROFILE_LENGTH, init, trigger)) {
      /* Done! */
      setTerm = atoi(param);
      menuBase.setterm = setTerm;
      //printf("Rel Z %d\n", setTerm);
      currentState = Settings;
      Encoder.setAccelerationEnabled(false);
      clearLastMenuItemRenderState();      
    }    
  } else if (action == Menu::actionParent && currentState == Edit) {
    Encoder.setAccelerationEnabled(false);
    currentState = Settings;
    clearLastMenuItemRenderState();
  }
  return true;  
}

void renderMenuItem(const Menu::Item_t *mi, uint8_t pos) {

  bool isCurrent = rfMenu.currentItem == mi;
  uint8_t y = MENU_BASE_Y + pos * MENU_ITEM_HEIGHT;

  if (currentlyRenderedItems[pos].mi == mi 
      && currentlyRenderedItems[pos].pos == pos 
      && currentlyRenderedItems[pos].current == isCurrent) {
    return; // don't render the same item in the same state twice
  }
  
  tft.setCursor(8, y + 14);
  /* menu cursor bar */
  tft.fillRect(5, y - 2, 200, MENU_ITEM_HEIGHT, isCurrent ? TFT_BLUE : TFT_WHITE);
  //printf("cur@pos %d, x %d, y %d\n",pos, 8, y + 12);
  if (isCurrent) {
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
  } else {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
  }
  tft.setFreeFont(STS_FONT); 
  tft.print(rfMenu.getLabel(mi));
  /* show values if in-place editable items */
  char buf[20];
  if (getItemValueLabel(mi, buf)) {
    tft.setCursor(120, y + 14);
    tft.print(buf); 
  }

  /* mark items that have children */
  if (rfMenu.getChild(mi) != &Menu::NullItem) {
    tft.setCursor(140, y + 14);
    tft.print(">"); // 0x10 -> filled right arrow
  }
  currentlyRenderedItems[pos].mi = mi;
  currentlyRenderedItems[pos].pos = pos;
  currentlyRenderedItems[pos].current = isCurrent;
}

bool kbd_set_1(const char *label, char *tmpbuf, uint32_t length, bool init, bool trigger) {

  bool finished = false;
  static uint32_t p;
  tft.setFreeFont(FSS12);
  if(init) {
    p = 0;
    tmpbuf[0] = 0;
    encAbsolute = 0;
    trigger = false; 
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(MENU_BASE_X + 62, 170); //146
    tft.print(label);
    tft.print(":");

    tft.setCursor(MENU_BASE_X + 62, 270); // 244
    tft.print("Dbl Click = Exit");
  }

  static int numElements = 0;
  static int lastencAbsolute = 0;

  int akt = 0;  
  
  if(encAbsolute<0) encAbsolute = 0;
  if(encAbsolute>numElements) encAbsolute = numElements;
  
  for(int i = 0; i < sizeof(start); i++) {
    for(char c = start[i]; c <= end[i]; c++) {
      tft.setCursor(x[i] + (c - start[i]) * spacing[i], y[i] + 45);
      if(init || encAbsolute == akt || lastencAbsolute == akt) {
        if(encAbsolute == akt) {
          tft.setTextColor(TFT_RED, TFT_BLACK);          
        } else {
          tft.setTextColor(TFT_WHITE, TFT_BLACK);          
        }
        switch(c) {
          case 1:
            tft.print("DEL");
            if(trigger) {
              if(p > 0)
                tmpbuf[--p] = 0;
            }
            break;
          case 2:
            tft.print("OK");
            if(trigger) {
              finished=true;
            }
            break;
          case 0:
          default:
            if(c == 0) {
              tft.print("SPACE");
            } else {
              tft.print(c);
            }
            if(trigger) {
              if (p < (length-1)) {
                tmpbuf[p++] = (c == 0 ? ' ' : c);
                tmpbuf[p] = 0;               
              }
            }
            break;
        } 
      } 
      akt++;      
    }
  }  
  
  numElements = akt-1;
  lastencAbsolute = encAbsolute;

  /* update display */
  tft.fillRect(MENU_BASE_X + 62, 180, 120, MENU_ITEM_HEIGHT, TFT_BLACK); //156 , 120
  tft.setCursor(MENU_BASE_X + 62, 200); //172
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setTextWrap(true);
  tft.print(tmpbuf);
  tft.setTextWrap(false);  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  
  tft.setFreeFont(STS_FONT);
  return finished;
}

bool kbd_set_2(const char *label, char *tmpbuf, uint32_t length, bool init, bool trigger) {

  bool finished = false;
  static uint32_t p;
  tft.setFreeFont(FSS12);
  if(init) {
    p = 0;
    tmpbuf[0] = 0;
    encAbsolute = 0;
    trigger = false; 
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(MENU_BASE_X + 62, 170); //146
    tft.print(label);
    tft.print(":");

    tft.setCursor(MENU_BASE_X + 62, 270); // 244
    tft.print("Dbl Click = Exit");
  }

  static int numElements = 0;
  static int lastencAbsolute = 0;

  int akt = 0;  
  
  if(encAbsolute<0) encAbsolute = 0;
  if(encAbsolute>numElements) encAbsolute = numElements;
  
  for(int i = 0; i < sizeof(start_2); i++) {
    for(char c = start_2[i]; c <= end_2[i]; c++) {
      tft.setCursor(x_2[i] + (c - start_2[i]) * spacing_2[i], y_2[i] + 45);
      if(init || encAbsolute == akt || lastencAbsolute == akt) {
        if(encAbsolute == akt) {
          tft.setTextColor(TFT_RED, TFT_BLACK);          
        } else {
          tft.setTextColor(TFT_WHITE, TFT_BLACK);          
        }
        switch(c) {
          case 1:
            tft.print("DEL");
            if(trigger) {
              if(p > 0)
                tmpbuf[--p] = 0;
            }
            break;
          case 2:
            tft.print("OK");
            if(trigger) {
              finished=true;
            }
            break;
          case 0:
          default:
            if(c == 0) {
              tft.print("SPACE");
            } else {
              tft.print(c);
            }
            if(trigger) {
              if (p < (length-1)) {
                tmpbuf[p++] = (c == 0 ? ' ' : c);
                tmpbuf[p] = 0;               
              }
            }
            break;
        } 
      } 
      akt++;      
    }
  }  
  
  numElements = akt-1;
  lastencAbsolute = encAbsolute;

  /* update display */
  tft.fillRect(MENU_BASE_X + 62, 180, 120, MENU_ITEM_HEIGHT, TFT_BLACK); //156 , 120
  tft.setCursor(MENU_BASE_X + 62, 200); //172
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setTextWrap(true);
  tft.print(tmpbuf);
  tft.setTextWrap(false);  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  
  tft.setFreeFont(STS_FONT);
  return finished;
}

bool editNumericalValue(const Menu::Action_t action) { 

  static int16_t iValueLast;
  static float   dValueLast;
  int16_t *iValue = NULL;
  float  *dValue = NULL;
  bool init = false;

  getItemValuePointer(rfMenu.currentItem, &dValue, &iValue);
  if ((init=(action == Menu::actionTrigger && currentState != Edit)) || action == Menu::actionDisplay) {
    if (init) {
      currentState = Edit;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setCursor(MENU_BASE_X + 62, MENU_BASE_Y + 84);
      switch (idxTest(rfMenu.currentItem)) {
        case 1:
          tft.print("0=High Z, 0 to 1000");
          break;
        default:
          break;
      }

      tft.setCursor(MENU_BASE_X + 62, MENU_BASE_Y + 38);
      tft.print("Click to save.");
      tft.setCursor(MENU_BASE_X + 62, MENU_BASE_Y + 62);
      tft.print("Doubleclick = exit");
      Encoder.setAccelerationEnabled(true);
      //save last Value
      if(iValue!=NULL) iValueLast=*iValue;
      if(dValue!=NULL) dValueLast=*dValue;
    }

    for (uint8_t i = 0; i < MENU_ITEMS_VISIBLE; i++) 
    {
      if (currentlyRenderedItems[i].mi == rfMenu.currentItem) 
      {
        if (init) {
          tft.fillRect(MENU_BASE_X + 60, MENU_BASE_Y - 2, 40, MENU_ITEM_HEIGHT - 2, TFT_RED);
        }
        tft.setCursor(MENU_BASE_X + 63, MENU_BASE_Y + 14);
        break;
      }
    }

    tft.setTextColor(TFT_WHITE, TFT_RED);
    /* no negative numbers may be needed! */
    if (encAbsolute < 0) encAbsolute=0;     // && !isNegSetting(rfMenu.currentItem))   
    if (isProfSetting(rfMenu.currentItem)) { 
      float tmp;
      float factor = 10;
      if (init) {
        tmp = *dValue;
        tmp *= factor;
        encAbsolute = (int16_t)tmp;
      }
      else {
        tmp = encAbsolute;
        tmp /= factor;
        *dValue = tmp;
      }      
    } else { 
      if (init) encAbsolute = *iValue;
      else *iValue = encAbsolute;
    }
    char buf[20];
    getItemValueLabel(rfMenu.currentItem, buf);
    /* clear display of any old value */
    tft.fillRect(MENU_BASE_X + 60, MENU_BASE_Y - 2, 40, MENU_ITEM_HEIGHT - 2, TFT_RED);
    tft.print(buf);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
  }
  else if ((action == Menu::actionParent || action == Menu::actionTrigger ) && currentState == Edit) 
  {
    currentState = Settings;
    clearLastMenuItemRenderState();
    if(action == Menu::actionParent){
      /* restore last Value */
      if(iValue!=NULL) *iValue=iValueLast;
      if(dValue!=NULL) *dValue=dValueLast;
    } else  {
      saveMenuBase();
    }
    Encoder.setAccelerationEnabled(false);
  }
  return true;
}

void makeSettBase() {
  setBase.spsrate = 1;      // hysteresis value for range switching
  setBase.min_adc = 0;      // option limit lowest measure level, 0-100, 0 = off
  setBase.batcorr = 3.21;   // battery display correction factor
  setBase.adcres  = 2.15262187e-7;    // adc uVolt/Bit resolution
  setBase.adccorr = 0x0c;   // disable system, enable self correction for offset & gain
  setBase.adczero = 35;
  setBase.sps_i_0 = 2;
  setBase.sps_i_1 = 4;
  setBase.sps_i_2 = 6;
  setBase.sps_i_3 = 8;
}

void makeBackBase() {
  backBase.a_r[0] = 0.0;
  backBase.a_r[1] = 0.0;
  backBase.a_r[2] = 0.0;

  backBase.b_r[0] = 0.0;
  backBase.b_r[1] = 0.0;
  backBase.b_r[2] = 0.0;

  backBase.c_r[0] = 0.0;
  backBase.c_r[1] = 0.0;
  backBase.c_r[2] = 0.0;
}

void makePolyBase() {
  polyBase.a_r1[0] = 0.0;
  polyBase.a_r1[1] = 0.0;
  polyBase.a_r1[2] = 0.0;
  polyBase.a_r1[3] = 0.0;
  polyBase.a_r1[4] = 0.0;
  polyBase.a_r2[0] = 0.0;
  polyBase.a_r2[1] = 0.0;
  polyBase.a_r2[2] = 0.0;
  polyBase.a_r2[3] = 0.0;
  polyBase.a_r2[4] = 0.0;
  polyBase.a_r3[0] = 0.0;
  polyBase.a_r3[1] = 0.0;
  polyBase.a_r3[2] = 0.0;
  polyBase.a_r3[3] = 0.0;
  polyBase.a_r3[4] = 0.0;

  polyBase.b_r1[0] = 0.0;
  polyBase.b_r1[1] = 0.0;
  polyBase.b_r1[2] = 0.0;
  polyBase.b_r1[3] = 0.0;
  polyBase.b_r1[4] = 0.0;
  polyBase.b_r2[0] = 0.0;
  polyBase.b_r2[1] = 0.0;
  polyBase.b_r2[2] = 0.0;
  polyBase.b_r2[3] = 0.0;
  polyBase.b_r2[4] = 0.0;
  polyBase.b_r3[0] = 0.0;
  polyBase.b_r3[1] = 0.0;
  polyBase.b_r3[2] = 0.0;
  polyBase.b_r3[3] = 0.0;
  polyBase.b_r3[4] = 0.0;

  polyBase.c_r1[0] = 0.0;
  polyBase.c_r1[1] = 0.0;
  polyBase.c_r1[2] = 0.0;
  polyBase.c_r1[3] = 0.0;
  polyBase.c_r1[4] = 0.0;
  polyBase.c_r2[0] = 0.0;
  polyBase.c_r2[1] = 0.0;
  polyBase.c_r2[2] = 0.0;
  polyBase.c_r2[3] = 0.0;
  polyBase.c_r2[4] = 0.0;
  polyBase.c_r3[0] = 0.0;
  polyBase.c_r3[1] = 0.0;
  polyBase.c_r3[2] = 0.0;
  polyBase.c_r3[3] = 0.0;
  polyBase.c_r3[4] = 0.0;
}

void makeCorrBase() {
  corrBase.mask_corr = 0;
  corrBase.a_r1_0 = 0.0;
  corrBase.a_r2_0 = 0.0;
  corrBase.a_r3_0 = 0.0;
  corrBase.b_r1_0 = 0.0;
  corrBase.b_r2_0 = 0.0;
  corrBase.b_r3_0 = 0.0;
  corrBase.c_r1_0 = 0.0;
  corrBase.c_r2_0 = 0.0;
  corrBase.c_r3_0 = 0.0;
}

void makeMenuBase() {
  menuBase.actchan  = 0;      // default channel in use
  menuBase.autorng  = 1;      // auto range mode active
  menuBase.autorun  = 1;
  menuBase.setterm = 50;
  menuBase.units    = 0;
  menuBase.off_dbm  = 0.0;
}

bool saveSettBase() {
  tmrControl(false);
  PREF.putBytes("Setting", (uint8_t*)&setBase, sizeof(setBase));
  #if nvr_debug
    for(int i = 0; i < sizeof(Sett_t); i++)
      printf("%#x ",(unsigned int) ((char*)&setBase)[i]);
    printf("\n");
  #endif
  tmrControl(true);
  return true;
}

bool saveBackBase() {
  tmrControl(false);
  PREF.putBytes("Backup", (uint8_t*)&backBase, sizeof(backBase));
  #if nvr_debug
    for(int i = 0; i < sizeof(Corr_t); i++)
      printf("%#x ",(unsigned int) ((char*)&backBase)[i]);
    printf("\n");
  #endif
  tmrControl(true);
  return true;
}

bool saveCorrBase() {
  tmrControl(false);
  PREF.putBytes("Correction", (uint8_t*)&corrBase, sizeof(corrBase));
  #if nvr_debug
    for(int i = 0; i < sizeof(Corr_t); i++)
      printf("%#x ",(unsigned int) ((char*)&corrBase)[i]);
    printf("\n");
  #endif
  tmrControl(true);
  return true;
}

bool savePolyBase() {
  tmrControl(false);
  PREF.putBytes("Polynome", (uint8_t*)&polyBase, sizeof(polyBase));
  #if nvr_debug
    for(int i = 0; i < sizeof(Poly_t); i++)
      printf("%#x ",(unsigned int) ((char*)&polyBase)[i]);
    printf("\n");
  #endif
  tmrControl(true);
  return true;
}

bool saveMenuBase() {
  tmrControl(false);
  menuBase.off_dbm = 0.0;
  menuBase.actchan = 0;
  PREF.putBytes("Menu", (uint8_t*)&menuBase, sizeof(menuBase));
  #if nvr_debug
    for(int i = 0; i < sizeof(Menu_t); i++)
      printf("%#x ",(unsigned int) ((char*)&menuBase)[i]);
    printf("\n");
  #endif
  tmrControl(true);
  return true;
}

bool loadSettBase() {
  
  size_t length = PREF.getBytesLength("Setting");

  #if nvr_debug
    for(int i = 0; i < sizeof(Setting_t); i++)
      printf("%#x ",(unsigned int) ((char*)&setBase)[i]);
    printf("\n");
  #endif

  if (length != sizeof(setBase)) {
    makeSettBase();
    saveSettBase();
    printf("save Setting base\n");
    return false;  
  } else {
    PREF.getBytes("Setting", (uint8_t*)&setBase, length);
  }
  return true;  
}

bool loadCorrBase() {

  size_t length = PREF.getBytesLength("Correction");

  if (length != sizeof(corrBase)) {
    makeCorrBase();
    saveCorrBase();
    printf("save correction base\n");
    return false;
  } else {
    PREF.getBytes("Correction", (uint8_t*)&corrBase, length);
  }
  return true;  
}

bool loadBackBase() {

  size_t length = PREF.getBytesLength("Backup");

  if (length != sizeof(backBase)) {
    makeBackBase();
    saveBackBase();
    printf("load backup base\n");
  } else {
    PREF.getBytes("Backup", (uint8_t*)&backBase, length);
  }
  return true;  
}

bool loadPolyBase() {
  
  size_t length = PREF.getBytesLength("Polynome");
  
  #if nvr_debug
    for(int i = 0; i < sizeof(Poly_t); i++)
      printf("%#x ",(unsigned int) ((char*)&polyBase)[i]);
    printf("\n");
  #endif

  if (length != sizeof(polyBase)) {
    makePolyBase();
    savePolyBase();
    printf("save Polymome base\n");
  return false;  
  } else {
    PREF.getBytes("Polynome", (uint8_t*)&polyBase, length);
  }
  return true;  
}

bool loadMenuBase() {

  size_t length = PREF.getBytesLength("Menu");

  if (length != sizeof(menuBase)) {
    makeMenuBase();
    saveMenuBase();
    printf("save Menu base\n");
  } else {
    PREF.getBytes("Menu", (uint8_t*)&menuBase, length);
  }
  return true;  
}

void initSettBase() {
  spsRate = setBase.spsrate;
  low_lvl = setBase.min_adc;
  Bat_Ratio = setBase.batcorr;
  Radc = setBase.adcres;
  AdcCorr = setBase.adccorr;
  AdcZero = setBase.adczero;
  sps_delay[0] = setBase.sps_i_0;
  sps_delay[1] = setBase.sps_i_1;
  sps_delay[2] = setBase.sps_i_2;
  sps_delay[3] = setBase.sps_i_3;
  pgaControl(gainValue, spsRate);
}

void initCorrBase() {
  int16_t ac = corrBase.mask_corr;

  if (((ac & 0x001) >> 0) == 0x01) {
    //printf("Was %e corr %e\n", polyBase.a_r1[0], corrBase.a_r1_0 / 20);
    polyBase.a_r1[0] = backBase.a_r[0] + (corrBase.a_r1_0 / 20);
    //printf("Now %e orig %e\n", polyBase.a_r1[0], backBase.a_r[0]);
  }
  if (((ac & 0x010) >> 4) == 0x01) polyBase.b_r1[0] = backBase.b_r[0] + (corrBase.b_r1_0 / 20);
  if (((ac & 0x100) >> 8) == 0x01) polyBase.c_r1[0] = backBase.c_r[0] + (corrBase.c_r1_0 / 20);

  if (((ac & 0x002) >> 1) == 0x01) polyBase.a_r2[0] = backBase.a_r[1] + (corrBase.a_r2_0 / 20);
  if (((ac & 0x020) >> 5) == 0x01) polyBase.b_r2[0] = backBase.b_r[1] + (corrBase.b_r2_0 / 20);
  if (((ac & 0x200) >> 9) == 0x01) polyBase.c_r2[0] = backBase.c_r[1] + (corrBase.c_r2_0 / 20);

  if (((ac & 0x004) >> 2) == 0x01) polyBase.a_r3[0] = backBase.a_r[2] + (corrBase.a_r3_0 / 20);
  if (((ac & 0x040) >> 6) == 0x01) polyBase.b_r3[0] = backBase.b_r[2] + (corrBase.b_r3_0 / 20);
  if (((ac & 0x400) >>10) == 0x01) polyBase.c_r3[0] = backBase.c_r[2] + (corrBase.c_r3_0 / 20);

}

void initMenuBase() {
  actChan   = menuBase.actchan;
  // disabled for now, we may use last setting value
  //autoRng  = menuBase.autorng;
  //autoRun   = menuBase.autorun;
  menuBase.setterm = 50;
  setTerm   = menuBase.setterm;
  //setUnit   = menuBase.units;
  setChannel(actChan);
  fastBtn(1);
  fastBtn(3);
  fastBtn(4);
}

      // Name,           Label,          Next,           Previous,       Parent,         Child,          Callback
MenuItem(miExit,         "",             Menu::NullItem, Menu::NullItem, Menu::NullItem, miRelMeas,      menuExit);
MenuItem(miRelMeas,      "dB Rel      ", miRelSpec,      Menu::NullItem, miExit,         Menu::NullItem, SetRelative);
MenuItem(miRelSpec,      "dBm Offset  ", miSetTerm,      miRelMeas,      miExit,         Menu::NullItem, editFloatSetting_1);
MenuItem(miSetTerm,      "Ref Z       ", miDual_BA,      miRelSpec,      miExit,         Menu::NullItem, editFloatSetting_2); //editNumericalValue);
MenuItem(miDual_BA,      "B - A       ", miDual_CA,      miSetTerm,      miExit,         Menu::NullItem, SetDifSrc);
MenuItem(miDual_CA,      "C - A       ", miNothing,      miDual_BA,      miExit,         Menu::NullItem, SetDifSrc);
MenuItem(miNothing,      "            ", Menu::NullItem, miDual_CA,      miExit,         Menu::NullItem, menuDummy);

void getItemValuePointer(const Menu::Item_t *mi, float **d, int16_t **i) {
  if (mi == &miSetTerm)    *i = &menuBase.setterm;
  if (mi == &miRelMeas)    *i = &switchBase.actrel;
  if (mi == &miRelSpec)    *d = &menuBase.off_dbm;
  if (mi == &miDual_BA)    *i = &switchBase.actb_a;
  if (mi == &miDual_CA)    *i = &switchBase.actc_a;
}

bool SetRelative(const Menu::Action_t action) {
  if (action == Menu::actionTrigger && currentState != Edit) {
    switch (relMode) {
      case 0:
        // change to relative mode
        switchBase.actrel = 1;
        relMode = 1;
        relBase_vac = vac;
        // handle input channel delta value
        if (mode_B_A || mode_C_A) {
          relBase_dbm = dbm_b - dbm_a;
        } else {
          relBase_dbm = dbm;
        }
        break;
      case 1:
        // change to normal mode
        switchBase.actrel = 0;
        relMode = 0;
        relBase_vac = 0.0;
        relBase_dbm = 0.0;
        break;
      default:
        break;
    }
    /* make sure changes are been printed out and state been cleared */
    clearLastMenuItemRenderState();
  }
  return true;
}

bool SetDifSrc(const Menu::Action_t action) {
  if (action == Menu::actionTrigger && currentState != Edit) {
    
    if (rfMenu.currentItem == &miDual_BA) {
      if (!mode_C_A) {
        if(!mode_B_A) {
          mode_B_A = true;
          fastBtn(7);
          a_x_mode = false;
          dual_step = 0;
          // erase button #1 text, touch event will also be disbled
          tft.fillRect(5, 285, 90, 30, TFT_WHITE);
          switchBase.actb_a = 1;
          secClick = true;
        } else {
          if (secClick) {
            secClick = false;
            relBase_dbm = dbm_b - dbm_a;
            //printf("need to zero\n");
          } else {
            mode_B_A = false;
            switchBase.actb_a = 0;
            digitalMeterHelper(40, 95, 10);
            digitalMeterHelper(280, 95, 10);
//            setChannel(actChan);
            spsRate = setBase.spsrate;
            fastBtn(1);
            fastBtn(7);
          }
        }
        //printf("BA %d, %d\n", mode_B_A, secClick);
      }
    }
    if (rfMenu.currentItem == &miDual_CA) {
      if (!mode_B_A) {
        if(!mode_C_A) {
          mode_C_A = true;
          fastBtn(7);
          a_x_mode = false;
          dual_step = 0;
          // erase button #1 text, touch event will also be disbled
          tft.fillRect(5, 285, 90, 30, TFT_WHITE);
          switchBase.actc_a = 1;
          secClick = true;
        } else {
          if (secClick) {
            secClick = false;
            relBase_dbm = dbm_b - dbm_a;
            //printf("need to zero\n");
          } else {
            mode_C_A = false;
            switchBase.actc_a = 0;
            digitalMeterHelper(40, 95, 10);
            digitalMeterHelper(280, 95, 10);
//            setChannel(actChan);
            spsRate = setBase.spsrate;
            fastBtn(1);
            fastBtn(7);
          }
        }
      }
    }

    clearLastMenuItemRenderState();
  }
  return true;
}

bool isProfSetting(const Menu::Item_t *mi) {
  return false;
}

bool isNegSetting(const Menu::Item_t *mi) {
  return mi == &miSetTerm; 
}

int8_t idxTest(const Menu::Item_t *mi) {
  if (mi == &miSetTerm) return 1;
  return 0;
}

bool getItemValueLabel(const Menu::Item_t *mi, char *label) {
  int16_t *iValue = NULL;
  float  *dValue = NULL;
  
  getItemValuePointer(mi, &dValue, &iValue);

  if(isProfSetting(mi)){
    sprintf(label,"%.1f",*dValue);    
  } else if (mi == &miSetTerm) {
    sprintf(label,"%d",*iValue);
  } else if (mi == &miRelMeas) {
    sprintf(label,"%s",(*iValue == 1) ? "Active" : "");
  } else if (mi == &miDual_BA) {
    sprintf(label,"%s",(*iValue == 1) ? "Active" : "");
  } else if (mi == &miDual_CA) {
    sprintf(label,"%s",(*iValue == 1) ? "Active" : "");
  } else if(mi == &miRelSpec) {
    sprintf(label,"%.2f",menuBase.off_dbm);
  } else {
    return false;    
  }
  return true;
}

void IRAM_ATTR service_encoder(void) {
  int16_t encMovement = Encoder.getValue();
  // handle button movement
  if (encMovement)  {
    if(!avg_Act) {
      encAbsolute += encMovement;
      if (currentState == Settings) {
        rfMenu.navigate((encMovement > 0) ? rfMenu.getNext() : rfMenu.getPrev());
        menuUpdateRequest = true;
      } else if (currentState == Edit) {
        if (rfMenu.currentItem != &Menu::NullItem) {
          rfMenu.executeCallbackAction(Menu::actionDisplay);      
        }        
      }
    } else {
      avg_Val += encMovement;
      avg_idx = 0;
      if (avg_Val < 2) {avg_Val = 2;}
      if (avg_Val > avg_Max) {avg_Val = avg_Max;}
      fastBtn(6);
    }
  }
}

void service_button() {
  /* handle button */
  switch (Encoder.getButton()) {

    case ClickEncoder::Clicked:
      if (currentState < UIMenuEnd) {
        rfMenu.invoke();
        menuUpdateRequest = true;
      } else if (currentState == Complete) { 
        menuExit(Menu::actionDisplay);    // reset to initial state
        rfMenu.navigate(&miRelMeas);      //miSettings);
        currentState = Settings;
        menuUpdateRequest = true;
      }
      break;

    case ClickEncoder::DoubleClicked:
      #if mnu_debug
        printf("currentState:        %d\n",currentState);
        printf("rfMenu.getParent():  %d\n",(uint32_t)rfMenu.getParent());
        printf("&miExit:             &d\n",(uint32_t)&miExit);
      #endif
      /* disable double click in case of B-A / C-A selected */ 
      if (!secClick) {
        if (currentState == Edit) {
          rfMenu.executeCallbackAction(Menu::actionParent);      
        } else if (currentState < UIMenuEnd && rfMenu.getParent() != &miExit) {
          //displayMenusInfos();
          rfMenu.navigate(rfMenu.getParent());
          menuUpdateRequest = true;
        }
      }
      break;
  }
}

void service_update() {
    /* handle menu update */
    if ((menuUpdateRequest) && (true)) {
      menuUpdateRequest = false;
      //uint64_t dtime = esp_timer_get_time();
      rfMenu.render(renderMenuItem, MENU_ITEMS_VISIBLE);
      
      /* Scrollbar */
      Menu::Info_t mi = rfMenu.getItemInfo(rfMenu.currentItem);
      uint8_t sbTop = MENU_BASE_Y - 2, sbWidth = 4, sbLeft = 210 - sbWidth;
      uint32_t sbHeight = MENU_ITEMS_VISIBLE * MENU_ITEM_HEIGHT;
      float sbMarkHeight = MENU_ITEM_HEIGHT; //sbHeight / mi.siblings;
      float sbMarkTop = MENU_BASE_Y - 2 + (sbMarkHeight * mi.position);
      tft.fillRect(sbLeft, sbTop,     sbWidth, sbHeight,     TFT_BLUE);
      tft.fillRect(sbLeft, (int32_t) sbMarkTop, sbWidth, (int32_t) sbMarkHeight, TFT_RED);

      /* debug scrollbar values */
      #if mnu_debug
          char t_buf[60];
          sprintf("%s blue - xl: %d, yt: %d, w: %d, h: %d\n", t_buf, sbLeft, sbTop, sbWidth, sbHeight);
          sprintf("%s red  - xl: %d, yt: %d, w: %d, h: %d\n", t_buf, sbLeft, (int32_t) sbMarkTop, sbWidth, (int32_t) sbMarkHeight);
      #endif

      // debug menu render times
      #if mnu_debug
        printf("menu render took: %d us!\n", (uint32_t)(esp_timer_get_time() - dtime));
      #endif

    }
}

void initial_menu() {
  menuExit(Menu::actionDisplay); // reset to initial state
  rfMenu.navigate(&miRelMeas); //miSettings);
  currentState = Settings;
  menuUpdateRequest = true;
}

void IRAM_ATTR isr_encoder(void) {
  Encoder.service();
}

void fastBtn(uint16_t mode) {
  #define y_btn 285
  int *r; /* r as pointer to int  */
  r = R;  /* r now points to array G */
  char buf2[16];
  uint16_t clr = TFT_BLACK;
  tft.setFreeFont(STS_FONT); 
  switch (mode) {
    case 0:
      tft.fillRect(5,       y_btn, 90, 30, TFT_WHITE);
      tft.fillRect(5 +  95, y_btn, 90, 30, TFT_WHITE);
      tft.fillRect(5 + 190, y_btn, 90, 30, TFT_WHITE);
      tft.fillRect(5 + 285, y_btn, 90, 30, TFT_WHITE);
      tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);

      tft.fillRect(5 + 380, y_btn - 35, 90, 30, TFT_WHITE);

      //tft.fillRect(5 + 380, y_btn - 70, 90, 30, TFT_WHITE);

      //tft.fillRect(5 + 285, y_btn - 35, 90, 30, TFT_WHITE);
      //tft.fillRoundRect(5 + 380, y_btn - 35, 90, 30, 3, TFT_WHITE);
      //tft.drawRoundRect(5 + 380, y_btn - 35, 90, 30, 3, TFT_GOLD);

      tft.setTextColor(clr, TFT_WHITE);
      sprintf(buf2, "Chan %d", 0);
      tft.drawCentreString(buf2, 50, y_btn + 7, GFXFF);
      sprintf(buf2, "%s", "Range 1");
      tft.drawCentreString(buf2, 145, y_btn + 7, GFXFF);
      sprintf(buf2, "%s", "dBm");
      tft.drawCentreString(buf2, 235, y_btn + 7, GFXFF);
      sprintf(buf2, "%s", "Auto");
      tft.drawCentreString(buf2, 335, y_btn + 7, GFXFF);
      sprintf(buf2, "%s", "Zero");
      tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);

      sprintf(buf2, "%s", "Avg #");
      tft.drawCentreString(buf2, 430, y_btn + 7 - 35, GFXFF);

      //sprintf(buf2, "%s", "Slow");
      //tft.drawCentreString(buf2, 430, y_btn + 7 - 70, GFXFF);

      //sprintf(buf2, "%s", "Run");
      //tft.drawCentreString(buf2, 430, y_btn + 7 - 35, GFXFF);

      fastBtn(2);
      fastBtn(3);
      fastBtn(4);
      fastBtn(5);
      fastBtn(7);
      break;
    case 1:
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5, y_btn, 90, 30, TFT_WHITE);
      sprintf(buf2, "Chan %s", ((actChan + 1) == 3) ? "C" : ((actChan + 1) == 2) ? "B" : "A");
      tft.drawCentreString(buf2, 50, y_btn + 7, GFXFF);
      break;
    case 2:  
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5 + 95, y_btn, 90, 30, TFT_WHITE);
      sprintf(buf2, "Range %d", *(r + rangeValue));
      tft.drawCentreString(buf2, 145, y_btn + 7, GFXFF);
      break;
    case 3:
      switch (setUnit) {
        case 0:
          sprintf(buf2, "dBm");
          break;
        case 1:
          sprintf(buf2, "mW");
          break;
        case 2:
          sprintf(buf2, "uV");
          break;
      }
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5 + 190, y_btn, 90, 30, TFT_WHITE);
      tft.drawCentreString(buf2, 235, y_btn + 7, GFXFF);
      break;
    case 4:
      if (autoRng) {
        sprintf(buf2, "Auto");
      } else {
        sprintf(buf2, "Man");
      }
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5 + 285, y_btn, 90, 30, TFT_WHITE);
      tft.drawCentreString(buf2, 335, y_btn + 7, GFXFF);
      break;
    case 5:
      tft.setTextColor(clr, TFT_WHITE);
      switch (zeroStep) {
        case 0:
          /* update button to init state */
          tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);
          sprintf(buf2, "%s", "Zero");
          tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);
          break;
        case 1:
          /* update to confirm channel zero or not */
          tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);
          sprintf(buf2, "%s", "Zero");
          tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);

          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.setCursor(MENU_BASE_X + 62, 170);
          tft.print("Cables removed ?");
          tft.fillRect(MENU_BASE_X + 64, 178, 80, 24, TFT_WHITE);
          tft.fillRect(MENU_BASE_X + 164, 178, 35, 24, TFT_WHITE);
          tft.setTextColor(TFT_BLACK, TFT_WHITE);
          tft.setCursor(MENU_BASE_X + 62, 196);
          tft.print("  Cancel        Ok");
          break;
        case 2:
          /* initiate channel zero operation, erase comm area, notify */
          tft.fillRect(MENU_BASE_X + 62, 155, 150, 60, TFT_BLACK);
          tft.setTextColor(clr, TFT_WHITE);
          tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);
          sprintf(buf2, "%s", "Busy");
          tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);
          /* enable zero average values in main adc loop */
          cal_int = true;
          cal_stp = 0;
          break;
        case 3:
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.setCursor(MENU_BASE_X + 62, 170);
          tft.print("Apply offset's ?");
          tft.fillRect(MENU_BASE_X + 64, 178, 80, 24, TFT_WHITE);
          tft.fillRect(MENU_BASE_X + 164, 178, 35, 24, TFT_WHITE);
          tft.setTextColor(TFT_BLACK, TFT_WHITE);
          tft.setCursor(MENU_BASE_X + 62, 196);
          tft.print("  Cancel        Ok");
          break;
        case 4:
          /* abort channel ero operation, erase comm area */
          tft.fillRect(MENU_BASE_X + 62, 155, 155, 60, TFT_BLACK);
          tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);
          sprintf(buf2, "%s", "Zero");
          tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);
          printf("Zero operation cancelled\n");
          zeroStep = 0;
          break;
        case 5:
          tft.fillRect(MENU_BASE_X + 62, 155, 150, 60, TFT_BLACK);
          tft.setTextColor(clr, TFT_WHITE);
          tft.fillRect(5 + 380, y_btn, 90, 30, TFT_WHITE);
          sprintf(buf2, "%s", "Zero Act");
          tft.drawCentreString(buf2, 430, y_btn + 7, GFXFF);
          zeroStep = 0;
          break;
        default:
          break;
      }
      break;
    case 6:
      if (avg_Act) {
        sprintf(buf2, "# %d Act", avg_Val);
      } else {
        sprintf(buf2, "Avg #");
      }
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5 + 380, y_btn - 35, 90, 30, TFT_WHITE);
      tft.drawCentreString(buf2, 430, y_btn + 7 - 35, GFXFF);
      break;
  case 7:
      if (mode_B_A || mode_C_A) {
        if (smp_Fast) {
          sprintf(buf2, "Slow");
          spsRate = spsRate + 1 ;
          //printf("1 Sample Rate (sps) = %d\n", spsRate);
        } else {
          sprintf(buf2, "Fast");
          spsRate = setBase.spsrate;
          //printf("2 Sample Rate (sps) = %d\n", spsRate);
        }
        adc.startConversion(spsRate);
      } else {
        sprintf(buf2, "     ");
        smp_Fast = false;
        //printf("3 Sample Rate (sps) = %d\n", spsRate);
      }
      tft.setTextColor(clr, TFT_WHITE);
      tft.fillRect(5 + 380, y_btn - 70, 90, 30, TFT_WHITE);
      tft.drawCentreString(buf2, 430, y_btn + 7 - 70, GFXFF);
      break;
    default:
      break;
  }
}

void touch_calibrate()
{
  uint16_t calData[5];
  //uint8_t calDataOK = 0;

  tft.init();
  tft.setRotation(3);

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.printf("Touch corners as indicated\n");

  tft.setTextFont(1);

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  printf("\n Use this calibration code in setup():\n");
  printf("  uint16_t calData[5] = { ");

  for (uint8_t i = 0; i < 5; i++)
  {
    printf("%d", calData[i]);
    if (i < 4) printf(", ");
  }

  printf(" };\n");
  printf("  tft.setTouch(calData);\n");


  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.printf("Calibration complete!\n");
  tft.printf("Calibration code sent to Serial port.\n");

  sys_delay_ms(4000);
}

void tft_ini_cal() {
  /* init (HSPI based, parameters in project .ini file) TFT screen & rotation */
  tft.init();
  tft.setRotation(3);
  imp.createSprite(480, 108);

  /* init touch routine as to obtain the calData value's */
  #ifdef lcd_debug
    // Calibrate the touch screen and retrieve the scaling factors
    touch_calibrate();
  #endif

  /* initialize the touch screen & it's value's */
  uint16_t calData[5] = { 396, 3229, 359, 3200, 3 }; // <== adjusted y1 value to 3200
  tft.setTouch(calData);

  /* clear out display */
  tft.fillScreen(TFT_BLACK);
}

void digitalMeterHelper(int32_t x, int32_t y, int unit) {

  imp.setFreeFont(STS_FONT);
  imp.setTextColor(TFT_BLACK);
  /* clear previous scale / unit value */
  imp.fillRect(x, y - 13, 75 , 26, TFT_WHITE);
  sys_delay_ms(2);
  imp.setCursor(x, y);
  /* set new scale / unit value */
  imp.print(helper_arr[unit]);
  sys_delay_ms(2);
  imp.setFreeFont(MTR_FONT);
}

void digitalMeter(int mode, int rel) {
  char buf1[32];
  int scale = 0;
  double tmp = 0;
  imp.setFreeFont(MTR_FONT); 

  switch (mode) {
    case 0:
      if (Disable_flg) {break;}
      /* setup / init screen part */
      imp.fillRect(5, 3, 470 , 105, TFT_WHITE);
      sys_delay_ms(2);
      imp.setTextColor(TFT_BLACK, TFT_WHITE);
      break;
    case 1:
      if (Disable_flg) {break;}
      /* clear previous values */
      digitalMeterHelper(180, 95, 10);
      imp.fillRect(20, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      imp.fillRect(260, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      digitalMeterHelper(40, 95, (actChan == 0) ? 12 : (actChan == 1) ? 13 : 14);
      /* main mV function on right side */
      scale = (vac < 0.001) ? 3 : (vac < 1) ?  2 : 1;
      digitalMeterHelper(400, 95, scale);
      if (rel == 1) {
        tmp = vac - relBase_vac;
      } else {
        tmp = vac;
      }
      sprintf(buf1, "%.2f", (scale == 3) ? tmp * 1000000 : (scale == 2) ? tmp * 1000 : tmp);
      imp.drawCentreString(buf1, 360, 35, GFXFF);
      sys_delay_ms(2);
      break;
    case 2:
      if (Disable_flg) {break;}
      /* clear previous values */
      imp.fillRect(20, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      imp.fillRect(260, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      digitalMeterHelper(40, 95, (actChan == 0) ? 12 : (actChan == 1) ? 13 : 14);
      /* main dBm functions on left side */
      if (setUnit == 0) {
        /* use helper to set scale, fixed for dBm */
        digitalMeterHelper(180, 95, 0);
        tmp = (dbm == dbm) ? dbm : 0.0;
        if (tmp == 0.0) {
          sprintf(buf1, "LOW");
        } else {
          sprintf(buf1, "%.2f", tmp);
        }
        imp.drawCentreString(buf1, 120, 35, GFXFF);
        sys_delay_ms(2);
      }  

      /* display in uW mode */
      if (setUnit == 1) {
        tmp = 1 * pow10((dbm == dbm) ? dbm/10 : 0.0);
        if (tmp < 1.0e-2) {
          sprintf(buf1, " %.2f", tmp*1000);
          digitalMeterHelper(180, 95, 5);
        } else {
          sprintf(buf1, " %.2f", tmp);
          digitalMeterHelper(180, 95, 4);
        }
        imp.drawCentreString(buf1, 120, 35, GFXFF);
        sys_delay_ms(2);
      }
      /* right side handling, calculate scale & use helper to display */
      if (rel == 0) {
        scale = (vac < 0.001) ? 3 : (vac < 1) ?  2 : 1;
        digitalMeterHelper(400, 95, scale);
        sprintf(buf1, "%.2f", (scale == 3) ? vac * 1000000 : (scale == 2) ? vac * 1000 : vac);
        imp.drawCentreString(buf1, 360, 35, GFXFF);
        sys_delay_ms(25);
      } else if (rel == 1) {
        if (setUnit == 0) {
          digitalMeterHelper(400, 95, 6);
          sprintf(buf1, "%.2f", dbm - relBase_dbm); 
        } else {
          digitalMeterHelper(400, 95, 6);
          sprintf(buf1, "%.2f", dbm - relBase_dbm); // ????
        }
        imp.drawCentreString(buf1, 360, 35, GFXFF);
        sys_delay_ms(25);
      } else if (rel == 2) {
        if (setUnit == 0){
          /* results are in dBm */
          digitalMeterHelper(180, 95, 0);
          digitalMeterHelper(400, 95, 7);
          tmp = (dbm == dbm) ? (dbm + rel_off_dbm) : 0.0;
          if (dbm == 0.0) {
            sprintf(buf1, "LOW");
          } else {
            sprintf(buf1, "%.2f", tmp);
          }
          imp.drawCentreString(buf1, 360, 35, GFXFF);
          sys_delay_ms(2);
        } else {
          /* results are in mW / uW */
          tmp = 1 * pow10((dbm == dbm) ? (dbm + rel_off_dbm)/10 : 0.0); 
          if (tmp < 1.0e-2) {
            sprintf(buf1, " %.2f", tmp*1000);
            digitalMeterHelper(400, 95, 9);
          } else {
            sprintf(buf1, " %.2f", tmp);
            digitalMeterHelper(400, 95, 8);
          }
          imp.drawCentreString(buf1, 360, 35, GFXFF);
          sys_delay_ms(2);
        }
      }
      break;
    case 3:
      if (Disable_flg) {break;}
      imp.fillRect(20, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      imp.fillRect(260, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      digitalMeterHelper(40, 95, (mode_B_A) ? 13 : 14);
      digitalMeterHelper(280, 95, (mode_B_A) ? 15 : 16);

      digitalMeterHelper(180, 95, 0);
      tmp = (dbm_b != dbm_b) ? 0.0 : dbm_b;
      sprintf(buf1, "%.2f", tmp);
      imp.drawCentreString(buf1, 120, 35, GFXFF);
      sys_delay_ms(2);
      digitalMeterHelper(400, 95, (rel == 0) ? 11 : 6);
      tmp = (dbm_a != dbm_a) ? 0.0 : dbm_b - dbm_a;
      sprintf(buf1, "%.2f", tmp);
      sprintf(buf1, "%.2f", (secClick) ? tmp : tmp - relBase_dbm);
      imp.drawCentreString(buf1, 360, 35, GFXFF);
      sys_delay_ms(2);
      break;
    case 9:
      if (rel == 1) { Disable_flg = true; }
      imp.fillRect(20, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      imp.fillRect(260, 40 - 8, 200 , 60, TFT_WHITE);
      sys_delay_ms(2);
      sprintf(buf1, "Flash Incorrect !");
      imp.drawCentreString(buf1, 240, 35, GFXFF);
      sys_delay_ms(2);
      break;
  }
  imp.pushSprite(0, 0);
  sys_delay_ms(25);
  tft.setFreeFont(STS_FONT);
}

/* function for average offset calculation */
bool off_Chan (int chan, int32_t val) {
  
  static int32_t min = 5000;
  static int32_t max = 0;
  static int32_t smp[off_size];
  bool off_action = false;        // flag to signal avage sample completed
  static int pnt = 0;
  int32_t avg, sum;
  int i;
  
  if (chan < 3) {
    smp[pnt] = val;
    if (pnt++ == AdcZero) {
      min = 1000;
      max = 0;
      pnt = 0;
      /* get sum over smp_size samples */
      sum = 0;
      for(i = 0; i < AdcZero; ++i) {
        sum += smp[i];
      }
      /* determine average over smp_size */
      avg = sum / AdcZero;
      off_val[chan] = avg;
      //printf("Avg %d\n", avg);
      off_action = true;
    } else {
      /* determine min / max value against average */
      if (val > max) {
        max = val;
      }
      if (val < min) {
        min = val;
      }
      /* for testing as to find/test scaling */
      #ifdef DEBUG
        printf("Min %d, Max %d, Val %d\n", min, max, val);
      #endif
    }
  } else {
    /* init sample array */
    for(i = 0; i < AdcZero; ++i) {
      smp[i] = 0;
    }
    min = 1000;
    max = 0;
    pnt = 0;
    off_action = true;
  }
  return off_action;
}

void barMeter(int mode, double val) {
  #define smp_size 25
  static double min = 99.0;
  static double max = -99.0;
  static double smp[smp_size];
  static uint16_t lmin;
  static uint16_t lmax;
  static uint16_t lavg;

  static int pnt = 0;
  double avg, sum, dmin, dmax;
  int i;
  int x = 100;
  int y = 123;
  switch (mode) {
    case 0:
      for(i = 0; i < smp_size; ++i) {
        smp[i] = 0.0;
      }
      /* bar Meter outline */
      tft.fillRect(5, 115,470, 12, TFT_WHITE);

      x = 239;
      tft.fillRect(x, y - 6, 2, 7, TFT_BLACK);
      tft.fillTriangle(x, y, x + 8, y, x + 4, y - 6, TFT_RED);
      tft.fillTriangle(x, y - 6, x + 8, y - 6, x + 4, y, TFT_GREEN);
      lavg = x;
      lmin = x;
      lmax = x;
      break;

    case 1: 
      smp[pnt] = val;
      if (pnt++ == smp_size) {
        min = 99.0;
        max = -99.0;
        pnt = 0;
      } else {
      /* get sum over last smp_size samples */
      sum = 0.0;
      for(i = 0; i < smp_size; ++i) {
        sum += smp[i];
      }
      /* determine average over last smp_size */
      avg = sum / smp_size;
      /* determine min / max value against average */
      if (val > max) {
        max = val;
      }
      if (val < min) {
        min = val;
      }
      dmin = avg - min;
      dmax = avg - max;
      int x0 = 239; //159;
      int x1 = 239 - ((int) abs(dmin) * M_Bar_Gain) ;
      int x2 = 239 + ((int) abs(dmax) * M_Bar_Gain) ;
      /* three sets of operations, remove current marker, place new marker, */
      /* update last position for average, minimum and maximum */
      tft.fillRect(lavg, y - 6, 2, 7, TFT_WHITE);
      tft.fillRect(x0, y - 6, 2, 7, TFT_BLACK);
      lavg = x0;
      tft.fillTriangle(lmin, y - 6, lmin + 8, y - 6, lmin + 4, y, TFT_WHITE);
      tft.fillTriangle(x1, y - 6, x1 + 8, y - 6, x1 + 4, y, TFT_GREEN);
      lmin = x1;
      tft.fillTriangle(lmax, y, lmax + 8, y, lmax + 4, y - 6, TFT_WHITE);
      tft.fillTriangle(x2, y, x2 + 8, y, x2 + 4, y - 6, TFT_RED);
      lmax = x2;
      
      /* for testing as to find/test scaling */
      #ifdef DEBUG
        char buf1[32];
        tft.setTextColor(TFT_BLACK, TFT_WHITE);
        sprintf(buf1, "%4.2f/%4.2f/%4.2f", min, avg, max);
        tft.drawCentreString(buf1, 80, 160, GFXFF);
      #endif
      break;
    }
  }
}

void stsMeter(int mode, float val) {
  static float last_clr;
  switch (mode) {
    case 0:
      tft.fillRect(382, 135, 3,  18, TFT_WHITE);
      tft.drawRoundRect(385, 132, 90,  24, 3,TFT_WHITE);
      tft.drawRoundRect(386, 133, 88,  22, 1,TFT_WHITE);
      break;
    case 1:
      tft.setFreeFont(STS_FONT);
      static char tmp[16] = {0};
      sprintf(tmp, "Bat %d %%", int(val)); 
      float clr = TFT_GREEN;
      if (val < 70) clr = TFT_YELLOW;  //6.8
      if (val < 50) clr = TFT_ORANGE;  // 6.4
      if (val < 30) clr = TFT_RED;     // 6.2
      if (last_clr != clr) {
        tft.fillRoundRect(387, 134, 86, 20, 0, clr);
        last_clr = clr;
      }
      tft.setTextColor(TFT_BLACK, clr);
      tft.drawCentreString(tmp, 428, 136, GFXFF);
      break;
  }
}

char *binString(unsigned short n, uint8_t size) {

  static char bin[17];
  int x;

  for (x = 0; x < size; x++)
  {
    bin[x] = n & (0x1 << (size - 1)) ? '1' : '0';
    n <<= 1;
  }
  bin[size] = '\0';
  return (bin);
}

double adc_dbm(double adc, int range, bool mode) {
  /* converts measured V to dBm based on polynom constants */
  double *a; /* a as pointer to double array */
  double a_ff = 0.0;
  double a_xx = 0.0;
  double a_vac = 0.0;
  double a_dbm = 0.0;

  #ifndef raw_mode

    a_xx = log10(adc);

    #ifdef dbm_debug
      printf("raw adc %f \n", adc);
      if (isinf(a_xx)) {
        printf("a_xx is inf\n");
      }
      printf("\nADC %e Log     %e\n", adc, a_xx);
    #endif
  
    switch (range) {
      case 0:
        /* range 1 (-5 to 15 dBm) */
        a = (actChan == 0) ? polyBase.a_r1 : (actChan == 1) ? polyBase.b_r1 : polyBase.c_r1;
        break;
      case 1:
        /* range 2 (-25 to -5 dBm) */
        a = (actChan == 0) ? polyBase.a_r2 : (actChan == 1) ? polyBase.b_r2 : polyBase.c_r2;
        break;
      case 2:
        /* range 2 (-60 to -25 dBm) */
        a = (actChan == 0) ? polyBase.a_r3 : (actChan == 1) ? polyBase.b_r3 : polyBase.c_r3;
        break;
      default:
        return -1; 
        break;
    }

    #ifdef dbm_debug
      for( int i = 0; i < 5; i++) {
        printf("A[%d] = %e\n", i, *(a + i) );
      }
    #endif
    // assume polynomial of at least 3 elements
    a_ff = *(a + 0) + *(a + 1) * a_xx + *(a + 2) * pow(a_xx, 2);
    // add optional 4th element id none zero
    if(*(a + 3) != 0.0) {
      a_ff = a_ff + *(a + 3) * pow(a_xx, 3);
    }
    // add optional 5th element id none zero
    if(*(a + 4) != 0.0) {
      a_ff = a_ff + *(a + 4) * pow(a_xx, 4);
    }

    #ifdef dbm_debug
      if (isinf(a_ff)) {
        printf("a_ff is inf @ range %d\n", range);
      }
      printf("FF (%e)\n", a_ff);
    #endif

    a_vac = pow(10, a_ff);

  #else
    a_vac = adc * (3.6 / ADC_RESOLUTION);
  #endif

  if (mode) return a_vac;

  #ifdef dbm_debug
    printf("Vac  %e\n", a_vac);
  #endif

  a_dbm = 10 * log10(pow(a_vac, 2) / (setTerm * 0.001));

  #ifdef dbm_debug
    printf("dBm  %e\n", a_dbm);
  #endif

  return a_dbm;
}

void chk_Touch() {
  uint16_t x = 0, y = 0; // To store the touch coordinates
  /* Pressed will be set true is there is a valid touch on the screen */
  bool pressed = tft.getTouch(&x, &y);
  /* Draw a white spot at the detected coordinates */
  if (pressed) {
    /* btn #1 */
    if ((x > 6 && x < 94) && (y > 286 && y < 314) && !mode_B_A && !mode_C_A) {
      if (actChan < 2) {
        actChan++;
      } else {
        actChan = 0;
      }
      menuBase.actchan = actChan;
      setChannel(actChan);
      fastBtn(1);
    }
    /* btn #2 */
    if ((x >101 && x < 189) && (y > 286 && y < 314)) {
      /*
      if (rangeValue < rangeMax) {
        //printf("\nGn X, Y position = %d, %d, %d\n",x, y, gainValue);
        rangeValue++;
      } else {
        rangeValue = 0;
      }
      gainValue = gains[rangeValue];
      // overruling sample rate
      if (rangeValue == 2) {
        spsRate = 1;
      } else {
        spsRate = 3;
      }
      setBase.spsrate = spsRate;
      pgaControl(gainValue, spsRate);
      autoRng = false;
      fastBtn(2);
      fastBtn(4);
      */
    }
    /* btn #3 */
    if ((x > 196 && x < 284) && (y > 286 && y < 314)) {
      if (setUnit < 1) {
        setUnit++;
      } else {
        setUnit = 0;
      }
      //menuBase.units = setUnit;
      fastBtn(3);
      saveMenuBase();
    }
    /* btn #4 */
    if ((x > 291 && x < 379) && (y > 286 && y < 314)) {
    }
      
    /* btn #5 */
    if ((x > 386 && x < 474) && (y > 286 && y < 314)) {
      zeroStep = 1;
      fastBtn(5);
    }

    if ((x > 348 && x < 374) && (y > 174 && y < 198) && zeroStep != 0) {
      //printf("Step %d\n", zeroStep);
      switch (zeroStep) {
        case 1:
          zeroStep = 2;
          fastBtn(5);
          break;
        case 3:
          zeroStep = 5;
          fastBtn(5);
          break;
        default:
          break;
      }
    }
    if ((x > 260 && x < 292) && (y > 174 && y < 198) && zeroStep != 0) {
      /* zero offset value's */
      off_val[0] = off_val[1] = off_val[2] = 0;
      zeroStep = 4;
      fastBtn(5);
    }

    /* btn #6 */
    if ((x > 386 && x < 474) && (y > 286 - 35 && y < 314 - 35)) {
      avg_Act = !avg_Act;
      avg_Val = 4;
      fastBtn(6);
    }

    /* btn #7 */
    if (mode_B_A || mode_C_A) {
      if ((x > 386 && x < 474) && (y > 286 - 70 && y < 314 - 70)) {
        smp_Fast = !smp_Fast;
        //avg_Val = 4;
        fastBtn(7);
      }
    }
    //printf("\nGn X, Y position = %d, %d\n",x, y);
  }

}

void chk_overLoad(uint32_t adcval) {

  if (adcval > ADC_UNI_MAX) {
    tft.fillRect(385, 156, 90,  52, TFT_BLACK);
      tft.setTextColor(TFT_RED, TFT_WHITE);
      tft.drawCentreString("Overload !", 432, 137, GFXFF);
      static char tmp[16] = {0};
      sprintf(tmp, "%04X", adc.readRegister(REG_STAT)); 
      tft.drawCentreString(tmp, 432, 163, GFXFF);
  } else {
    tft.fillRect(385, 156, 90,  52, TFT_BLACK);
  }
}

void splashscreen() {
  /* splash screen */
  tft.setCursor(40, 30);
  tft.setFreeFont(FSS12);
  tft.print("RF Power meter, multi input");
  tft.setCursor(40, 55);
  tft.print("+23 dBm to - 60dBm");
  tft.setCursor(40, 80);
  static char tmp[32] = {0};
  sprintf(tmp, "Version: H/W %s, F/W %s", hw_ver, sw_ver); 
  tft.print(tmp);
  tft.setFreeFont(STS_FONT);
  tft.setCursor(40, 129);
  tft.print("(c)2022 paul@pro-serv.nl");
  tft.setCursor(40, 149);
  tft.print("(c)2022 Jacques Audet");
  sys_delay_ms(splash_delay);
}

void getAdcCal() {
  /* current calibration registers values */
  printf("Self Cal offset\n");
  printf("  SCOC_SPI (0x09): %u\n", adc.readRegister24(REG_SCOC_SPI));
  printf("  SCOC_ADC (0x17): %u\n", adc.readRegister24(REG_SCOC_ADC));
  printf("Self Cal gain\n");
  printf("  SCGC_SPI (0x0A): %u\n", adc.readRegister24(REG_SCGC_SPI));
  printf("  SCGC_ADC (0x18): %u\n", adc.readRegister24(REG_SCGC_ADC));
  printf("System Cal offset\n");
  printf("  SOC_SPI  (0x07): %u\n", adc.readRegister24(REG_SOC_SPI));
  printf("  SOC_ADC  (0x15): %u\n", adc.readRegister24(REG_SOC_ADC));
  printf("System Cal gain\n");
  printf("  SGC_SPI  (0x08): %u\n", adc.readRegister24(REG_SGC_SPI));
  printf("  SGC_ADC  (0x16): %u\n", adc.readRegister24(REG_SGC_ADC));

  printf("Data reg : %u\n", adc.readRegister24(REG_DATA));
  printf("Status   : %s ", binString(adc.readRegister(REG_STAT), 16));
  setAdcStatus(adc.readRegister(REG_STAT));
  printf("\n\n");
}

void getAdcCntrl() {
  /* print control registers */
  printf("Cntl_1 = %s\n",   binString(adc.readRegister(REG_CTRL1), 8));
  sys_delay_ms(1);
  printf("Cntl_2 = %s\n",   binString(adc.readRegister(REG_CTRL2), 8));
  sys_delay_ms(1);
  printf("Cntl_3 = %s\n",   binString(adc.readRegister(REG_CTRL3), 8));
  sys_delay_ms(1);
  printf("Status = %s\n\n", binString(adc.readRegister(REG_STAT), 16));
  sys_delay_ms(1);
}

void setAdcStatus(int16_t sts) {
  /* print any pending error in status reg */
  if ((sts & 0x0004) != 0) { printf("Data Overrange %s\n",   binString(adc.readRegister(REG_STAT), 16)); }
  if ((sts & 0x0008) != 0) { printf("Gain Overrange %s\n",   binString(adc.readRegister(REG_STAT), 16)); }
  if ((sts & 0x0100) != 0) { printf("Analog Overrange %s\n", binString(adc.readRegister(REG_STAT), 16)); }
  if ((sts & 0x0200) != 0) { printf("Data Read Error %s\n",  binString(adc.readRegister(REG_STAT), 16)); }
  if ((sts & 0x4000) != 0) { printf("Invalid Cal Mode %s\n", binString(adc.readRegister(REG_STAT), 16)); }
  if ((sts & 0X8000) != 0) { printf("'InReset' mode %s\n",   binString(adc.readRegister(REG_STAT), 16)); }
}

void setAdcSetup(uint8_t gain) {

  // execute one self calibration measurement
  adc.execCal(REG_CTRL5, 0x00);
  //getAdcCal();

  /* init ADC with operation mode */
  adc.setMode(CONVERSION_MODE_CONT);
  adc.setDataFormat(DATA_FORMAT_BINARY);
  adc.setMeasuremode(MEASURE_UNIPOLAR);
  adc.setClocktype(CLOCK_INTERNAL);
  adc.setDataMode(DATA_MODE_24BITS);
  adc.setAnalogInputBuffer(false);

  setPgaEnable(gain);

  /* select last executed correction method */
  //printf("Cntrl 5 - 0x%02X\n", AdcCorr);
  printf("Internal calibration enabled !\n");
  adc.writeRegister(REG_CTRL5, AdcCorr);
}

void setChannel(uint8_t Chan) {
  
  if (att_sts[Chan] == true) {
    #ifdef chk_debug
      printf("\nt_chn %d att %s\n\n", Chan, att_sts[Chan] ? "T" : "F");
    #endif
    adc.writeBinDIO(0x70, 0x00 | Chan);
  } else {
    #ifdef chk_debug
      printf("\nf_chn %d att %s\n\n", Chan, att_sts[Chan] ? "T" : "F");
    #endif
    adc.writeBinDIO(0x70, 0x04 | Chan);
  }
}

void setPgaEnable(uint8_t gains) {
  // disabled by 99 --> set to 99 to re-enable direct mode
  if (gains == 99) {  // 
    adc.setPgaEnable(false);
  } else {
    adc.setPgaEnable(true);
    adc.setPgaGain(gains);
  }
}

void pgaControl(uint8_t gain, uint8_t srate)  {
/* ToDo - 13/6/22 removed direct mode */
  setPgaEnable(gain);
  adc.startConversion(srate);
}

void tmrControl(bool mode) { 
  if (!mode) {
    timerAlarmDisable(encodertimer);
  } else {
    timerAlarmEnable(encodertimer);
  }
  sys_delay_ms(10);
}

void adcCalibrateMode(int8_t mode) {

  switch (mode) {
    case 0:
      // internal self adc cal
      //adc.execCal(REG_CTRL5, 0x00);
      //delayMicroseconds(100);
      //adc.writeRegister(REG_CTRL5, 0x0E);
      //setBase.adccorr = 0x0c;
      break;
    case 1:
      // system offset cal
      //adc.execCal(REG_CTRL5, 0x4B);
      //adc.writeRegister(REG_CTRL5, 0x4D);
      //setBase.adccorr = 0x08;
      break;
    case 2:
      /* not yet implemented due to lack of fs value procedure */
      /* also add logic to test if only fs or alseo zero was done */
      //adc.execCal(REG_CTRL5, 0x80);
      break;
    default:
      break;
  }
  adc.startConversion(spsRate);
  saveSettBase();
  /* print calibration registers & status */
  #if (cal_debug)
    printf("Reg 5 %d\n", adc.readRegister(REG_CTRL5));
    getAdcCal();
  #endif
}

void chn_arr_init(int val = 2, bool att = false) {

  for (uint8_t i = 0; i < 3; i++) {
    r_val[i] = val;
    att_sts[i] =  att;
    lastAdc[i] = 1000;

    for (uint8_t  j=0; j<6; j++) {
      avg_smp[j][i] = 0;
    }
    off_val[i] = 0;
  }

  rangeValue = val; // was 2
  actChan = CHAN_A;
  setChannel(actChan);
}

bool between (uint32_t l, uint32_t  h, uint32_t v) {
  return ((v > l) && (v < h)) ? true : false;
}

bool chk_autoRange(uint32_t adcVal, int chan) {
/*
  bool chgd;
  int32_t tmp_delta;

  int r_n = 9;
  int r_l = 9;
  int d_m = 9;
  int r_o;
  bool a_o;
*/
  chgd = false;
  r_o = r_val[chan];
  a_o = att_sts[chan];

  // get delta since last adc reading
  tmp_delta = adcVal - lastAdc[chan];
  tmp_delta = (unsigned) (tmp_delta < 0) ? -tmp_delta : tmp_delta;

  // skip test for new range if delta less than ADC_DELTA counts
  if ((lastAdc[chan] == 0) || (adcVal == 0)) { // added test for adcVal equ 0
    lastAdc[chan] = adcVal;
    return false;
  } else {
    #if (chk_debug)
      printf("chn %d, r_val %d, adc %7d, lst %7d, dlt %7d, lvl %.2f dBm, att %d\n", chan, r_val[chan], adcVal, lastAdc[chan], 
        tmp_delta, adc_dbm(adcVal, r_val[chan], false), att_sts[chan]);
    #endif
    if ((tmp_delta < (ADC_DELTA * 10)) && false) {  // added 
      lastAdc[chan] = adcVal;
      return false;
    }
  }

  // test signal for going up or down since previous sample
  if (adcVal < lastAdc[chan]) {
    d_m = 0;
    /*
     * *** signal is decreasing ***
     * range 3 att F x128 dn 2.362.000 to 1000
     * range 2 att F x4 dn 3.559.000 to 74.000
     * range 1 att T x1 dn 15.390.000 to 1.057.700
     */
    if (adcVal < 74000) {
      r_l = 1;
      if (r_val[chan] == 0){
        att_sts[chan] = false;
        rangeValue = 2;
        chgd = true;
      }
      if (r_val[chan] == 1){
        att_sts[chan] = false;
        rangeValue = 2;
        chgd = true;
      }
      if (r_val[chan] == 2){
        att_sts[chan] = false;
        rangeValue = 2;
        //chgd = true;
      }
    } else if (adcVal < 1057000) {
      r_l = 2;
      if (r_val[chan] == 0){
        if (!att_sts[chan]) {
          rangeValue = 1;
          chgd = true;
        }
      }
      if (r_val[chan] == 1){
        att_sts[chan] = false;
      }
      if (r_val[chan] == 2){
        att_sts[chan] = false;
      }
    } else if (adcVal < 3559000) {
      r_l = 3;
      if (r_val[chan] == 0){
        ;
      }
      if (r_val[chan] == 1){
        att_sts[chan] = false;
      }
      if (r_val[chan] == 2){
        att_sts[chan] = false;
      } 
    }
    r_n = rangeValue;
  } else {
    d_m = 1;
    /*
     * *** signal is increasing ***
     * range 3 att F x128 up 1000 to 2.959.000
     * range 2 att F x4 up 92.620 to 4.130.000
     * range 1 att T x1 up 1.227.000 to 15.390.000
     */
    if (adcVal > 4130000) {
      r_l = 1;
      if (r_val[chan] == 0) {
        att_sts[chan] = true;
        rangeValue = 0;
        chgd = true;
      } else if (r_val[chan] == 1) {
        att_sts[chan] = true;
        rangeValue = 0;
        chgd = true;
      } else if (r_val[chan] == 2) {
        att_sts[chan] = false;
        rangeValue = 1;
        chgd = true;
      }
    } else if ( adcVal > 2959000 ) {
      r_l = 2;
      if (r_val[chan] == 2) {
        att_sts[chan] = false;
        rangeValue = 1;
        chgd = true;
      }
    } else {
      r_l = 3;
    }
    r_n = rangeValue;
  }
  //#if (car_debug)
  if (dm_debug) {
  // debug & state print out helper
    printf("%s_%s.t%d.o%d.n%d, adc %8d, o_att %s, n_att %s, adc %6.2f dBm\n", 
    (chan == 0) ? "A" : (chan == 1) ? "B" : "C", d_m ? "up" : "dn", r_l, r_o, r_n, 
    adcVal, a_o ? "Y" : "N", att_sts[chan] ? "Y" : "N", adc_dbm(adcVal, r_val[chan], 
    false));
  }
  //#endif
  /* save for next compare */
  lastAdc[chan] = AdcResp;
  r_val[chan] = rangeValue;
  setChannel(chan);         // needed as to allow attenuator to be updated
  /* update settings */
  if (chgd) {
    gainValue = gains[rangeValue];
    pgaControl(gainValue, spsRate);
    fastBtn(2);
  }
  return chgd;
}

void dis_BT_Wifi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  btStop();

  esp_wifi_stop();
  esp_bt_controller_disable();
}

void cmd_single(int mde) {
  /* helper function for cmd_single_xxx() */
  single_mode = mde;
  autoRun = false;
  autoRng = false;
  fastBtn(4);
  cmd_Run = false;
  cmd_Step = true;
}

void cmd_single_adc() {
  /* execute single conversion */
  cmd_single(1);
}

void cmd_single_dbm() {
  /* execute single conversion */
  cmd_single(2);
}

void cmd_single_vac() {
  /* execute single conversion */
  cmd_single(3);
}

void cmd_continue() {
  /* execute continuos conversion */
  cmd_Run = false;
  cmd_Step = false;
  autoRng = true;
  fastBtn(4);
  autoRun = true;
  //fastBtn(5);
}

void cmd_channel() {
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    
    if ((int(*arg) >= 65) && (int(*arg) < 68)) {
      actChan = int(*arg) - 65;
      menuBase.actchan = actChan;
      setChannel(actChan);
      //rangeValue = r_val[actChan]; // added for test
      fastBtn(1);
    }
  }
}

void cmd_monitor() {
  /* monitor conversion /w printout every x times */
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 1) && (aNumber < 50)) {
      dsp_cnt = aNumber;
      dbg_mon = true;
    } else {
      dbg_mon = false;
    }
  }
}

void cmd_gain() {
  /* sets gain value from cmd line */
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 1) && (aNumber < 9)) {
      if (autoRng) {
        printf("Auto Range turned off, use 'M' cmd to obtain readout\n");
        autoRng = false;
      }
      //menuBase.autorng = autoRng;
      //saveMenuBase();
      fastBtn(4);
      gainValue = aNumber - 1;
      if (gainValue == 0) {
        rangeValue = 0;
      } else if (gainValue < 3) {
        rangeValue = 1;
      } else {
        rangeValue = 2;
      }
      fastBtn(2);
      adc.setPgaGain(gainValue);
      adc.startConversion(spsRate);
    }
  } else {
    printf("G ?\n");
  }
}

void cmd_load_poly() {

  DynamicJsonDocument doc(json_size);

  printf("Use term emu program to read Json file from serial port\n"); 
  printf("which loads a file @ 9600 baud into flash\n");
  Serial.println("Ready, send file now within 10 sec.");

  Serial.setTimeout(JSON_TIMEOUT);

  delay(10);

  String s = Serial.readStringUntil('#');
    
  while(Serial.available() > 0) {Serial.read();}
  Serial.print("File read, checking content, status: ");
    
  DeserializationError error = deserializeJson(doc, s);
  if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  } else {
    Serial.println("Loaded ok"); // error.c_str()
  }
  JsonArray A_1_Array = doc["A_1"]["value"];
  JsonArray A_2_Array = doc["A_2"]["value"];
  JsonArray A_3_Array = doc["A_3"]["value"];

  JsonArray B_1_Array = doc["B_1"]["value"];
  JsonArray B_2_Array = doc["B_2"]["value"];
  JsonArray B_3_Array = doc["B_3"]["value"];

  JsonArray C_1_Array = doc["C_1"]["value"];
  JsonArray C_2_Array = doc["C_2"]["value"];
  JsonArray C_3_Array = doc["C_3"]["value"];

  backBase.a_r[0]  = A_1_Array[0];
  polyBase.a_r1[0] = A_1_Array[0];
  polyBase.a_r1[1] = A_1_Array[1];
  polyBase.a_r1[2] = A_1_Array[2];
  polyBase.a_r1[3] = A_1_Array[3];
  polyBase.a_r1[4] = A_1_Array[4];

  backBase.a_r[1]  = A_2_Array[0];
  polyBase.a_r2[0] = A_2_Array[0];
  polyBase.a_r2[1] = A_2_Array[1];
  polyBase.a_r2[2] = A_2_Array[2];
  polyBase.a_r2[3] = A_2_Array[3];
  polyBase.a_r2[4] = A_2_Array[4];

  backBase.a_r[2]  = A_3_Array[0];
  polyBase.a_r3[0] = A_3_Array[0];
  polyBase.a_r3[1] = A_3_Array[1];
  polyBase.a_r3[2] = A_3_Array[2];
  polyBase.a_r3[3] = A_3_Array[3];
  polyBase.a_r3[4] = A_3_Array[4];

  backBase.b_r[0]  = B_1_Array[0];
  polyBase.b_r1[0] = B_1_Array[0];
  polyBase.b_r1[1] = B_1_Array[1];
  polyBase.b_r1[2] = B_1_Array[2];
  polyBase.b_r1[3] = B_1_Array[3];
  polyBase.b_r1[4] = B_1_Array[4];

  backBase.b_r[1]  = B_2_Array[0];
  polyBase.b_r2[0] = B_2_Array[0];
  polyBase.b_r2[1] = B_2_Array[1];
  polyBase.b_r2[2] = B_2_Array[2];
  polyBase.b_r2[3] = B_2_Array[3];
  polyBase.b_r2[4] = B_2_Array[4];

  backBase.b_r[2]  = B_3_Array[0];
  polyBase.b_r3[0] = B_3_Array[0];
  polyBase.b_r3[1] = B_3_Array[1];
  polyBase.b_r3[2] = B_3_Array[2];
  polyBase.b_r3[3] = B_3_Array[3];
  polyBase.b_r3[4] = B_3_Array[4];

  backBase.c_r[0]  = C_1_Array[0];
  polyBase.c_r1[0] = C_1_Array[0];
  polyBase.c_r1[1] = C_1_Array[1];
  polyBase.c_r1[2] = C_1_Array[2];
  polyBase.c_r1[3] = C_1_Array[3];
  polyBase.c_r1[4] = C_1_Array[4];

  backBase.c_r[1]  = C_2_Array[0];
  polyBase.c_r2[0] = C_2_Array[0];
  polyBase.c_r2[1] = C_2_Array[1];
  polyBase.c_r2[2] = C_2_Array[2];
  polyBase.c_r2[3] = C_2_Array[3];
  polyBase.c_r2[4] = C_2_Array[4];

  backBase.c_r[2]  = C_3_Array[0];
  polyBase.c_r3[0] = C_3_Array[0];
  polyBase.c_r3[1] = C_3_Array[1];
  polyBase.c_r3[2] = C_3_Array[2];
  polyBase.c_r3[3] = C_3_Array[3];
  polyBase.c_r3[4] = C_3_Array[4];

  // save to flash
  savePolyBase();
  saveBackBase();
  saveCorrBase();
  loadPolyBase();
}

void cmd_load_sett() {

  double temp = 0.0;
  uint16_t tmp1 = 0;

  DynamicJsonDocument doc(json_size);

  printf("Use term emu program to read Json file from serial port\n"); 
  printf("which loads a file @ 9600 baud into flash\n");
  Serial.println("Ready, send file now within 10 sec.");

  Serial.setTimeout(JSON_TIMEOUT);

  delay(10);

  String s = Serial.readStringUntil('#');
    
  while(Serial.available() > 0) {Serial.read();}
  Serial.print("File read, checking content, status: ");
    
  DeserializationError error = deserializeJson(doc, s);
  if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
  } else {
    Serial.println("Loaded ok"); // error.c_str()
  }

  JsonArray Set_Array = doc["Setup"]["value"];
  temp = Set_Array[0];
  setBase.adcres = temp / ADC_RESOLUTION;
  Radc = temp / ADC_RESOLUTION;

  temp = Set_Array[1];
  setBase.batcorr = temp / analogRead(ADC_PIN) * 1000;
  Bat_Ratio = temp / analogRead(ADC_PIN) * 1000;

  setBase.spsrate = (uint16_t) Set_Array[2] & 0x0003;
  // only value's 0, 1, 2 are allowed
  if (setBase.spsrate == 3) {
    setBase.spsrate--;
  }

  Set_Array = doc["Samples"]["value"];
  temp = Set_Array[0];
  setBase.adczero = (int) temp;

  Set_Array = doc["SPS_Delay"]["value"];
  tmp1 = Set_Array[0];
  setBase.sps_i_0 = tmp1;

  tmp1 = Set_Array[1];
  setBase.sps_i_1 = tmp1;

  tmp1 = Set_Array[2];
  setBase.sps_i_2 = tmp1;

  tmp1 = Set_Array[3];
  setBase.sps_i_3 = tmp1;
  // save to flash
  saveSettBase();
  loadSettBase();
}

void cmd_manrange() {
  /* sets active range */
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 1) && (aNumber < 4)) {
      autoRng = false;
      fastBtn(4);
      rangeValue = aNumber - 1;
      gainValue = gains[rangeValue];
      fastBtn(2);
      adc.setPgaGain(gainValue);
//      if (rangeValue == 2) {
        spsRate = 1;
//      } else {
//        spsRate = 3;
//      }
      setBase.spsrate = spsRate;
      adc.startConversion(spsRate);
    }
  } else {
    printf("R ?\n");
  }
}

void cmd_autorange() {
  /* set auto range on */
  autoRng = true;
  fastBtn(4);
}

void cmd_factory() {
  /* reset rf_meter to factory */
  PREF.clear(); 
  sys_delay_ms(500);
  ESP.restart();
}

void cmd_zero_count() {
  /* changes zero sample count */
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 10) && (aNumber <= 50)) {
      setBase.adczero = AdcZero = aNumber;
      // save to flash
      saveSettBase();
      loadSettBase();
    } else {
      printf("Zero Sample count => illegal value (range = 10-50)\n");
    }
  } else {
    printf("AV ?\n");
  }
}

void cmd_units() {
  /* changes main display units (dBm, mVac, mW) */
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 0) && (aNumber < 2)) {
      //menuBase.units = aNumber;
      setUnit = aNumber;
      fastBtn(3);
      saveMenuBase();
    }
  } else {
    printf("U ?\n");
  }
}

void cmd_view() {
  /* provides printout of various flash storage area's */
  int aNumber;
  char *arg;
  char buf3[12];

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg); // Converts a char string to an integer
    switch (aNumber) {
      case 0:
        printf("========== system parameter ====\n");
        printf("Sample rate   %d sps\n", setBase.spsrate);
        printf("Input Term    %d Ohm\n", menuBase.setterm);
        sprintf(buf3, "%4.2f dBm", adc_dbm(low_lvl, 2, false));
        printf ("Noise floor   %s    (cut-off value)\n", (low_lvl  == 0) ? "Off" : buf3);
        printf("Battery       %.4f V\n", setBase.batcorr * analogRead(ADC_PIN) / 1000);
        printf("ADC Vref      %.4f V\n", setBase.adcres * ADC_RESOLUTION);
        printf("Samples used  %d for an 'Averaged Zero' value\n", setBase.adczero);
        break;
      case 1:
        printf("========== A0 correction factors ====\n");
        printf("Sys table  Chan A R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", polyBase.a_r1[0], polyBase.a_r2[0], polyBase.a_r3[0]);
        printf("Correction Chan A R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", corrBase.a_r1_0, corrBase.a_r2_0, corrBase.a_r3_0);
        printf("Sys table  Chan B R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", polyBase.b_r1[0], polyBase.b_r2[0], polyBase.b_r3[0]);
        printf("Correction Chan B R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", corrBase.b_r1_0, corrBase.b_r2_0, corrBase.b_r3_0);
        printf("Sys table  Chan C R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", polyBase.c_r1[0], polyBase.c_r2[0], polyBase.c_r3[0]);
        printf("Correction Chan C R1 A[0] %e R2 A[0] %e R3 A[0] %e\n", corrBase.c_r1_0, corrBase.c_r2_0, corrBase.c_r3_0);
        printf("Active correction mask %03X\n", corrBase.mask_corr);
        break;

      case 2:
        printf("========== menu parameter ====\n");
        printf ("active Chan    %s\n", ((menuBase.actchan + 1) == 3) ? "C" : ((menuBase.actchan + 1) == 2) ? "B" : "A");
        printf ("Auto/Man range %s\n", (menuBase.autorng) ? "On" : "Off");
        printf ("Auto Run       %s\n", (menuBase.autorun) ? "On" : "Off");
        printf ("Offset dBm     %.2f\n", menuBase.off_dbm);
        break;
      case 3:
        printf("========== calibration registers ====\n");
        getAdcCal();
        break;
      case 4:
        printf ("Data Rate 0 (sps) delay    %d\n", setBase.sps_i_0);
        printf ("Data Rate 1 (sps) delay    %d\n", setBase.sps_i_1);
        printf ("Data Rate 2 (sps) delay    %d\n", setBase.sps_i_2);
        printf ("Data Rate 3 (sps) delay    %d\n", setBase.sps_i_3);
        break;
      default:
        break;
    }
  }
}

void cmd_param_1() {
  /* used for initial setting of battery ratio value and adc resolution */
  double aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atof(arg);
    // 2.1529198976e-7 = Resolution = Vavdd / 16777215
    if ((aNumber >= 3.4) && (aNumber < 3.63)) {
      printf("ADC resolution for Vref %e will applied\n", aNumber);
      setBase.adcres = aNumber / ADC_RESOLUTION;
      Radc = aNumber / ADC_RESOLUTION;
    }
  }
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atof(arg);
    // 3.21 = battery correction factor
    if ((aNumber >= 6.0) && (aNumber < 9.0)) {
      printf("Battery ratio for Vbat %.3f will applied\n", aNumber);
      setBase.batcorr = aNumber / analogRead(ADC_PIN) * 1000;
      Bat_Ratio = aNumber / analogRead(ADC_PIN) * 1000;
    }
  }
  saveSettBase();
}

/* sets menu parameter settings */
void cmd_param_2() {
  int aNFC;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNFC = atoi(arg);
    if ((aNFC >= 0) && (aNFC <= 2000)) {
      low_lvl = setBase.min_adc = aNFC;
      saveSettBase();
    }
  }
}

void cmd_sps_dly() {
  int aNumber;
  int aIndex;
  char *arg;
  bool valid = true;
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber >= 0) && (aNumber < 4)) {
      aIndex = aNumber;
    } else {valid = false;}
    arg = sCmd.next();
    if (arg != NULL) {
      aNumber = atoi(arg);
      if ((aNumber >= 1) && (aNumber < 50)) {
        ;
      } else { valid = false; }
    }
  }
  if (valid) {
    switch (aIndex) {
      case 0:
        setBase.sps_i_0 = aNumber;
        break;
      case 1:
        setBase.sps_i_1 = aNumber;
        break;
      case 2:
        setBase.sps_i_2 = aNumber;
        break;
      case 3:
        setBase.sps_i_3 = aNumber;
        break;
    }
    saveSettBase();
    loadSettBase();
  } else {
      printf("Cmd like 'SD X Y' (x=SPS item (0-3), y=value (1-9)\n");
  }
  saveSettBase();
  loadSettBase();
}
/*
void cmd_param_3() {
  // set the imput channel termination 
  int aNumber;
  bool valid = true;
  int aTmp = 0;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if ((aNumber != 0) && (aNumber != 50) && (aNumber != 75)) valid = false;
    if (aNumber == 50) aTmp = aTmp | 0x10;
    if (aNumber == 50) aTmp = aTmp | 0x20;
    arg = sCmd.next();
    if (arg != NULL) {
      aNumber = atoi(arg);
      if ((aNumber != 0) && (aNumber != 50) && (aNumber != 75)) valid = false;
      if (aNumber == 50) aTmp = aTmp | 0x04;
      if (aNumber == 75) aTmp = aTmp | 0x08;
      arg = sCmd.next();
      if (arg != NULL) {
        aNumber = atoi(arg);
        if ((aNumber != 0) && (aNumber != 50) && (aNumber != 75)) valid = false;
        if (aNumber == 50) aTmp = aTmp | 0x01;
        if (aNumber == 75) aTmp = aTmp | 0x02;
      } else {
        valid = false;
      }
    } else {
      valid = false;
    }
  } else {
    valid = false;
  }
  if (valid) {
    setBase.term_50 = aTmp;
    term_50 = aTmp;
    printf ("Input Termination   Chan C = %s, chan B = %s, chan A = %s\n", 
      ((setBase.term_50 & 0x20) == 0x20) ? "75" : ((setBase.term_50 & 0x10) == 0x10) ? "50" : "--",
      ((setBase.term_50 & 0x08) == 0x08) ? "75" : ((setBase.term_50 & 0x04) == 0x04) ? "50" : "--", 
      ((setBase.term_50 & 0x02) == 0x02) ? "75" : ((setBase.term_50 & 0x01) == 0x01) ? "50" : "--");    
  } else {
      printf("Command format should be 'PT xx yy zz' (where xx/yy/zz is 0, 50 or 75)\n");
  }
  saveSettBase();
}
*/
void cmd_debug_mode() {
  double aNumber;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);
    if (aNumber == 0) {
      dm_debug = false;
    } else {
      dm_debug = true;
    }
  }
}

void cmd_cx_ry_cal() {
  /* used for dBm Offset of A[0] value by channel & range */
  double aNumber;
  int aChan;
  int aRange;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL)  {
      // for  selected chan update correction
    if ((int(*arg) >= 65) && (int(*arg) < 68)) {
      aChan = int(*arg) - 65;
      arg = sCmd.next();
      if (arg != NULL) {
        aRange = atoi(arg);
        if ((aRange >= 1) && (aRange < 4)) {
          arg = sCmd.next();
          if (arg != NULL) {
            aNumber = atof(arg); // Converts a char string to an integer
            if (aNumber == 0.0) {
              // set to zero & restore original polynomial value
              switch (aChan) {
                case 0:
                  if (aRange == 1) {
                    corrBase.a_r1_0 = 0.0;
                    polyBase.a_r1[0] = backBase.a_r[0];
                  }
                  if (aRange == 2) {
                    corrBase.a_r2_0 = 0.0;
                    polyBase.a_r2[0] = backBase.a_r[1];
                  }
                  if (aRange == 3) {
                    corrBase.a_r3_0 = 0.0;
                    polyBase.a_r3[0] = backBase.a_r[2];
                  }
                  corrBase.mask_corr = corrBase.mask_corr & ~(0x01 << (aRange - 1));
                  break;
                case 1:
                  if (aRange == 1) {
                    corrBase.b_r1_0 = 0.0;
                    polyBase.b_r1[0] = backBase.b_r[0];
                  }
                  if (aRange == 2) {
                    corrBase.b_r2_0 = 0.0;
                    polyBase.b_r2[0] = backBase.b_r[1];
                  }
                  if (aRange == 3) {
                    corrBase.b_r3_0 = 0.0;
                    polyBase.b_r3[0] = backBase.b_r[2];
                  }
                  corrBase.mask_corr = corrBase.mask_corr & ~(0x01 << (aRange - 1 + 4));
                  break;
                case 2:
                  if (aRange == 1) {
                    corrBase.c_r1_0 = 0.0;
                    polyBase.c_r1[0] = backBase.c_r[0];
                  }
                  if (aRange == 2) {
                    corrBase.c_r2_0 = 0.0;
                    polyBase.c_r2[0] = backBase.c_r[1];
                  }
                  if (aRange == 3) {
                    corrBase.c_r3_0 = 0.0;
                    polyBase.c_r3[0] = backBase.c_r[2];
                  }
                  corrBase.mask_corr = corrBase.mask_corr & ~(0x01 << (aRange - 1 + 8));
                  break;
              }
              savePolyBase();
              loadPolyBase();
              printf("A[0] for chan %c, range %d = %.2f dBm Offset removed.\n", 
                  (char) (aChan + 65), aRange, aNumber);
            } else  if ((aNumber >= -10.0) && (aNumber < 10.0)) {
              switch (aChan) {
                case 0:
                  if (aRange == 1) corrBase.a_r1_0 = aNumber;
                  if (aRange == 2) corrBase.a_r2_0 = aNumber;
                  if (aRange == 3) corrBase.a_r3_0 = aNumber;
                  corrBase.mask_corr = corrBase.mask_corr | 0x01 << (aRange - 1);
                  break;
                case 1:
                  if (aRange == 1) corrBase.b_r1_0 = aNumber;
                  if (aRange == 2) corrBase.b_r2_0 = aNumber;
                  if (aRange == 3) corrBase.b_r3_0 = aNumber;
                  corrBase.mask_corr = corrBase.mask_corr | 0x01 << (aRange - 1 + 4);
                  break;
                case 2:
                  if (aRange == 1) corrBase.c_r1_0 = aNumber;
                  if (aRange == 2) corrBase.c_r2_0 = aNumber;
                  if (aRange == 3) corrBase.c_r3_0 = aNumber;
                  corrBase.mask_corr = corrBase.mask_corr | 0x01 << (aRange - 1 + 8);
                  break;
              }
              printf("A[0] for chan %c, range %d = %.6f dBm Offset applied.\nUse same command with 0.0 value to undo this dBm Offset\n", 
                  (char) (aChan + 65), aRange, aNumber);
            }
          }
          initCorrBase();
          saveCorrBase();

        } else {
          printf("A[0] => illegal range selection (use 1,2,3)\n");
        }
      }
    } else {
      printf("A[0] => illegal chan selection (use A,B,C)\n");
    }
  }
}

void unrecognized(const char *command) {
  /* provides overview of available commands */
  printf("Valid (uppercase only) commands & parameters are:\n");
  printf("  A           Continuous ADC conversion\n");
  printf("  A0 X y z    dBm Offset for A[0], X = A, B or C, y = range (1-3), z = value\n"); 
  printf("  C X         Channel select where X = A, B or C\n");
  printf("  D x         Debug ADC printout, x = interval (1 - 49), to stop use x = 0\n");
  printf("  G x         Gain, where x = gain (1 - 8)\n");
  printf("  LP          Load Polynomial data to NVS storage\n");
  printf("  LS          Load Vref, Vbat, Sample Rate, # Samples & SPS delay data to NVS storage\n");
  printf("  AV x        # of samples used for Zero Offset\n");
  printf("  M           single ADC conversion\n");
  printf("  MD          single dBm conversion\n");
  printf("  MV          single Vac conversion\n");
  printf("  NF x        Noise Floor value, where x is range (0 (Off) < 200)  default = 30\n"); //(700 = -60 dBm)\n");
  printf("  PS x y      x = ADC Vref value (default = 3.6V), y = Battery voltage\n");
//  printf("  PT xx yy zz xx = chan C 0/50/75, yy = chan B 0/50/75, zz = chan A 0/50/75  (50 = terminated)\n");
  printf("  R x         range, where x = range (1 - 3)\n");
  printf("  RO          Auto Range on\n");
  printf("  RST         Resetting to factory, will need recal\n");
  //printf("  TC          Touch Screen Calibration, handle with care !\n");
  printf("  U x         Display units, default 0, 0 = dBm, 1 = mW, (2 = uV --> under construction !)\n");
  printf("  V x         Flash value's: 0 - system, 1 - A[0] correction, 2 - menu, 3 - calibration reg's, 4 - sps delays\n");
}

void setup() {

Disable_flg = false;

pinMode(ADC_DRDY, INPUT_PULLUP);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
pinMode(15, OUTPUT);
pinMode(ADC_SYNC, OUTPUT);          // added in sw v1.5b2
digitalWrite(ADC_SYNC, LOW);        // should be set low for normal operation

pinMode(21, OUTPUT);
digitalWrite(21, LOW); 
pinMode(22, OUTPUT);
digitalWrite(22, LOW); 
pinMode(15, OUTPUT);
digitalWrite(15, LOW); 
/* to besure it's off */
dis_BT_Wifi();

/* only needed to totally erase preferences memory storage */
#if (nvs_erase)
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init(); // initialize the NVS partition.
  while(true){};
#endif

  /* init debug serial port */
  Serial.flush();
  Serial.begin(9600);
  
  tft_ini_cal();
  splashscreen();
  tft_ini_cal();

  /* init VSPI interface for ADC */
  adc.begin(ADC_CLK, ADC_MISO, ADC_MOSI, ADC_CS, ADC_DRDY); // CLK, MISO, MOSI, CS, DRDY.

  /* init output #1 & #2, init various array's, select chan #1
     changed to high level init @ startup as to avoid overload */
  chn_arr_init(1, false);

  /* setup & start timer */
  encodertimer = timerBegin(0, 80, true);
  timerAttachInterrupt(encodertimer, &onTimer, true);
  timerAlarmWrite(encodertimer, 1000, true);

  //delayMicroseconds(0);
  timerAlarmEnable(encodertimer);
  attachInterrupt(ADC_DRDY, onAdc, RISING);

  /* draw initial parts on tft screen */
  digitalMeter(0, 0); // draw init digital meter
  barMeter(0, 0.0);     // draw init bar meter
  stsMeter(0, 0.0);     // draw init status / battery
  fastBtn(0);

  /* Preferences init */
  PREF.begin("RFMETER", false);

  bool flg = true;
  if (!loadSettBase()) {
    flg = false;
  }
  initSettBase();
  // note this needs to be/stay in rigth sequence
  if (!loadPolyBase()) {
    flg = false;
  }
  if (!loadCorrBase()) {
    flg = false;
  }
  loadBackBase();
  initCorrBase();
  loadMenuBase();
  initMenuBase();
  if (!flg) {
    printf("Execute the 'RST' and 'LP' and/or 'LS' commands to initialize RF_Meter\n");
    digitalMeter(9, 1);
  }
  printf("Version: H/W %s, F/W %s\n", hw_ver, sw_ver); 
  /* init ADC settings & gain */
  setAdcSetup(gainValue);

  /* setup screen based menu */
  initial_menu();

  /* get current battery level */
  Bat_lvl = getBattery(ADC_PIN);
  if (Bat_lvl > 70) {
    printf("Battery = %4.0f %%\n", Bat_lvl);
  } else if (Bat_lvl < 30) {
    printf("Battery = %4.0f %%, charge battery before usage !\n", Bat_lvl);
  } else {
    printf("Battery = %4.0f %%, you may need to charge it !\n", Bat_lvl);
  }
  stsMeter(1, Bat_lvl);

#if (ply_debug)
  printf("Testing @ 100k /w range 3 %4.2f dBm\n",adc_dbm(1.0e5, 2, false)); // -40 dBm
  printf("Testing @ 1M   /w range 2 %4.2f dBm\n",adc_dbm(1.0e6, 1, false)); // -14 dBm
  printf("Testing @ 10M  /w range 1 %4.2f dBm\n",adc_dbm(1.0e7, 0, false)); //  11 dBm
#endif

//printf("Testing 600 counts @ range 3 = %4.2f dBm, %4.6f mV\n",adc_dbm(600, 2, false),adc_dbm(6600, 2, true)*1000);

  sCmd.addCommand("A", cmd_continue);
  sCmd.addCommand("A0", cmd_cx_ry_cal);
  sCmd.addCommand("C", cmd_channel);
  sCmd.addCommand("D", cmd_monitor);
  sCmd.addCommand("G", cmd_gain);
  sCmd.addCommand("LP", cmd_load_poly);
  sCmd.addCommand("LS", cmd_load_sett);
  sCmd.addCommand("AV", cmd_zero_count);
  sCmd.addCommand("M", cmd_single_adc);
  sCmd.addCommand("MD", cmd_single_dbm);
  sCmd.addCommand("MV", cmd_single_vac);
  sCmd.addCommand("PS", cmd_param_1);
  sCmd.addCommand("NF", cmd_param_2);
  sCmd.addCommand("R", cmd_manrange);
  sCmd.addCommand("RO", cmd_autorange);
  sCmd.addCommand("RST", cmd_factory);
  sCmd.addCommand("SD", cmd_sps_dly);
  sCmd.addCommand("DM", cmd_debug_mode);
  //sCmd.addCommand("TC", touch_calibrate);
  sCmd.addCommand("U", cmd_units);
  sCmd.addCommand("V", cmd_view);
  sCmd.setDefaultHandler(unrecognized);

}

void loop() {
/*
  int scale = 0;
  int *g; // r as pointer to int
  */
  g = G;  // r now points to array G
/*
  uint64_t time_ms = 0;

  static uint64_t lastreadadc = time_ms;
  static uint64_t lastreadencoder = time_ms;
  static uint64_t lastreadButton = time_ms;
  static uint64_t lastreadtouch = time_ms;
  static uint64_t lastreadbattery = time_ms;
  static uint64_t lastdelayedadc = time_ms;
  static uint16_t act_cnt = 0;
  static uint16_t adc_cnt = 0;                // used for adc being inactive too long
  static uint16_t lst_cnt = 0;
  static double dbm_x = 0.0;
  static double dbm_y = 0.0;
  */
  // enable self calibration value for compensation
  //adc.writeRegister(REG_CTRL5, 0x0C);
  // start conversions

  adc.startConversion(spsRate);

  //runable = false;
  while (runable) {
    /* init run time timers for none-blocking update / service */
    time_ms = esp_timer_get_time()/1000;

    /* one time read of ADC value if data valid */
    if (adc_rdy && !cal_int) {
      sys_delay_ms(1);
      AdcResp =  adc.readADC();
      /* implement range 3 offset value */
      if (off_val[actChan] != 0 && (r_val[actChan] + 1) == 3) { AdcResp -= off_val[actChan]; }
      /* implement data below dead zone value */
      if (low_lvl != 0 && (r_val[actChan] + 1) == 3 && AdcResp < low_lvl) {AdcResp = 30;}

      portENTER_CRITICAL_ISR(&mux);
      adc_rdy = false;
      portEXIT_CRITICAL_ISR(&mux);
      conv_rdy = true;
      adc_cnt++;
    }

    /* routne to gather average offset for all channels */
    if (adc_rdy && cal_int) {

      portENTER_CRITICAL_ISR(&mux);
      adc_rdy = false;
      portEXIT_CRITICAL_ISR(&mux);
      switch (cal_stp) {
        case 0:
          /* init sample array, move to next sequence step when done */
          if (off_Chan(3, 0)) {
            cal_stp++;
          }
          break;
        case 1:
          /* get average value for active channel move to next step when done */
          AdcResp =  adc.readADC();
          if (off_Chan(actChan, AdcResp)) {
            cal_stp++;
          }
          adc_cnt++;
          break;
        case 2:
          /* we are done, now init & update button text */
          cal_stp = 0;
          zeroStep = 3;
          fastBtn(5);

          printf("Using offset for channel %c, value %d\n", (char) (actChan + 65), off_val[actChan]);

          AdcResp =  adc.readADC();
          cal_int = false;

          break; 
        default:
          break;
      }

    }

    if (conv_rdy && !(mode_B_A || mode_C_A)) {
      if(!avg_Act) {
        // Todo added below !!!!!!
        setChannel(actChan);
        if(!chk_autoRange(AdcResp, actChan)) {
          vac = adc_dbm(AdcResp, r_val[actChan], true); // example alternative att_sts[actChan] ? AdcResp * 5 : AdcResp rangeValue
          dbm = adc_dbm(AdcResp, r_val[actChan], false);
          digitalMeter(2, relMode);

          /* show measured rf signal somewhere ! */
          if ((++act_cnt > dsp_cnt) and (dbg_mon)) {
            printf("ADC Chan %c, Raw %d, Vac %e, R %d, G %dx, dBm %e\n", 
            (char) (actChan + 65),
            AdcResp, vac, r_val[actChan] + 1, *(g + gainValue), dbm);
            act_cnt = 0;
          }

          if (cmd_Step) {
            switch (single_mode) {
              case 1:
                printf("%d,%d\n", AdcResp, r_val[actChan] + 1);
                break;
              case 2:
                printf("%.2f,%d\n", dbm, r_val[actChan] + 1);
                break;
              case 3:
                scale = (vac < 0.001) ? 3 : (vac < 1) ?  2 : 1;
                printf("%.2f,%d\n", (scale == 3) ? vac * 1000000 : (scale == 2) ? vac * 1000 : vac, r_val[actChan] + 1);
                break; 
              default:
                break;          
            }
            cmd_Step = false;
          }

          /* show signal noise distribution */
          barMeter(1, dbm);
        }
        avg_idx = 0;

      } else {
        if(!chk_autoRange(AdcResp, actChan)) {
          if (avg_idx == avg_Val) {
            AdcResp = 0;
            for(int8_t i = 0; i < avg_Val; ++i) {
              AdcResp += avg_smp[i][actChan];
              //printf("%d, %d , %d\n", i, avg_smp[i][actChan], actChan);
            }
            AdcResp = AdcResp / avg_Val;
            //printf("%d\n", AdcResp);
            vac = adc_dbm(AdcResp, r_val[actChan], true);
            dbm = adc_dbm(AdcResp, r_val[actChan], false);
            digitalMeter(2, relMode);

            /* show measured rf signal somewhere ! */
            if ((++act_cnt > dsp_cnt) and (dbg_mon)) {
              printf("ADC Chan %c, Avg %d, Vac %e, R %d, G %dx, dBm %e\n", 
              (char) (actChan + 65),
              AdcResp, vac, r_val[actChan] + 1, *(g + gainValue), dbm);
              act_cnt = 0;
            }

            if (cmd_Step) {
              switch (single_mode) {
                case 1:
                  printf("%d,%d\n", AdcResp, r_val[actChan] + 1);
                  break;
                case 2:
                  printf("%.2f,%d\n", dbm, r_val[actChan] + 1);
                  break;
                case 3:
                  scale = (vac < 0.001) ? 3 : (vac < 1) ?  2 : 1;
                  printf("%.2f,%d\n", (scale == 3) ? vac * 1000000 : (scale == 2) ? vac * 1000 : vac, r_val[actChan] + 1);
                  break; 
                default:
                  break;          
              }
              cmd_Step = false;
            }

            /* show signal noise distribution */
            barMeter(1, dbm);

            avg_idx = 0;
          } else {
              avg_smp[avg_idx++][actChan] = AdcResp;
          }
        }
      }
      conv_rdy = false;
    }

    if (conv_rdy && (mode_B_A || mode_C_A)) {

    //  if(!chk_autoRange(AdcResp, actChan)) {
        if (!a_x_mode) {
          //printf("*** A_Chan = %s & Step %d ***\n", a_x_mode ? "T" : "F", dual_step);
          switch (dual_step) {
            // select channel A
            case 0:
              actChan = CHAN_A;
              setChannel(actChan);
              dly_cnt = sps_delay[spsRate];
              dual_step++;
              //printf("A0__Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
              lastdelayedadc = time_ms;
              break;
            case 1:
              if(!chk_autoRange(AdcResp, CHAN_A)) {
                if (dly_cnt > 0) {
                  //printf("A1a_Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                  dly_cnt--;
                } else {
                  dual_step++;
                  //printf("A1b_Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                }
              }
              break;
            case 2:
              if(!chk_autoRange(AdcResp, CHAN_A)) {
                // todo process chan data, check noise correction
                if (low_lvl != 0 && r_val[CHAN_A] == 2 && AdcResp < low_lvl) {AdcResp = 0;}
                dbm_x = adc_dbm(AdcResp, r_val[CHAN_A], false);
                #if (dch_debug)
                  printf("A_Testing /w range %d %4.2f dBm\n", r_val[CHAN_A] + 1, dbm_x);
                  printf("val_a %.2f, raw %d, rng %d\n\n", dbm_x, AdcResp, r_val[0] + 1);
                #endif
                actChan = mode_B_A ? CHAN_B : CHAN_C;
                setChannel(actChan);
                a_x_mode = true;//!a_x_mode;
                  //printf("A2__Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                dual_step = 0;
              }
              break;
            default:
              break;
          }
        } else {
          //printf("*** X_Chan = %s & Step %d *** \n", a_x_mode ? "T" : "F", dual_step);
          switch (dual_step) {
            // select channel B || C
            case 0:
              if(!chk_autoRange(AdcResp, mode_B_A ? CHAN_B : CHAN_C)) {
                dly_cnt = sps_delay[spsRate];
                dual_step++;
               //printf("B0__Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                lastdelayedadc = time_ms;
              }
              break;
            case 1:
              if(!chk_autoRange(AdcResp, mode_B_A ? CHAN_B : CHAN_C)) {
                if (dly_cnt > 0) {
                  //printf("B1a_Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                  dly_cnt--;
                } else {
                  dual_step++;
                  //printf("B1b_Cnt %d, mSec %12d\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                }
              }
              break;
            case 2:
              if(!chk_autoRange(AdcResp, mode_B_A ? CHAN_B : CHAN_C)) {    
                // todo process chan data, check noise correction
                if (low_lvl != 0 && r_val[mode_B_A ? CHAN_B : CHAN_C] == 2 && AdcResp < low_lvl) {AdcResp = 0;}
                dbm_y = adc_dbm(AdcResp, r_val[mode_B_A ? CHAN_B : CHAN_C], false);
                #if (dch_debug)
                  printf("B_Testing /w range %d %4.2f dBm\n", r_val[mode_B_A ? CHAN_B : CHAN_C], dbm_y);
                  printf("val_x %.2f, raw %d, rng %d\n\n", dbm_y, AdcResp, r_val[mode_B_A ? CHAN_B : CHAN_C] + 1);
                  printf("R_val_a %.2f, r_a %d, val_x %.2f, r_x %d, val_x-a %.2f\n\n",dbm_x, r_val[0] + 1, dbm_y, r_val[mode_B_A ? CHAN_B : CHAN_C] + 1, dbm_y - dbm_x);
                #endif
                dbm_a = dbm_x;
                dbm_b = dbm_y;

                digitalMeter(3, relMode);
                //actChan = CHAN_A;
                //setChannel(actChan);
                a_x_mode = false;//!a_x_mode;
                  //printf("B2__Cnt %d, mSec %12d\n\n", dly_cnt, time_ms - lastdelayedadc);
                  lastdelayedadc = time_ms;
                dual_step = 0;
              }
              break;
            default:
              break;
          }
        }
      //}
      #if (chk_debug)
        // marker @ sample interval
        digitalWrite(22, HIGH); 
        sys_delay_ms(1);
        digitalWrite(22, LOW); 
      #endif
      conv_rdy = false;
    }

    sys_delay_ms(1);

    /* check adc still being active */
    if(time_ms >= (lastreadadc + 5000)) {
      lastreadadc = time_ms;
      if (lst_cnt != adc_cnt) {
        lst_cnt = adc_cnt;
      } else {
        adc.startConversion(spsRate);
      }
    }

    /* handle battery value */
    if(time_ms >= (lastreadbattery + 5000)) {
      lastreadbattery = time_ms;
      stsMeter(1, getBattery(27));
    }

    /* handle encoder */
    if(time_ms >= (lastreadencoder + 10)) {
      lastreadencoder = time_ms;
      service_encoder();
    }

    /* handle rotary push button */
    if(time_ms >= (lastreadButton + 1)) {
      lastreadButton = time_ms;
      service_button();
    }

    /* Menu refresh service */
    service_update();
    
    /* check touch screen area */
    if(time_ms >= (lastreadtouch + 100)) {
      lastreadtouch = time_ms;
      chk_Touch();
    }

    /* Process pending serial commands */
    sCmd.readSerial();
    
  }
}