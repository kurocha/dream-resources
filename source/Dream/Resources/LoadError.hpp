//
//  LoadError.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Dream/Core/Path.hpp>
#include <stdexcept>

namespace Dream
{
	namespace Resources
	{
		using namespace Dream::Core;
		
		// This exception represents that a requested resource failed to load for some reason. 
		// - The resource was available on disk but couldn't be read.
		// - The resource could be read but was corrupt.
		// - A required sub-resource couldn't be loaded.
		// If a resource simply isn't available, within ILoader, this would result nullptr.
		// ILoader will usually only return nullptr, but in your application code, if this represents a critical failure, you can use this exception to propagate the failure.
		class LoadError : public std::runtime_error
		{
		public:
			LoadError(const Path & path, std::string message);
			virtual ~LoadError();
			
			const Path & path() const { return _path; }
			
			virtual const char* what() const noexcept;
			
		private:
			Path _path;
			std::string _what;
		};
	}
}
