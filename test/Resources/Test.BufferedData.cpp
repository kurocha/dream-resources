//
//  Test.BufferedData.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 21/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/BufferedData.hpp>
#include <Buffers/StaticBuffer.hpp>

namespace Resources
{
	UnitTest::Suite BufferedDataTestSuite {
		"Resources::BufferedData",
		
		{"it can make data from shared buffer",
			[](UnitTest::Examiner & examiner) {
				auto buffer = shared<Buffers::StaticBuffer>("Hello World!", false);
				auto data = owned<BufferedData>(buffer);
				
				examiner.expect(data->size()) == 12;
			}
		},
	};
}
