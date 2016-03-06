//
//  Loader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Dream/Core/Data.hpp>
#include <Dream/Resources/Loader.hpp>

namespace Dream
{
	namespace Resources
	{
		class FakeFileSystem : public FileSystem
		{
		public:
			FakeFileSystem() {}
			virtual ~FakeFileSystem() {}
			
			virtual PathType path_type(const Path & path) const
			{
				if (path == Path("apple.jpg"))
					return PathType::STORAGE;
				else
					return PathType::DIRECTORY;
			}
			
			virtual FileSize file_size(const Path & path) const
			{
				return 1024;
			}
			
			// List all children paths in a given path, filtering by filter
			virtual void list(const Path & path, PathType filter, std::function<void (const Path & path)> callback) const
			{
				callback("apple.jpg");
			}
			
			// Must be an exact path (can be relative if the FileSystem implementation supports that)
			virtual Ref<IData> load(const Path & path) const
			{
				Shared<Core::DynamicBuffer> dynamic_buffer = new DynamicBuffer;
				
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
					Ref<FakeFileSystem> file_system = new FakeFileSystem;
					Ref<ILoader> loader = new Loader(file_system, Path());
										
					auto data = loader->load_data("apple.jpg");
					examiner << "Data can be directly loaded.";
					examiner.check(data);
					
					examiner.expect(data->size()) == 9;
				}
			},
		};
	}
}
