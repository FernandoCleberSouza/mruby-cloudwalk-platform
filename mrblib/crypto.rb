class Platform::Crypto
  def self.dukpt_encrypt_buffer(slot, message)
    ret, out, ksn = self._dukpt_encrypt_buffer(slot, message)
    if ret == 0
      [ret, out.to_s.upcase, ksn.to_s.upcase]
    end
  end
end
