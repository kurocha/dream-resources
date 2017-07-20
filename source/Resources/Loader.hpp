//
//  Resources/Loader.h
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 29/09/06.
//  Copyright (c) 2006 Samuel Williams. All rights reserved.
//
//

#pragma once

#include <URI/Generic.hpp>
#include <Memory/Object.hpp>
#include <Memory/Owner.hpp>

#include <vector>

namespace Resources
{
	using namespace Memory;
	
	template <typename LoadT>
	class Loader : public Object {
	public:
		virtual ~Loader() {}
		
		virtual Own<LoadT> load(const URI::Generic & uri) const = 0;
	};
}
