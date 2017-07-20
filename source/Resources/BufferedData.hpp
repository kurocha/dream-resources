//
//  BufferedData.hpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 21/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Data.hpp"
#include <Buffers/Buffer.hpp>
#include <Memory/Shared.hpp>

namespace Resources
{
	class BufferedData : public Data
	{
	public:
		BufferedData(Memory::Shared<Buffers::Buffer> buffer) : _buffer(buffer) {}
		virtual ~BufferedData();
		
		virtual const Byte * begin() const {return _buffer->begin();}
		virtual const Byte * end() const {return _buffer->end();}
		
		virtual std::size_t size() const {return _buffer->size();}
		
	private:
		Memory::Shared<Buffers::Buffer> _buffer;
	};
}
