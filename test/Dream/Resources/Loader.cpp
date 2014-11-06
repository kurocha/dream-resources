//
//  Loader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

namespace Dream
{
	namespace Resources
	{
		UnitTest::Suite LoaderTestSuite {
			"Dream::Resources::Loader",
			
			{"it should have some real tests",
				[](UnitTest::Examiner & examiner) {
					examiner.expect(false) == true;
				}
			},
		};
	}
}
