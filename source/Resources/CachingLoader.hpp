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
	class CachingLoader : public ChainLoader<LoadT, LoadT>
	{
	public:
		using ChainLoader<LoadT, LoadT>::ChainLoader;
		virtual ~CachingLoader() {}
		
		virtual Owned<LoadT> load(const URI::Generic & uri) const
		{
			auto iterator = _cache.find(uri);
			
			if (iterator != _cache.end()) {
				return iterator->second;
			}
			
			auto object = this->load_next(uri);
			_cache.insert({uri, object});
			
			return object;
		}
		
		auto & cache() noexcept {return _cache;}
		auto & cache() const noexcept {return _cache;}
		
		void update(const URI::Generic & uri, Owned<LoadT> object)
		{
			_cache.insert({uri, object});
		}
		
	private:
		mutable std::map<const URI::Generic, Owned<LoadT>> _cache;
	};
}
