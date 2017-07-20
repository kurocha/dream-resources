//
//  FileData.cpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "FileData.hpp"

namespace Resources
{
	FileData::FileData(const std::string & path) : _file(path), _buffer(_file, _file.size())
	{
	}
	
	FileData::~FileData()
	{
	}
}
