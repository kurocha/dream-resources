
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.0"

define_target "dream-resources" do |target|
	target.build do |environment|
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Dream/**/*.{h,hpp}')
		
		build static_library: "DreamResources", source_files: source_root.glob('Dream/**/*.cpp')
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.depends "Library/Dream"
	
	target.provides "Library/DreamResources" do
		append linkflags "-lDreamResources"
	end
end

define_target "dream-resources-tests" do |target|
	target.build do |environment|
		test_root = target.package.path + 'test'
		
		run tests: "DreamResources", source_files: test_root.glob('Dream/**/*.cpp')
	end
	
	target.depends "Library/UnitTest"
	target.depends "Library/DreamResources"

	target.provides "Test/DreamResources"
end

define_configuration "travis" do |configuration|
	configuration[:source] = "http://github.com/dream-framework/"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "dream"
	configuration.require "euclid"
	configuration.require "unit-test"
	
	configuration.require "language-cpp-class"
end
