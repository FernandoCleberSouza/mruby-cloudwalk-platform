#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/hash.h"
#include <gedi.h>

static mrb_value
mrb_platform_io_s__getc(mrb_state *mrb, mrb_value self)
{
  mrb_int timeout=0;
  GEDI_KBD_e_Key eKey;

  mrb_get_args(mrb, "i", &timeout);

  GEDI_KBD_Get(&eKey, timeout, FALSE);

  return mrb_fixnum_value(key);
}

void
mrb_io_init(mrb_state* mrb)
{
  struct RClass *io;

  io = mrb_class_get(mrb, "IO");

  mrb_define_class_method(mrb , io , "_getc" , mrb_platform_io_s__getc , MRB_ARGS_REQ(1));
}

