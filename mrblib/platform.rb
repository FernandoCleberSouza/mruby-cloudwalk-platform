class Platform
  Network = ::Network if Kernel.const_defined? :Network
  IO      = ::IO

  class System
    class << self
      alias_method :restart, :reboot if self.respond_to? :reboot
    end
  end

  class IO
    DEFAULT_TIMEOUT = 30000

    class << self
      attr_accessor :timeout
    end
    self.timeout = DEFAULT_TIMEOUT

    # get_string c implementation.
    #
    # @param min [Fixnum] Minimum length of the input string.
    # @param max [Fixnum] Maximum length of the input string (127 bytes maximum).
    # @param mode [Symbol] Mode to input, check IO_INPUT_* variables.
    def self.get_string(min, max, mode = :letters)
      _gets(min, max, convert_input_type(mode), 0, 2)
    end
  end

  def self.screen_definition
    case System.model
    when "mp20"
      [20, 10]
    when "gpos400"
      [21, 20]
    else
      [20, 10]
    end
  end

  def self.icons_status_bar
    model = System.model.to_s
    [
      "./shared/background_#{model}.bmp", "./shared/wifi_#{model}.bmp",
      "./shared/gprs_#{model}.bmp", "./shared/battery_#{model}.bmp"
    ]
  end

  def self.define_device_modules
    Device.const_set(:EMV, Platform::EMV)
  end

  # Will be called at RunTime boot
  def self.setup
    Screen.setup(*screen_definition)
    begin
      self.define_device_modules
      require 'posxml_parser'
      require 'cloudwalk_handshake'
      CloudwalkHandshake.configure!
      self.setup_keyboard
      self.setup_status_bar
      Platform::Printer.start
    rescue LoadError
    rescue NameError
    end
  end

  def self.version
    "0.2.1"
  end

  def self.setup_keyboard
    Device::IO.setup_keyboard(["qzQZ _,.", "abcABC", "defDEF", "ghiGHI", "jklJKL",
                              "mnoMNO", "prsPRS", "tuvTUV", "wxyWXY", "spSP"])
  end

  def self.setup_status_bar
    Platform::System.status_bar(*icons_status_bar)
    DaFunk::Helper::StatusBar.managment = false if DaFunk::Helper::StatusBar.respond_to?(:managment=)
  end
end
