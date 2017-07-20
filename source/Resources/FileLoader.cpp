//
//  FileLoader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "FileLoader.hpp"

#include <sys/stat.h>

#include "FileData.hpp"

namespace Resources
{
	FileLoader::FileLoader()
	{
	}
	
	FileLoader::~FileLoader()
	{
	}
	
	bool FileLoader::is_readable(const std::string & path) const
	{
		struct stat file_info = {0};

		if (stat(path.c_str(), &file_info) != 0) {
			// If there was an error other than not found...
			if (errno != ENOENT) {
				throw std::system_error(errno, std::generic_category(), "stat");
			}

			return false;
		}

		if (S_ISDIR(file_info.st_mode)) {
			// It's a directory...
			return false;
		}
		
		return true;
	}
	
	Own<Data> FileLoader::load(const URI::Generic & uri) const
	{
		if (uri.scheme == "file") {
			auto path = uri.path.value;
			
			if (is_readable(path)) {
				return owner<FileData>(path);
			}
		}
		
		return nullptr;
	}
}
