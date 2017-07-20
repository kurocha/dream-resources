//
//  Test.RelativeLoader.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/RelativeLoader.hpp>
#include <Resources/FileLoader.hpp>

namespace Resources
{
	UnitTest::Suite RelativeLoaderTestSuite {
		"Resources::RelativeLoader",
		
		{"it should have some real tests",
			[](UnitTest::Examiner & examiner) {
				auto file_loader = owned<FileLoader>();
				auto relative_loader = owned<RelativeLoader<Data>>("file:Resources/", file_loader);
				
				auto data = relative_loader->load("fixtures/test.txt");
				
				examiner.check(data);
				examiner.expect(data->size()) == 12u;
			}
		},
	};
}
