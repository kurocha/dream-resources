//
//  CachingLoader.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Loader.hpp"

namespace Dream
{
	namespace Resources
	{
		class CachingLoader : public Loader
		{
		public:
			using ChainLoader::ChainLoader;
			virtual ~CachingLoader ();
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
			
		private:
			mutable std::map<const Path, Ref<Object>> _cache;
		};
	}
}
