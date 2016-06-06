//
//  Loader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Dream/Core/Data.hpp>
#include <Dream/Resources/FileLoader.hpp>

#include <Dream/Core/Logger.hpp>

namespace Dream
{
	namespace Resources
	{
		using namespace Dream::Core::Logging;
		
		class FakeFileLoader : public FileLoader
		{
		public:
			FakeFileLoader() {}
			virtual ~FakeFileLoader() {}
			
			using FileLoader::load;
			
			// Must be an exact path (can be relative if the FileSystem implementation supports that)
			virtual Ref<Object> load(const Path & path, const ILoader & loader) const
			{
				Shared<Core::DynamicBuffer> dynamic_buffer(new DynamicBuffer);
				
				auto string = path.to_local_path();
				dynamic_buffer->resize(string.size());
				dynamic_buffer->assign(string.data());
				
				return new Core::BufferedData(dynamic_buffer);
			}
		};
		
		UnitTest::Suite LoaderTestSuite {
			"Dream::Resources::Loader",
			
			{"it should load a file",
				[](UnitTest::Examiner & examiner) {
					auto loader = ref(new FakeFileLoader);
					
					auto data = loader->load("apple.jpg").as<IData>();
					
					examiner << "Data can be directly loaded.";
					examiner.check(data);
					
					examiner.expect(data->size()) == 9;
				}
			},
		};
	}
}
