//
//  FileSystem.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Dream/Core/Path.hpp>
#include <Dream/Core/Data.hpp>

#include <functional>

namespace Dream
{
	namespace Resources
	{
		using Core::Path;
		using Core::IData;
		
		typedef uint64_t FileSize;
		
		enum class PathType
		{
			// File does not exist:
			UNKNOWN = 0,

			// Include directories:
			DIRECTORY = 1 << 0,

			// Regular readable files:
			STORAGE = 1 << 2,

			// Include entries that start with dots:
			HIDDEN = 1 << 8,

			ANY = 0xFFFFFFFF
		};
		
		class FileSystem : public Object
		{
		public:
			FileSystem();
			virtual ~FileSystem();
			
			virtual PathType path_type(const Path & path) const = 0;
			virtual FileSize file_size(const Path & path) const = 0;
			
			// List all children paths in a given path, filtering by filter
			virtual void list(const Path & path, PathType filter, std::function<void (const Path & path)> callback) const = 0;
			
			// Must be an exact path (can be relative if the FileSystem implementation supports that)
			virtual Ref<IData> load(const Path & path) const = 0;
		};
	}
}
