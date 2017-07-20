
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
	target.build do
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Resources/**/*.hpp')
		
		build static_library: "Resources", source_files: source_root.glob('Resources/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Library/Memory"
	target.depends "Library/URI"
	target.depends "Library/Buffers"
	
	target.provides "Library/Resources" do
		append linkflags [
			->{install_prefix + 'lib/libResources.a'},
		]
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
