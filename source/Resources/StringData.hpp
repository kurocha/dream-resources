//
//  StringData.hpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Data.hpp"
#include <string>

namespace Resources
{
	class StringData : public Data
	{
	public:
		StringData(const std::string & buffer) : _buffer(buffer) {}
		virtual ~StringData();
		
		virtual const Byte * begin() const {return reinterpret_cast<const Byte *>(_buffer.data());}
		virtual const Byte * end() const {return reinterpret_cast<const Byte *>(_buffer.data() + _buffer.size());}
		
		virtual std::size_t size() const {return _buffer.size();}
		
	private:
		std::string _buffer;
	};
}
