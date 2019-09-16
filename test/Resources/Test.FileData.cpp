//
//  Test.FileData.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/FileData.hpp>

#include <URI/File.hpp>

namespace Resources
{
	UnitTest::Suite FileDataTestSuite {
		"Resources::FileData",
		
		{"it should load data from disk",
			[](UnitTest::Examiner & examiner) {
				URI::File fixture_path(getenv("RESOURCES_TESTS_FIXTURES"), true);
				URI::Generic test_path = fixture_path + "Resources/fixtures/test.txt";
				
				FileData file_data(test_path.path.value);
				
				examiner.expect(file_data.size()) == 12;
			}
		},
	};
}
