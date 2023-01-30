#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Menu.h>

#define MENU_BASE_X 160
#define MENU_BASE_Y 134
#define MAX_PROFILES 9
#define MENU_ITEMS_VISIBLE 6
#define MENU_ITEM_HEIGHT 24
#define PROFILE_LENGTH 20
#define TFT_GREY 0x5AEB

typedef struct {
  const Menu::Item_t *mi;
  uint8_t pos;
  bool current;
} LastItemState_t;

typedef struct {
  int16_t spsrate;
  int16_t min_adc;
  float   batcorr;
  float   adcres;
  int16_t adccorr;
  int16_t adczero;
  int16_t sps_i_0;
  int16_t sps_i_1;
  int16_t sps_i_2;
  int16_t sps_i_3;
} Sett_t;

typedef struct {
  double a_r1[5];   // chan_range_polynome
  double a_r2[5];
  double a_r3[5];

  double b_r1[5];   // chan_range_polynome
  double b_r2[5];
  double b_r3[5];

  double c_r1[5];   // chan_range_epolynome
  double c_r2[5];
  double c_r3[5];

  double r_a[3];    // this array holds the three a_rx[0], b_rx[0], c_rx[0] backup values
  double r_b[3];
  double r_c[3];
} Poly_t;

typedef struct {
  double a_r[3];
  double b_r[3];
  double c_r[3];
} Back_t;

typedef struct {
  uint16_t mask_corr;
  double  a_r1_0;  // chan_range_polynome
  double  a_r2_0;
  double  a_r3_0;
  double  b_r1_0;
  double  b_r2_0;
  double  b_r3_0;
  double  c_r1_0;
  double  c_r2_0;
  double  c_r3_0;
} Corr_t;

typedef struct {
  uint8_t actchan;
  int16_t autorng;
  uint8_t autorun;
  int16_t setterm;
  int8_t  units;
  float  off_dbm;
} Menu_t;

typedef struct {
int16_t actb_a;
int16_t actc_a;
int16_t actrel;
} Switch_t;

//prototypes
void IRAM_ATTR onTimer();
double getBattery(int pin);
void clearLastMenuItemRenderState();
bool menuExit(const Menu::Action_t a);
bool menuDummy(const Menu::Action_t a);
bool editFloatSetting_1(const Menu::Action_t action);
bool editFloatSetting_2(const Menu::Action_t action);
void renderMenuItem(const Menu::Item_t *mi, uint8_t pos);
bool kbd_set_1(const char *label, char *tmpbuf, uint32_t length, bool init, bool trigger);
bool kbd_set_2(const char *label, char *tmpbuf, uint32_t length, bool init, bool trigger);
bool editNumericalValue(const Menu::Action_t action);
void makeSettBase();
void makeCorrBase();
void makePolyBase();
void makeBackBase();
void makeMenuBase();
bool saveSettBase();
bool saveCorrBase();
bool savePolyBase();
bool saveBackBase();
bool saveMenuBase();
bool loadSettBase();
bool loadCorrBase();
bool loadPolyBase();
bool loadMenuBase();
void initSettBase();
void initCorrBase();
void initMenuBase();
void getItemValuePointer(const Menu::Item_t *mi, float **d, int16_t **i);
bool SetRelative(const Menu::Action_t action);
bool SetDifSrc(const Menu::Action_t action);
bool isProfSetting(const Menu::Item_t *mi);
bool isNegSetting(const Menu::Item_t *mi);
int8_t idxTest(const Menu::Item_t *mi);
bool getItemValueLabel(const Menu::Item_t *mi, char *label);
void IRAM_ATTR service_encoder(void);
void service_button();
void service_update();
void initial_menu();
void IRAM_ATTR isr_encoder(void);
void fastBtn(uint16_t mode);
void touch_calibrate();
void tft_ini_cal();
void digitalMeter(int mode, double val_1, double val_2);
bool off_Chan (int chan, int32_t val);
void barMeter(int mode, double val);
void stsMeter(int mode, float val);
char *binString(unsigned short n, uint8_t size);
double adc_dbm(double adc, int range, bool mode);
void chk_Touch();
void chk_overLoad(uint32_t adcval);
void splashscreen();
void getAdcCal();
void getAdcCntrl();
void digitalMeterHelper(int32_t x, int32_t y, int unit);
void setAdcStatus(int16_t sts);
void setAdcSetup(uint8_t gain);
void setChannel(uint8_t data);
void pgaControl(uint8_t gain, uint8_t srate);
void tmrControl(bool mode);
//bool execInternCal(const Menu::Action_t action);
//bool execSysCal(const Menu::Action_t action);
void adcCalibrateMode(int8_t mode);
bool chk_autoRange();
void dis_BT_Wifi();
void cmd_single();
void cmd_single_adc();
void cmd_single_dbm();
void cmd_single_vac();
void cmd_continue();
void cmd_channel();
void cmd_monitor();
void cmd_gain();
void cmd_load_poly();
void cmd_load_sett();
void cmd_autorange();
void cmd_factory();
void cmd_units();
//void cmd_range();
//void cmd_sample();
void cmd_view();
void cmd_param_1();
void cmd_param_2();
//void cmd_param_3();
void cmd_cx_ry_cal();
void setPgaEnable(uint8_t gains);
void chn_arr_init(int val, bool att);
void unrecognized(const char *command);
#endif