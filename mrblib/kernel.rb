module Kernel
  # TODO Implement
  SCREEN_X_SIZE  = 320
  SCREEN_Y_SIZE  = 480
  XUI_KEY1       = 107
  XUI_KEY2       = 108
  XUI_KEY3       = 109
  XUI_KEY4       = 110
  XUI_KEY5       = 111
  XUI_KEY6       = 112
  XUI_KEY7       = 113
  XUI_KEY8       = 114
  XUI_KEY9       = 115
  XUI_KEY0       = 106
  XUI_KEYCANCEL  = 118
  XUI_KEYTIMEOUT = 1
  XUI_KEYCLEAR   = 119
  XUI_KEYENTER   = 120
  XUI_KEYSHARP   = 150
  XUI_KEYF1      = 116
  XUI_KEYALPHA   = XUI_KEYF1
  XUI_KEYF2      = 101
  XUI_KEYF3      = 102
  XUI_KEYF4      = 103
  XUI_KEYFUNC    = 2
  XUI_KEYUP      = 121
  XUI_KEYDOWN    = 117
  XUI_KEYMENU    = 139
  # TODO Implement

  IO_INPUT_NUMBERS = :numbers
  IO_INPUT_LETTERS = :letters
  IO_INPUT_SECRET  = :secret

  INPUT_NUMBERS = 36 # TODO Implement
  INPUT_LETTERS = 20 # TODO Implement
  INPUT_SECRET  = 28 # TODO Implement

  PLATFORM_KEYS = {
    XUI_KEY0       => "0",
    XUI_KEY1       => "1",
    XUI_KEY2       => "2",
    XUI_KEY3       => "3",
    XUI_KEY4       => "4",
    XUI_KEY5       => "5",
    XUI_KEY6       => "6",
    XUI_KEY7       => "7",
    XUI_KEY8       => "8",
    XUI_KEY9       => "9",
    XUI_KEYF1      => 0x01.chr,
    XUI_KEYF2      => 0x02.chr,
    XUI_KEYF3      => 0x03.chr,
    XUI_KEYF4      => 0x04.chr,
    XUI_KEYFUNC    => 0x06.chr,
    XUI_KEYUP      => 0x07.chr,
    XUI_KEYDOWN    => 0x08.chr,
    XUI_KEYMENU    => 0x09.chr,
    #XUI_KEYALPHA   => 0x10.chr,
    XUI_KEYSHARP   => 0x11.chr,
    XUI_KEYTIMEOUT => 0x12.chr,
    XUI_KEYENTER   => 0x0D.chr,
    XUI_KEYCLEAR   => 0x0F.chr,
    XUI_KEYCANCEL  => 0x1B.chr
  }

  def print_line(buf, row=nil, column=nil)
    Platform::Display.print_line(buf, row, column)
  end

  def gets(separator = 0x0D.chr, limit = SCREEN_X_SIZE, mode = IO_INPUT_LETTERS)
    Device::IO.get_string(1, limit, mode).split(separator).first
  end

  def getc(timeout_io = nil)
    timeout_io ||= IO.timeout
	key = IO._getc(timeout_io)
    convert_key(key)
  end

  private
  def convert_key(value)
    PLATFORM_KEYS[value] || 0x1B.chr
  end

  def convert_input_type(type)
    case type
    when IO_INPUT_NUMBERS then INPUT_NUMBERS
    when IO_INPUT_LETTERS then INPUT_LETTERS
    when IO_INPUT_SECRET then INPUT_SECRET
    else
      INPUT_LETTERS
    end
  end
end
