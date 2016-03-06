//
//  LocalFileSystem.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 7/11/2014.
//  Copyright, 2014, by Samuel Williams. All rights reserved.
//

#pragma once

#include "FileSystem.hpp"

namespace Dream
{
	namespace Resources
	{
		class LocalFileSystem : public virtual FileSystem
		{
		public:
			LocalFileSystem();
			virtual ~LocalFileSystem();
			
			virtual PathType path_type(const Path & path) const;
			virtual FileSize file_size(const Path & path) const;
			virtual void list(const Path & path, PathType filter, std::function<void (const Path & path)> callback) const;
			virtual Ref<IData> load(const Path & path) const;
		};
	}
}
