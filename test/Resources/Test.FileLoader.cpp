//
//  Loader.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/FileLoader.hpp>
#include <Resources/StringData.hpp>

namespace Resources
{
	UnitTest::Suite LoaderTestSuite {
		"Resources::FileLoader",
		
		{"it should load a file",
			[](UnitTest::Examiner & examiner) {
				auto file_loader = owner<FileLoader>();
				
				auto data = file_loader->load("file:Resources/fixtures/test.txt");
				
				examiner.check(data);
				examiner.expect(data->size()) == 12;
			}
		},
		
		{"it should not load non-file resources",
			[](UnitTest::Examiner & examiner) {
				auto loader = owner<FileLoader>();
				
				auto data = loader->load("apple.jpg");
				
				examiner.expect(data) == nullptr;
			}
		}
	};
}
