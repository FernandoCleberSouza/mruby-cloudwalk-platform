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

mrb_value
mrb_magnetic_s_open(mrb_state *mrb, mrb_value self)
{
  mrb_int ret;

  /*TODO Implement*/

  return mrb_fixnum_value(ret);
}

mrb_value
mrb_magnetic_s_read(mrb_state *mrb, mrb_value self)
{
  mrb_int ret;

  BYTE abTk1[256], abTk2[256], abTk3[256];
  UINT uiLen1 = 0,uiLen2 = 0,uiLen3 = 0 ;
  GEDI_e_Ret eRet;

  uiLen1 = sizeof(abTk1);
  uiLen2 = sizeof(abTk2);
  uiLen3 = sizeof(abTk3);

  eRet = GEDI_MSR_Read(abTk1, &uiLen1, abTk2, &uiLen2, abTk3, &uiLen3);


  GEDI_LCD_DrawString(0,0,10,10,"T1:%x Len:%04d",abTk1,uiLen1);
  GEDI_LCD_DrawString(0,20,10,10,"T2:%x Len:%04d",abTk2,uiLen2);
  GEDI_LCD_DrawString(0,40,10,10,"T3:%x Len:%04d",abTk3,uiLen3);

  return mrb_fixnum_value(ret);
}

mrb_value
mrb_magnetic_s_close(mrb_state *mrb, mrb_value self)
{
  /*TODO Implement*/

  return mrb_nil_value();
}

/*{:track1 => "", :track2 => "", :track3 => ""}*/
mrb_value
mrb_magnetic_s_tracks(mrb_state *mrb, mrb_value self)
{
  mrb_value hash;

  /*TODO Implement*/

  hash = mrb_hash_new(mrb);
  mrb_hash_set(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, "track1")), mrb_str_new_cstr(mrb, "track1 information"));
  mrb_hash_set(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, "track2")), mrb_str_new_cstr(mrb, "track2 information"));
  mrb_hash_set(mrb, hash, mrb_symbol_value(mrb_intern_cstr(mrb, "track3")), mrb_str_new_cstr(mrb, "track3 information"));

  return hash;
}

void
mrb_magnetic_init(mrb_state* mrb)
{
  struct RClass *platform;
  struct RClass *magnetic;

  platform = mrb_class_get(mrb, "Platform");
  magnetic = mrb_define_class_under(mrb, platform, "Magnetic", mrb->object_class);

  mrb_define_class_method(mrb , magnetic , "open"      , mrb_magnetic_s_open      , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , magnetic , "read"      , mrb_magnetic_s_read      , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , magnetic , "close"     , mrb_magnetic_s_close     , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , magnetic , "tracks"    , mrb_magnetic_s_tracks    , MRB_ARGS_REQ(1));
}

