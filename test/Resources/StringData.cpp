//
//  StringData.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/StringData.hpp>
#include <Memory/Owned.hpp>

namespace Resources
{
	using namespace Memory;
	
	UnitTest::Suite StringDataTestSuite {
		"Resources::StringData",
		
		{"it can buffer a string",
			[](UnitTest::Examiner & examiner) {
				Owned<Data> data = owned<StringData>("Hello World!");
				
				examiner.expect(data->size()) == 12;
				examiner.expect(data->begin()) != nullptr;
				examiner.expect(data->end()) != nullptr;
				examiner.expect(data->end() - data->begin()) == 12;
			}
		},
	};
}
