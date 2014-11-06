//
//  LocalFileSystem.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 7/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#include "LocalFileSystem.hpp"

#include <Dream/Core/System.hpp>

#include <cstddef>

// For stat()
#include <sys/stat.h>

// For directory access
#include <dirent.h>

// For errno
#include <sys/errno.h>

// MAXPATHLEN
#include <sys/param.h>

// getcwd
#include <unistd.h>

// memset
#include <string.h>

namespace Dream
{
	namespace Resources
	{
		using Core::SystemError;
		
		LocalFileSystem::LocalFileSystem()
		{
		}
		
		LocalFileSystem::~LocalFileSystem()
		{
		}
		
		PathType LocalFileSystem::path_type(const Path & path) const
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

				//std::cerr << path << " is unknown" << std::endl;
				return PathType::UNKNOWN;
			}

			//mode_t mode = file_info.st_mode & S_IFMT;

			if (S_ISDIR(file_info.st_mode)) {
				//std::cerr << path << " is directory" << std::endl;
				return PathType::DIRECTORY;
			}

			//std::cerr << path << " is storage : " << S_ISREG(file_info.st_mode) << std::endl;

			// It isn't a directory so it must be some kind of storage.
			return PathType::STORAGE;
		}
		
		FileSize LocalFileSystem::file_size(const Path & path) const
		{
			SystemError::reset();

			auto native_path = path.to_local_path();
			
			struct stat file_info;
			memset(&file_info, 0, sizeof(file_info));

			if (stat(native_path.c_str(), &file_info) != 0) {
				SystemError::check(native_path);
			}

			return FileSize(file_info.st_blocks) * FileSize(file_info.st_blksize);
		}
		
		void LocalFileSystem::list(const Path & path, PathType filter, std::function<void (const Path & path)> callback) const
		{
			auto native_path = path.to_local_path();
			DIR * directory = opendir(native_path.c_str());

			struct dirent storage, * entry;
			int entry_type = 0;

			if (filter & PathType::DIRECTORY)
				entry_type |= DT_DIR;
			else if (filter & PathType::STORAGE)
				entry_type |= DT_REG;

			while (1) {
				int error = readdir_r(directory, &storage, &entry);

				// Did some error occur?
				if (error != 0)
					throw std::runtime_error("Could not enumerate directory");

				// Are we at the end of the directory list?
				if (entry == NULL)
					break;

				if (entry_type && !(entry_type & entry->d_type))
					continue;

				// Skip "hidden" files.
				if (!(filter & HIDDEN) && entry->d_name[0] == '.')
					continue;

				callback(entry->d_name);
			}

			closedir(directory);
		}
		
		Ref<IData> LocalFileSystem::load(const Path & path) const
		{
			return new Core::LocalFileData(path);
		}
		
		/* Old filesystem code:
		
		void Path::remove () const {
			StringT path = to_local_path();

			if (::remove(path.c_str()) != 0) {
				SystemError::check(__func__);
			}
		}

		void Path::move (const Path & new_name) const {
			StringT from = to_local_path(), to = new_name.to_local_path();
			if (::rename(from.c_str(), to.c_str()) != 0) {
				SystemError::check(__func__);
			}
		}

		Path Path::temporary_file_path () {
			char * path = ::tmpnam(NULL);

			if (path == nullptr) {
				SystemError::check(__func__);
			}

			return Path(path);
		}

		Path Path::current_working_directory () {
			char buffer[MAXPATHLEN];
			getcwd(buffer, MAXPATHLEN);

			return Path((const char *)buffer);
		}
		*/
	}
}
