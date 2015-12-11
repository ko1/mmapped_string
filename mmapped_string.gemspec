# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mmapped_string/version'

Gem::Specification.new do |spec|
  spec.name          = "mmapped_string"
  spec.version       = MmappedString::VERSION
  spec.authors       = ["Koichi Sasada"]
  spec.email         = ["ko1@atdot.net"]

  spec.summary       = %q{Return file contens using mmap(2).}
  spec.description   = %q{Return file contens using mmap(2).}
  spec.homepage      = "http://github.com/ko1/mmapped_string"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions    = %w[ext/mmapped_string/extconf.rb]

  spec.add_development_dependency "bundler", "~> 1.10"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "minitest"
end
