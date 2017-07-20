
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.0.0"

define_target "resources" do |target|
	target.build do |environment|
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Resources/**/*.hpp')
		
		build static_library: "Resources", source_files: source_root.glob('Resources/**/*.cpp')
	end
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.depends "Library/Memory"
	target.depends "Library/URI"
	target.depends "Library/Buffers"
	
	target.provides "Library/Resources" do
		append linkflags {install_prefix + "lib/libResources.a"}
	end
end

define_target "resources-tests" do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		copy test_assets: test_root.glob('**/fixtures/*')
		
		run tests: "Resources", source_files: test_root.glob('Resources/**/*.cpp'), arguments: arguments
	end
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Resources"

	target.provides "Test/Resources"
end

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha/"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "unit-test"
	
	configuration.require "generate-template"
	configuration.require "generate-project"
	configuration.require "generate-cpp-class"
	
	configuration.import "resources"
end

define_configuration "resources" do |configuration|
	configuration.public!
	
	configuration.require "memory"
	configuration.require "uri"
	configuration.require "buffers"
end
