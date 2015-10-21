#include <stdlib.h>
#include <stdio.h>
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/hash.h"
#include "gedi.h"

#define FontH 20
#define FontW 20

static mrb_value
mrb_platform_print_s__open(mrb_state *mrb, mrb_value self)
{
  mrb_int ret;

  /*ret = OsPrnOpen();*/

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_platform_print_s__reset(mrb_state *mrb, mrb_value self)
{
  /*OsPrnReset();*/
  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__close(mrb_state *mrb, mrb_value self)
{
  /*OsPrnClose();*/
  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__font(mrb_state *mrb, mrb_value self)
{
  mrb_value filename;
  mrb_int ret;

  mrb_get_args(mrb, "z", &filename);

  /*ret = OsPrnSetFont(RSTRING_PTR(filename))*/

  ret = GEDI_PRNTR_FontSet((const CHAR *)filename.value.p);

  return mrb_fixnum_value(ret);
}

static mrb_value
mrb_platform_print_s__level(mrb_state *mrb, mrb_value self)
{
  mrb_int level=0;

  mrb_get_args(mrb, "i", &level);
  /*OsPrnSetGray(level);*/

  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__size(mrb_state *mrb, mrb_value self)
{
  mrb_int singlecode_width=0,singlecode_height=0,multicode_width=0,multicode_height=0;

  mrb_get_args(mrb, "iiii", &singlecode_width, &singlecode_height, &multicode_width, &multicode_height);

  /*OsPrnSelectFontSize(singlecode_width, singlecode_height, multicode_width, multicode_height);*/
  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__feed(mrb_state *mrb, mrb_value self)
{
  mrb_int size;

  mrb_get_args(mrb, "i", &size);
  /*OsPrnFeed(size);*/
  GEDI_PRNTR_Init(size*8);
  GEDI_PRNTR_Output();

  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__print(mrb_state *mrb, mrb_value self)
{
  mrb_value buf;

  mrb_get_args(mrb, "z", &buf);
  /*OsPrnPrintf(RSTRING_PTR(buf));*/

  GEDI_PRNTR_Init(160);
  GEDI_PRNTR_DrawString(0, 0, FontH, FontW, (const CHAR *)buf.value.p);
  GEDI_PRNTR_Output();
  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__print_bmp(mrb_state *mrb, mrb_value self)
{
  mrb_value path;

  mrb_get_args(mrb, "z", &path);

  /*OsPrnPutImage(RSTRING_PTR(path));*/

  GEDI_e_Ret eRet;
  GEDI_PRNTR_Init(400);
  eRet = GEDI_PRNTR_DrawPictureFromFile(0, 0, (const CHAR *)path.value.p, 200);
  printf("%d\n", eRet);
  GEDI_PRNTR_Output();
  GEDI_CLOCK_Delay(1000);


  return mrb_nil_value();
}

static mrb_value
mrb_platform_print_s__check(mrb_state *mrb, mrb_value self)
{
  mrb_int ret;

  /*ret = OsPrnCheck();*/

  GEDI_PRNTR_Status(&ret);

  GEDI_LCD_DrawString(0,20,20, 20, "Resultado:");

  switch(ret){

  case 0:
	  GEDI_LCD_DrawString(0,40,20, 20, "0- STATUS OK");

	  break;

  case 1:
	  GEDI_LCD_DrawString(0,40,20, 20, "1- OVERHEAT");

	  break;

  case 2:
	  GEDI_LCD_DrawString(0,40,20, 20, "2- OUT OF PAPER");

	  break;
  default:
	  break;
  }

  return mrb_fixnum_value(ret);
}

void
mrb_init_print(mrb_state* mrb)
{
  struct RClass *platform;
  struct RClass *krn;
  struct RClass *print;

  krn      = mrb->kernel_module;
  platform = mrb_class_get(mrb, "Platform");
  print    = mrb_define_class_under(mrb, platform, "Print", mrb->object_class);

  mrb_define_class_method(mrb , print , "_open"      , mrb_platform_print_s__open      , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , print , "_reset"     , mrb_platform_print_s__reset     , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , print , "_close"     , mrb_platform_print_s__close     , MRB_ARGS_NONE());
  mrb_define_class_method(mrb , print , "_font="     , mrb_platform_print_s__font      , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , print , "_level="    , mrb_platform_print_s__level     , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , print , "_size"      , mrb_platform_print_s__size      , MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb , print , "_feed"      , mrb_platform_print_s__feed      , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , print , "_print"     , mrb_platform_print_s__print     , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , print , "_print_bmp" , mrb_platform_print_s__print_bmp , MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb , print , "_check"     , mrb_platform_print_s__check     , MRB_ARGS_NONE());
}

