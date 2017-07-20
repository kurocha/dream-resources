//
//  CachingLoader.hpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "ChainLoader.hpp"

namespace Resources
{
	template <typename LoadT>
	class CachingLoader : public ChainLoader<LoadT>
	{
	public:
		using ChainLoader<LoadT>::ChainLoader;
		virtual ~CachingLoader() {}
		
		virtual Owned<Object> load(const URI::Generic & uri) const
		{
			auto iterator = _cache.find(path);
			
			if (iterator != _cache.end()) {
				return iterator->second;
			}
			
			auto object = load_next(path);
			
			_cache.insert({path, object});
			
			return object;
		}
		
	private:
		mutable std::map<const URI::Generic, Owned<LoadT>> _cache;
	};
}
