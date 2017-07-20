//
//  Loader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Resources/FileLoader.hpp>
#include <Resources/StringData.hpp>

namespace Resources
{
	class FakeFileLoader : public FileLoader
	{
	public:
		FakeFileLoader() {}
		virtual ~FakeFileLoader() {}
		
		using FileLoader::load;
		
		// Must be an exact path (can be relative if the FileSystem implementation supports that)
		virtual Own<Data> load(const URI::Generic & uri) const
		{
			return owner<StringData>(uri.path.value);
		}
	};
	
	UnitTest::Suite LoaderTestSuite {
		"Dream::Resources::Loader",
		
		{"it should load a file",
			[](UnitTest::Examiner & examiner) {
				auto loader = owner<FakeFileLoader>();
				
				auto data = loader->load("apple.jpg");
				
				examiner << "Data can be directly loaded.";
				examiner.check(data);
				
				examiner.expect(data->size()) == 9;
			}
		},
	};
}
