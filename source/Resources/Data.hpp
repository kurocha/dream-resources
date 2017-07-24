//
//  Data.hpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <Memory/Object.hpp>
#include <Buffers/Buffer.hpp>

namespace Resources
{
	using namespace Memory;
	
	class Data : public Object, public Buffers::Buffer
	{
	public:
		using Byte = unsigned char;
		
		Data();
		virtual ~Data();
	};
}
