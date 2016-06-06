//
//  FileLoader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "FileLoader.hpp"

#include <Dream/Core/System.hpp>
#include <Dream/Core/Data.hpp>

#include <sys/stat.h>

namespace Dream
{
	namespace Resources
	{
		FileLoader::FileLoader()
		{
		}
		
		FileLoader::~FileLoader()
		{
		}
		
		bool FileLoader::is_readable(const Path & path) const
		{
			SystemError::reset();

			auto native_path = path.to_local_path();

			struct stat file_info = {0};

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
		
		Ref<Object> RelativeFileLoader::load(const Path & path, const ILoader & top) const
		{
			// We don't handle absolute paths here.
			if (path.is_absolute()) return nullptr;
			
			return FileLoader::load(_root + path, top);
		}
	}
}
