#include "mruby.h"
#include <stddef.h>


#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/hash.h"
#include "mruby/string.h"
#include "mruby/variable.h"
//#include "Utils/KeyBoardMan.h"

#include "gedi.h"

GEDI_KBD_e_Key eKey_w;

#if MRUBY_RELEASE_NO < 10000
  #include "error.h"
#else
  #include "mruby/error.h"
#endif

GEDI_WIFI_st_Info *pstNet;
GEDI_WIFI_st_Info *wifi_conf;



static mrb_value
mrb_wifi_start(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret=0;
  /* dummy function */
  return mrb_fixnum_value(ret);
}

/*Turn on/off the power 1 - on 0 - off*/
static mrb_value
mrb_wifi_power(mrb_state *mrb, mrb_value klass)
{
  mrb_int state, ret;
  mrb_get_args(mrb, "i", &state);

  if(state)
  {
	  do
	  {
		  ret = GEDI_WIFI_Enable ();
		  GEDI_CLOCK_Delay(500);
	  }while(ret!=0);
  }
  else
  {
	  ret = GEDI_WIFI_Disable ();
  }

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_wifi_connect(mrb_state *mrb, mrb_value klass)
{
  mrb_value password, essid, bssid, channel, mode, authentication, cipher;
  const char *sPassword, *sEssid, *sBssid, *sChannel, *sCipher, *sMode, *sAuthentication;

//  int timeout=60000;
//  mrb_int ret = 0;
//
//  GEDI_WIFI_e_Status * wifStatus;
//  GEDI_WIFI_st_Info *psInfo;
//  GEDI_WIFI_e_Status *WifiStatus;
//  char pass[36]="";
//  char Conectado = 0;
//  int Line = 16;
//  char BUF[256];
//  int pos = 0;
//
//  UINT uiSize;
//
//  GEDI_WIFI_Status (&WifiStatus);
//
//
//  switch((intptr_t)WifiStatus)
//  {
//
//  case GEDI_WIFI_STATUS_AP_CONNECTED:
//	  ret = 0;
//	  return mrb_fixnum_value(ret);
//
//  default:
//      break;
//
//  }
//
//  /* TODO: Ler configuração do arquivo de config */
//  GEDI_LCD_Clear();
//  GEDI_LCD_DrawString(0,Line*0,12,16,"Lista de Redes:");
//  GEDI_WIFI_Scan ();
//
//  do{
//	  GEDI_WIFI_Status(&wifStatus);
//	  GEDI_CLOCK_Delay(500);
//  }while(wifStatus==8);
//
//  GEDI_WIFI_APListGet ((GEDI_WIFI_st_Info **)&psInfo, &uiSize);
//
//  pstNet = (GEDI_WIFI_st_Info *)psInfo;
//  wifi_conf = pstNet;
//  char Essid[10][36];
//
//  UINT s = 0,l=0;
//
//  for(s=0;s<uiSize; s++) {
//
//	  sprintf(BUF,"%d. %s",s,pstNet->ESSID);
//	  GEDI_LCD_DrawString(0,Line*(1+s),12,16,BUF);
//	  pstNet++;
//  }
//
//  GEDI_LCD_DrawString(0,Line*(1+s),12,16,"Escolha a rede:");
//  pos = KeyBoard_Get_Number();
//  sprintf(BUF,"Escolha a rede:%d", pos);
//  GEDI_LCD_DrawString(0,Line*(1+s++),12,16,BUF);
//
//
//  for(l=0;l<pos;l++)
//  {
//	  wifi_conf++;
//  }
//
//  GEDI_LCD_Clear();
//  sprintf(BUF,"Conectando a -> %s",wifi_conf->ESSID);
//  GEDI_LCD_DrawString(0,Line*0,12,16,BUF);
//  GEDI_CLOCK_Delay(3000);
//
//  char myEssid[36] = "teste";
//  char myPass[32+1] = "1234567890";
//
//  mrb_cv_set(mrb, klass, mrb_intern_lit(mrb, "@essid"), mrb_str_new_cstr(mrb, myEssid));
//  essid = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@essid"));
//  sEssid = mrb_str_to_cstr(mrb, essid);
//
//  //sprintf(wifi_conf.ESSID,"%s",myEssid);
//
//  mrb_cv_set(mrb, klass, mrb_intern_lit(mrb, "@password"), mrb_str_new_cstr(mrb, myPass));
//  password = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@password"));
//  sPassword = mrb_str_to_cstr(mrb, password);
//
//  int pointer = 0;
//
//
////  while(!KeyBoard_Get_Numbers(pass)){
////
////	  sprintf(BUF,"Senha:%s",(const char *)pass);
////	  GEDI_LCD_DrawString(0,Line*1,12,16,BUF);
////
////  }
//
//
///*
//  bssid = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@bssid"));
//  sBssid = mrb_str_to_cstr(mrb, bssid);
//  TODO Implement
//
//  channel = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@channel"));
//  sChannel = mrb_str_to_cstr(mrb, channel);
//  TODO Implement
//
//  mode = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@mode"));
//  sMode = mrb_str_to_cstr(mrb, mode);
//  TODO Implement
//
//  authentication = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@authentication"));
//  sAuthentication = mrb_str_to_cstr(mrb, authentication);
//  TODO Implement
//
//  password = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@password"));
//  sPassword = mrb_str_to_cstr(mrb, password);
//  TODO Implement
//
//  cipher = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@cipher"));
//  sCipher = mrb_str_to_cstr(mrb, cipher);
//  TODO Implement*/
//
//  pass[sizeof(pass)]="\0";
//
//  GEDI_WIFI_APConnect (wifi_conf, pass);
//
//  //GEDI_LCD_DrawString(0,80,20,20,ret);
//
//  while(wifStatus!=2 && eKey_w!=GEDI_KBD_KEY_CANCEL)
//  {
//	  GEDI_KBD_Get(&eKey_w, FALSE, FALSE);
//	  GEDI_CLOCK_Delay(100);
//	  GEDI_WIFI_Status (&wifStatus);
//	  sprintf(BUF,"Status:%03d",wifStatus);
//	  GEDI_LCD_DrawString(0,Line*2,12,16,BUF);
//	  GEDI_CLOCK_Delay(500);
//  }
//
//  GEDI_LCD_DrawString(0,Line*3,12,16,"CONECTADO...");
//  GEDI_CLOCK_Delay(3000);
//  CHAR szValue[256];
//  GEDI_WIFI_ConfigGet (3, &szValue, sizeof(szValue));
//  sprintf(BUF,"Endereço IP:%s",szValue);
//  GEDI_LCD_DrawString(0,Line*4,12,16,BUF);
//  GEDI_CLOCK_Delay(3000);

  return mrb_fixnum_value(0);
}

/*0   -> Sucess */
/*1   -> In Progress*/
/*< 0 -> Fail*/
static mrb_value
mrb_wifi_connected_m(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret = 0;
  GEDI_WIFI_e_Status eStatus;

  GEDI_WIFI_Status(&eStatus);

  if(eStatus & GEDI_WIFI_STATUS_AP_CONNECTING) ret = 1;
  else if(eStatus & GEDI_WIFI_STATUS_AP_CONNECTED) ret = 0;
  else ret = -1;

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_wifi_disconnect(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret = 0;
  GEDI_WIFI_e_Status eStatus;

  GEDI_WIFI_APDisconnect();

  do
  {
	  GEDI_CLOCK_Delay(500);
	  GEDI_WIFI_Status(&eStatus);
  } while (!(eStatus & GEDI_WIFI_STATUS_AP_CONNECTED));

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_wifi__scan(mrb_state *mrb, mrb_value klass)
{
  mrb_int i = 0;
  UINT uiListSize = 0;
  GEDI_WIFI_st_Info *aps;
  GEDI_WIFI_e_Status peStatusMask;
  // mrb_value context;
  // char debug[1024];
  //
  // memset(debug, 0, sizeof(debug));
  // context = mrb_const_get(mrb, mrb_obj_value(mrb->object_class), mrb_intern_lit(mrb, "ContextLog"));
  // mrb_funcall(mrb, context, "info", 1, mrb_str_new_cstr(mrb, "inside mrb_wifi__scan"));

  GEDI_WIFI_Enable();
  GEDI_WIFI_Scan();

  do {
    GEDI_WIFI_Status(&peStatusMask);
  } while (peStatusMask == GEDI_WIFI_STATUS_SCANNING);

  GEDI_WIFI_APListGet(&aps, &uiListSize);

  if (uiListSize < 0) return mrb_false_value();

  for (i = 0; i < uiListSize; i++) {
    mrb_funcall(mrb, klass, "ap", 9,
      mrb_str_new_cstr(mrb, (char *)aps[i].Address),
      mrb_str_new_cstr(mrb, (char *)aps[i].ESSID),
      mrb_str_new_cstr(mrb, (char *)aps[i].Mode),
      mrb_str_new_cstr(mrb, (char *)aps[i].Freq),
      mrb_str_new_cstr(mrb, (char *)aps[i].Quality),
      mrb_str_new_cstr(mrb, (char *)aps[i].Type_1),
      mrb_str_new_cstr(mrb, (char *)aps[i].GroupCipher_1),
      mrb_str_new_cstr(mrb, (char *)aps[i].PairwiseCiphers_1),
      mrb_str_new_cstr(mrb, (char *)aps[i].Authentication_1)
    );
  }
  return mrb_true_value();
}

void
mrb_wifi_init(mrb_state *mrb)
{
  struct RClass *platform, *network, *wifi;

  platform = mrb_class_get(mrb, "Platform");
  network  = mrb_class_get_under(mrb, platform, "Network");
  wifi     = mrb_define_class_under(mrb, network, "Wifi", mrb->object_class);

  mrb_define_class_method(mrb, wifi, "start", mrb_wifi_start, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, wifi, "power", mrb_wifi_power, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, wifi, "connect", mrb_wifi_connect, MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, wifi, "connected?", mrb_wifi_connected_m, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, wifi, "disconnect", mrb_wifi_disconnect, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, wifi, "_scan", mrb_wifi__scan, MRB_ARGS_NONE());
}

