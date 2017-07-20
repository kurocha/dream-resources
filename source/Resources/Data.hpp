//
//  Data.hpp
//  File file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Memory/Object.hpp>

namespace Resources
{
	using namespace Memory;
	
	class Data : public Object
	{
	public:
		using Byte = unsigned char;
		
		Data();
		virtual ~Data();
		
		virtual const Byte * begin() const = 0;
		virtual const Byte * end() const = 0;
		
		virtual std::size_t size() const = 0;
	};
}
