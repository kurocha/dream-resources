//
//  FileLoader.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Dream
{
	namespace Resources
	{
		class FileLoader : public Object, public virtual ILoader
		{
		public:
			FileLoader();
			virtual ~FileLoader();
			
			bool is_readable(const Path & path);
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
		};
		
		class RelativeFileLoader : public FileLoader
		{
		public:
			RelativeFileLoader(const Path & root);
			virtual ~RelativeFileLoader();
			
			bool is_readable(const Path & path);
			
			virtual Ref<Object> load(const Path & path, const ILoader & top) const;
		};
	}
}
