//
//  Test.FileData.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/FileData.hpp>

namespace Resources
{
	UnitTest::Suite FileDataTestSuite {
		"Resources::FileData",
		
		{"it should load data from disk",
			[](UnitTest::Examiner & examiner) {
				FileData file_data{"Resources/fixtures/test.txt"};
				
				examiner.expect(file_data.size()) == 12;
			}
		},
	};
}
