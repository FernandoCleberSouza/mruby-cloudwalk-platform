#include <stdlib.h>
#include <stdio.h>
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/hash.h"

#include "gedi.h"

#define FontH 22
#define FontW 15


mrb_display_s_clear(mrb_state *mrb, mrb_value self)
static void
{

  GEDI_LCD_Clear();

  return mrb_nil_value();
}

static mrb_value
mrb_display_s_clear_line(mrb_state *mrb, mrb_value self)
{
  mrb_int line;

  mrb_get_args(mrb, "i", &line);

  GEDI_LCD_DrawString(0,line*FontH,FontW,FontH,"                ");

  return mrb_nil_value();
}

static mrb_value
mrb_display_s_print_bitmap(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_int x, y;

  mrb_get_args(mrb, "zii", &path, &y, &x);

  GEDI_LCD_DrawPictureFromFile(x,y,(const CHAR *)path.value.p, GEDI_FS_STORAGE_PRIVATE);

  return mrb_nil_value();
}

/*
  retrieve arguments from mrb_state.
  mrb_get_args(mrb, format, ...)
  returns number of arguments parsed.
  format specifiers:
    string  mruby type     C type                 note
    ----------------------------------------------------------------------------------------------
    o:      Object         [mrb_value]
    C:      class/module   [mrb_value]
    S:      String         [mrb_value]
    A:      Array          [mrb_value]
    H:      Hash           [mrb_value]
    s:      String         [char*,mrb_int]        Receive two arguments.
    z:      String         [char*]                NUL terminated string.
    a:      Array          [mrb_value*,mrb_int]   Receive two arguments.
    f:      Float          [mrb_float]
    i:      Integer        [mrb_int]
    b:      Boolean        [mrb_bool]
    n:      Symbol         [mrb_sym]
    d:      Data           [void*,mrb_data_type const] 2nd argument will be used to check data type so it won't be modified
    &:      Block          [mrb_value]
    *:      rest argument  [mrb_value*,mrb_int]   Receive the rest of the arguments as an array.
    |:      optional                              Next argument of '|' and later are optional.
    ?:      optional given [mrb_bool]             true if preceding argument (optional) is given.
 */

static mrb_value
mrb_display_s_print_line(mrb_state *mrb, mrb_value self)
{
  mrb_value buf;
  mrb_int x, y;

  mrb_get_args(mrb, "zii", &buf, &y, &x);

  /*TODO Implement*/
  GEDI_LCD_DrawString(x*FontW,y*FontH,FontW,FontH,(const CHAR *)buf.value.p);

  return mrb_nil_value();
}

static mrb_value
mrb_display_s_print_status_bar(mrb_state *mrb, mrb_value self)
{
  mrb_value path;
  mrb_int slot = 0;

  mrb_get_args(mrb, "io", &slot, &path);

  /*TODO Implement*/
  /*if (mrb_string_p(path)) {*/
    /*if (XuiSetStatusbarIcon(slot, RSTRING_PTR(path)) == 0)*/
      /*return mrb_true_value();*/
    /*else*/
      /*return mrb_nil_value();*/
  /*} else {*/
    /*if (XuiSetStatusbarIcon(slot, NULL) == 0)*/
      /*return mrb_true_value();*/
    /*else*/
      /*return mrb_nil_value();*/
    /*return mrb_nil_value();*/
  /*}*/
  return mrb_nil_value();
}

static mrb_value
mrb_display_s_status_bar_slots_available(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(8);
}

void
mrb_display_init(mrb_state* mrb)
{
  struct RClass *platform;
  struct RClass *display;

  platform = mrb_class_get(mrb, "Platform");
  display = mrb_define_class_under(mrb, platform, "Display", mrb->object_class);

  mrb_define_class_method(mrb , display , "clear"                      , mrb_display_s_clear                      , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , display , "clear_line"                 , mrb_display_s_clear_line                 , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , display , "print_bitmap"               , mrb_display_s_print_bitmap               , MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb , display , "print_line"                 , mrb_display_s_print_line                 , MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb , display , "print_status_bar"           , mrb_display_s_print_status_bar           , MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb , display , "status_bar_slots_available" , mrb_display_s_status_bar_slots_available , MRB_ARGS_NONE());
}
