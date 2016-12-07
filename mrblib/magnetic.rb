class Platform::Magnetic
  GEDI_MSR_STATUS_SUCCESS = 0
  SUCCESS = 1

  class << self
    attr_accessor :tracks
  end

  def self.open
    self.tracks = {}
  end

  def self.close
    nil
  end

  def self.read
    hash = self._read
    ret  = hash.delete(:ret)
    if ret == GEDI_MSR_STATUS_SUCCESS
      ret = SUCCESS
      self.tracks = hash
    end
    ret
  end
end

