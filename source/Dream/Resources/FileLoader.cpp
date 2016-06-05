//
//  FileLoader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "FileLoader.hpp"

namespace Dream
{
	namespace Resources
	{
		FileLoader::FileLoader(Ptr<IFileSystem> file_system) : _file_system(file_sytem)
		{
		}
		
		FileLoader::~FileLoader()
		{
		}
		
		bool FileLoader::is_readable(const Path & path)
		{
			SystemError::reset();

			auto native_path = path.to_local_path();

			struct stat file_info;
			memset(&file_info, 0, sizeof(file_info));

			if (stat(native_path.c_str(), &file_info) != 0) {
				// If there was an error other than not found...
				if (errno != ENOENT) {
					SystemError::check(native_path);
				}

				return false;
			}

			if (S_ISDIR(file_info.st_mode)) {
				// It's a directory...
				return false;
			}
			
			return true;
		}
		
		Ref<Object> FileLoader::load(const Path & path, const ILoader & top) const
		{
			if (is_readable(path))
				return new Core::LocalFileData(path);
			else
				return nullptr;
		}
		
		RelativeFileLoader::RelativeFileLoader(const Path & root) : _root(root)
		{
		}
		
		RelativeFileLoader::~RelativeFileLoader()
		{
		}
		
		bool RelativeFileLoader::is_readable(const Path & path)
		{
			return FileLoader::is_readable(_root + path);
		}
		
		Ref<Object> RelativeFileLoader::load(const Path & path, const ILoader & top) const
		{
			return FileLoader::load(_root + path, top);
		}
	}
}
