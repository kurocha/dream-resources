//
//  CachingLoader.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "CachingLoader.hpp"

namespace Dream
{
	namespace Resources
	{
		CachingLoader::CachingLoader(Ptr<ILoader> next_loader) : ChainLoader(next_loader)
		{
		}
		
		CachingLoader::~CachingLoader()
		{
		}
		
		Ref<Object> CachingLoader::load(const Path & path, const ILoader & top) const
		{
			auto iterator = _cache.find(path);
			
			if (iterator != _cache.end()) {
				return *iterator;
			}
			
			// We force top = *this, as we want to ensure consistent behaviour.
			auto object = load_next(path, *this);
			
			_cache.insert({path, object});
			
			return object;
		}
	}
}
