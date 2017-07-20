//
//  FileLoader.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 6/6/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Loader.hpp"
#include "FileData.hpp"

namespace Resources
{
	class FileLoader : public Loader<Data>
	{
	public:
		FileLoader();
		virtual ~FileLoader();
		
		virtual Own<Data> load(const URI::Generic & uri) const;
		
	protected:
		bool is_readable(const std::string & path) const;
	};
}
