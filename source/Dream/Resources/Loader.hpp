//
//  Resources/Loader.h
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 29/09/06.
//  Copyright (c) 2006 Samuel Williams. All rights reserved.
//
//

#pragma once

#include <Dream/Core/Path.hpp>

#include <vector>

namespace Dream 
{
	/**
	 Provides infrastructure for loading resources.

	 Loading resources is a fairly complex task. A number of traits are useful to have:

	    - Quick loading of data from disk (using mmap for example).
	    - The ability to load data without knowning its exact implementation.
	    - The ability to search multiple locations for resources.
	 */
	namespace Resources
	{
		using namespace Dream::Core;
		
		class ILoader : public virtual IObject {
		public:
			virtual ~ILoader ();
			
			Ref<Object> load (const Path & path)
			{
				return load(path, *this);
			}
			
			virtual Ref<Object> load (const Path & path, const ILoader & top) const = 0;
		};
		
		typedef std::vector<Ref<ILoader>> Loaders;
		
		class ChainLoader : public Object, public virtual ILoader
		{
		public:
			ChainLoader(Ptr<ILoader> next_loader);
			virtual ~ChainLoader();
			
			using ILoader::load;
			
		protected:
			Ref<Object> load_next(const Path & path, const ILoader & top) const;
			
			Ref<ILoader> _next_loader;
		};
		
		class CompositeLoader : public Object, public virtual ILoader
		{
		public:
			CompositeLoader(const Loaders & loaders);
			virtual ~CompositeLoader();
			
			using ILoader::load;
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
			
		private:
			std::vector<Ref<ILoader>> _loaders;
		};
	}
}
