require "mmapped_string/version"
require "mmapped_string/mmapped_string"

module MmappedString
  def self.open fname
    mmap_open(fname, File.size(fname))
  end
end
