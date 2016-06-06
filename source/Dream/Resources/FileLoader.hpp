//
//  FileLoader.hpp
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
		class FileLoader : public Object, public virtual ILoader
		{
		public:
			FileLoader();
			virtual ~FileLoader();
			
			using ILoader::load;
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
			
		private:
			bool is_readable(const Path & path) const;
		};
		
		/// Load relative paths with the given root. Absolute paths will be ignored.
		class RelativeFileLoader : public FileLoader
		{
		public:
			RelativeFileLoader(const Path & root);
			virtual ~RelativeFileLoader();
			
			using FileLoader::load;
			
			bool is_readable(const Path & path) const;
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
		
		private:
			Path _root;
		};
	}
}
