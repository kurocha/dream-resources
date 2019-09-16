//
//  Loader.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/RelativeLoader.hpp>
#include <Resources/FileLoader.hpp>
#include <Resources/StringData.hpp>

#include <URI/File.hpp>

namespace Resources
{
	UnitTest::Suite LoaderTestSuite {
		"Resources::FileLoader",
		
		{"it should load a file",
			[](UnitTest::Examiner & examiner) {
				URI::File fixture_path(getenv("RESOURCES_FIXTURES"), true);
				
				auto file_loader = owned<FileLoader>();
				auto loader = owned<RelativeLoader<Data>>(fixture_path, file_loader);
				
				auto data = loader->load("Resources/fixtures/test.txt");
				
				examiner.check(data);
				
				if (data)
					examiner.expect(data->size()) == 12;
			}
		},
		
		{"it should not load non-file resources",
			[](UnitTest::Examiner & examiner) {
				auto loader = owned<FileLoader>();
				
				auto data = loader->load("apple.jpg");
				
				examiner.expect(data) == nullptr;
			}
		}
	};
}
