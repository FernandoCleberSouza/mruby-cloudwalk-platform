#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/hash.h"

#include "gedi.h"



static mrb_value
mrb_system_s__serial(mrb_state *mrb, mrb_value self)
{
  char serial[20];

  memset(serial, 0, sizeof(serial));
  GEDI_INFO_ControlNumberGet(GEDI_INFO_CONTROL_NUMBER_SN, serial);

  return mrb_str_new_cstr(mrb, serial);
}

static mrb_value
mrb_system_s__set_backlight(mrb_state *mrb, mrb_value self)
{
  mrb_int mode;

  mrb_get_args(mrb, "i", &mode);

  /*TODO Implement*/

  return mrb_fixnum_value(mode);
}

static mrb_value
mrb_system_s__battery(mrb_state *mrb, mrb_value self)
{
  UINT puiPercentage;

  GEDI_POWER_BatteryGetCapacity (&puiPercentage);

  return mrb_str_new_cstr(mrb, battery);
}

static mrb_value
mrb_audio_s__beep(mrb_state *mrb, mrb_value self)
{
  mrb_int tone, milliseconds;

  mrb_get_args(mrb, "ii", &tone, &milliseconds);

  GEDI_AUDIO_PlayNote (0, tone, milliseconds);

  return mrb_nil_value();
}

static mrb_value
mrb_system_s_reboot(mrb_state *mrb, mrb_value self)
{
  mrb_int ret=0;

  ret = GEDI_POWER_Reset ();

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_system_s_hwclock(mrb_state *mrb, mrb_value self)
{
  /*ST_TIME t;*/
  mrb_int year, month, day, hour, minute, second;
  GEDI_CLOCK_st_RTC stRTC;

  mrb_get_args(mrb, "iiiiii", &year, &month, &day, &hour, &minute, &second);

  stRTC.bYear   = year;
  stRTC.bMonth  = month;
  stRTC.bDay    = day;
  stRTC.bHour   = hour;
  stRTC.bMinute = minute;
  stRTC.bSecond = second;
  
  GEDI_EnterEng("E");
  GEDI_CLOCK_RTCSet(&stRTC);
  mrb_fixnum_value(0);
}

void
mrb_system_init(mrb_state* mrb)
{
  struct RClass *platform;
  struct RClass *audio;
  struct RClass *system;

  platform = mrb_define_class(mrb, "Platform", mrb->object_class);
  audio    = mrb_define_class_under(mrb, platform, "Audio", mrb->object_class);
  system   = mrb_define_class_under(mrb, platform, "System", mrb->object_class);

  mrb_define_class_method(mrb , system , "serial"     , mrb_system_s__serial        , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , system , "backlight=" , mrb_system_s__set_backlight , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , system , "battery"    , mrb_system_s__battery       , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , audio  , "beep"       , mrb_audio_s__beep           , MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb , system , "reboot"     , mrb_system_s_reboot         , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , system , "hwclock"    , mrb_system_s_hwclock        , MRB_ARGS_REQ(6));
}

