require "bundler/gem_tasks"
require "rake/testtask"
require "rake/extensiontask"

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList['test/**/*_test.rb']
end

spec = Gem::Specification.load('mmapped_string.gemspec')

Rake::ExtensionTask.new("mmapped_string", spec){|ext|
  ext.lib_dir = "lib/mmapped_string"
}

task :default => :test

task :run => 'compile' do
  ruby %q{-I ./lib test.rb}
end
