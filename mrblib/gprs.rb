class Platform::Network::Gprs
  GEDI_GSM_NETSTATUS_ESTABLISHED   = 2
  GEDI_GSM_NETSTATUS_ESTABLISHING  = 16
  GEDI_GSM_NETSTATUS_CONNECTING    = 32
  GEDI_GSM_NETSTATUS_SENDING       = 64
  GEDI_GSM_NETSTATUS_RECEIVING     = 128
  GEDI_GSM_NETSTATUS_DISCONNECTING = 256
  GEDI_GSM_NETSTATUS_ONHOOKING     = 512

  class << self
    attr_accessor :password, :user, :apn
    attr_reader :media
    @media = :gprs
  end

  def self.init(options = {})
    @apn      = options[:apn]
    @user     = options[:user]
    @password = options[:password]
    self.start
  end

  def self.type
    Network::NET_LINK_WL
  end

  def self.connect
    self._connect
  end

  def self.connected?
    connection = self._connected?
    ret = -1
    ret = 1 if (connection & GEDI_GSM_NETSTATUS_CONNECTING) != 0
    ret = 0 if (connection & GEDI_GSM_NETSTATUS_ESTABLISHED) != 0
    ret
  end
end
