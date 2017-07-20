//
//  ChainLoader.hpp
//  This file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Loader.hpp"

namespace Resources
{
	template <typename LoadT, typename NextT>
	class ChainLoader : public Loader<LoadT>
	{
	public:
		ChainLoader(Loader<NextT> * next) : _next(next) {}
		virtual ~ChainLoader() {}
		
	protected:
		Owned<NextT> load_next(const URI::Generic & uri) const
		{
			return _next->load(uri);
		}
		
		Owned<Loader<NextT>> _next;
	};
}
