//
//  Resources/Loader.cpp
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 4/05/07.
//  Copyright (c) 2007 Samuel Williams. All rights reserved.
//
//

#include "Loader.hpp"

#include <iostream>
#include <map>

namespace Dream
{
	namespace Resources
	{
		ILoader::~ILoader ()
		{
		}
		
		ChainLoader::ChainLoader(Ptr<ILoader> next_loader) : _next_loader(next_loader)
		{
		}
		
		ChainLoader::~ChainLoader()
		{
		}
		
		Ref<Object> ChainLoader::load_next(const Path & path, const ILoader & top) const
		{
			return _next_loader->load(path, top);
		}
		
		CompositeLoader::CompositeLoader(const Loaders & loaders) : _loaders(loaders)
		{
		}
		
		CompositeLoader::~CompositeLoader()
		{
		}
		
		Ref<Object> CompositeLoader::load(const Path & path, const ILoader & top) const
		{
			for (auto loader : _loaders) {
				if (auto object = loader->load(path, top))
					return object;
			}
			
			return nullptr;
		}
	}
}
