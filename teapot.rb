
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.0.0"

# Project Metadata

define_project 'resources' do |project|
	project.title = 'Resources'
	project.summary = 'Abstract resource loading given a URI.'
	
	project.license = 'MIT License'
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = '1.0.0'
end

# Build Targets

define_target 'resources-library' do |target|
	target.depends "Language/C++14"
	
	target.depends "Library/Memory", public: true
	target.depends "Library/URI", public: true
	target.depends "Library/Buffers", public: true
	
	target.provides "Library/Resources" do
		source_root = target.package.path + 'source'
		
		library_path = build static_library: "Resources", source_files: source_root.glob('Resources/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "resources-fixtures" do |target|
	target.depends :platform
	target.depends "Build/Files"
	
	target.provides "Fixtures/Resources" do
		test_root = target.package.path + 'test'
		cache_prefix = environment[:build_prefix] / environment.checksum
		
		copy source: test_root.glob("**/fixtures/*"), prefix: cache_prefix
		
		resources_fixtures cache_prefix
	end
end

define_target "resources-tests" do |target|
	target.depends "Library/UnitTest"
	target.depends "Language/C++14"
	
	target.depends "Library/Resources"
	target.depends "Fixtures/Resources"
	
	target.provides "Test/Resources" do |*arguments|
		test_root = target.package.path + 'test'
		
		run source_files: test_root.glob('Resources/**/*.cpp'), arguments: arguments
	end
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha/"
	configuration.import "resources"
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require "generate-cpp-class"
	
	configuration.require "generate-template"
	configuration.require "generate-project"
	configuration.require "generate-travis"
end

define_configuration "resources" do |configuration|
	configuration.public!
	
	configuration.require "memory"
	configuration.require "uri"
	configuration.require "buffers"
end
