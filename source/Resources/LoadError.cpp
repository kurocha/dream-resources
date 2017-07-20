//
//  LoadError.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "LoadError.hpp"

#include <sstream>

namespace Resources
{
	LoadError::LoadError(const URI::Generic & uri, std::string message) : std::runtime_error(message), _uri(uri)
	{
		std::stringstream buffer;
		
		buffer << "While loading '" << uri << "', a load error occurred: " << message;
		
		_what = buffer.str();
	}
	
	LoadError::~LoadError()
	{
	}
	
	const char* LoadError::what() const noexcept
	{
		return _what.c_str();
	}
}
