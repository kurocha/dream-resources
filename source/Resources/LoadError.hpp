//
//  LoadError.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include <URI/Generic.hpp>
#include <stdexcept>

namespace Resources
{
	// This exception represents that a requested resource failed to load for some reason. 
	// - The resource was available on disk but couldn't be read.
	// - The resource could be read but was corrupt.
	// - A required sub-resource couldn't be loaded.
	// If a resource simply isn't available, within Loader, this would result nullptr.
	// Loader will usually only return nullptr, but in your application code, if this represents a critical failure, you can use this exception to propagate the failure.
	class LoadError : public std::runtime_error
	{
	public:
		LoadError(const URI::Generic & uri, std::string message);
		virtual ~LoadError();
		
		const URI::Generic & uri() const { return _uri; }
		
		virtual const char* what() const noexcept;
		
	private:
		URI::Generic _uri;
		std::string _what;
	};
}
