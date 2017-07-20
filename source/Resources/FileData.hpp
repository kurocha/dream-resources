//
//  FileData.hpp
//  File file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Data.hpp"

#include <Buffers/File.hpp>
#include <Buffers/MappedBuffer.hpp>

namespace Resources
{
	class FileData : public Data
	{
	public:
		FileData(const std::string & path);
		virtual ~FileData();
		
		virtual const Byte * begin() const {return _buffer.begin();}
		virtual const Byte * end() const {return _buffer.end();}
		
		virtual std::size_t size() const {return _buffer.size();}
		
	private:
		Buffers::File _file;
		Buffers::MappedBuffer _buffer;
	};
}
