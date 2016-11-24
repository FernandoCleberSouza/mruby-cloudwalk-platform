
#include "mruby.h"
#include <stddef.h>
#include <string.h>

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/hash.h"
#include "mruby/string.h"
#include "mruby/variable.h"

#include <gedi.h>

#if MRUBY_RELEASE_NO < 10000
  #include "error.h"
#else
  #include "mruby/error.h"
#endif

/*Start the hardware*/
static mrb_value
mrb_gprs_start(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret=0;

  ret = GEDI_GSM_Enable(GEDI_GSM_SIM1, "", 120000);

  return mrb_fixnum_value(ret);
}

/*Turn on/off the power 1 - on 0 - off*/
static mrb_value
mrb_gprs_power(mrb_state *mrb, mrb_value klass)
{
  mrb_int on;
  mrb_get_args(mrb, "i", &on);

  /*TODO Implement*/
  /*OsWlSwitchPower(on);*/

  return mrb_true_value();
}

/*Start GPRS dial*/
/*should be unblocking if timeout 0*/
static mrb_value
mrb_gprs_connect(mrb_state *mrb, mrb_value klass)
{
  mrb_value apn, user, password;
  const char *sAPN, *sUser, *sPass;
  int keep_alive=300000, timeout=0, ret=0;

  apn   = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@apn"));
  sAPN  = mrb_str_to_cstr(mrb, apn);

  user  = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@user"));
  sUser = mrb_str_to_cstr(mrb, user);

  password = mrb_cv_get(mrb, klass, mrb_intern_lit(mrb, "@password"));
  sPass    = mrb_str_to_cstr(mrb, password);

  ret = GEDI_GSM_GPRS_Open(sAPN, sUser, sPass, 120000);
  
  return mrb_fixnum_value(ret);
}

/*Check if dial has ended*/
/*   0 -> Sucess*/
/*   1 -> In Progress*/
/* < 0 -> Fail*/
static mrb_value
mrb_gprs_connected_m(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret=0;
  GEDI_GSM_e_NetStatus eStatus;

  GEDI_GSM_GPRS_Status(&eStatus);

  return mrb_fixnum_value((mrb_int)eStatus);
}

static mrb_value
mrb_gprs_disconnect(mrb_state *mrb, mrb_value klass)
{
  mrb_int ret=0;

  GEDI_GSM_GPRS_Close();
  
  return mrb_true_value();
}

/*Must to return the signal value between 1 and 5*/
static mrb_value
mrb_gprs_signal(mrb_state *mrb, mrb_value klass)
{
  /*TODO Implement*/
  /*mrb_int signal = OsWlGetSignal();*/
  mrb_int signal = 0;
  return mrb_fixnum_value(signal);
}

void
mrb_gprs_init(mrb_state* mrb)
{
  struct RClass *platform, *network, *gprs;

  platform = mrb_class_get(mrb, "Platform");
  network  = mrb_class_get_under(mrb, platform, "Network");
  gprs     = mrb_define_class_under(mrb, network, "Gprs", mrb->object_class);

  mrb_define_class_method(mrb, gprs, "start", mrb_gprs_start, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, gprs, "power", mrb_gprs_power, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, gprs, "_connect", mrb_gprs_connect, MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, gprs, "_connected?", mrb_gprs_connected_m, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, gprs, "disconnect", mrb_gprs_disconnect, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, gprs, "signal", mrb_gprs_signal, MRB_ARGS_NONE());
}

