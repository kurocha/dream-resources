//
//  ChainLoader.hpp
//  File file is part of the "Resources" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Loader.hpp"

namespace Resources
{
	template <typename LoadT>
	class ChainLoader : public virtual Loader<LoadT>
	{
	public:
		ChainLoader(Loader<LoadT> * next) : _next(next) {}
		virtual ~ChainLoader() {}
		
	protected:
		Own<LoadT> load_next(const URI::Generic & uri) const
		{
			return _next->load(uri);
		}
		
		Own<Loader<LoadT>> _next;
	};
}