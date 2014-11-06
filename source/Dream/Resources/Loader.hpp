//
//  Resources/Loader.h
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 29/09/06.
//  Copyright (c) 2006 Samuel Williams. All rights reserved.
//
//

#pragma once

#include <Dream/Core/Logger.hpp>

#include "Loadable.hpp"
#include "FileSystem.hpp"

#include <map>

namespace Dream {
	/**
	 Provides infrastructure for loading resources.

	 Loading resources is a fairly complex task. A number of traits are useful to have:

	    - Quick loading of data from disk (using mmap for example).
	    - The ability to load data without knowning its exact type.
	    - The ability to search multiple locations for resources.

	 Classes that are designed to load from resources need to be registered. This is typically done by writing

	 <code>
	 Resources::register("filetype", MyResourceFactory::klass);
	 </code>

	 This means that the user can write

	 <code>
	 Ref<MyResourcesFactory> factory = loader->load <MyResourcesFactory> ("path/to/resource");
	 </code>

	 Factory classes should process the loaded data accordingly. A resource factory should provide a set of creation methods, such as <tt>create_my_resource</tt>.
	 This means that once a resource is loaded, the factory can be cached (i.e. the loaded data), and actual "resources" can be created as needed.

	 It might be necessary to load data from more than one path. If this is the case, an AggregateLoader should be used. Generally, an application should have
	 need for only one top level loader, and it should be constructed so that it has access to all resources needed.

	 A resource factory should retain an instance to its original loader if needed.
	 */
	namespace Resources {
		using namespace Dream::Core;

		StringT extension(const Path &s, bool dot);

		typedef std::map<StringT, Ref<ILoadable>> LoadersT;

		class ILoader : virtual public IObject {
		public:
			virtual Ref<Object> load_path (const Path &res) const = 0;
			// This resource loader's current base path
			virtual const Path & resource_path () const = 0;

			/// Normalize a resource request
			virtual Path path_for_resource(Path) const = 0;
			virtual Path path_for_resource(StringT name, StringT ext, Path dir) const = 0;
			virtual void resources_for_type(StringT ext, Path subdir, std::vector<Path> & paths) const = 0;

			/// Primary interface for loading resources
			template <typename InterfaceT>
			Ref<InterfaceT> load (const Path & resource_name) const
			{
				using namespace Core::Logging;

				Ref<Object> resource = load_path(path_for_resource(resource_name));

				if (!resource) {
					log_error("Resource failed to load: ", resource_name);
				}

				Ref<InterfaceT> result = resource.as<InterfaceT>();

				if (!result) {
					log_error("Invalid resource class: ", resource_name);
				}

				return result;
			}

			virtual void preload_resource(const Path & path) = 0;
			virtual void preload_resources(std::vector<Path> & paths) = 0;

			virtual void set_loader_for_extension(Ptr<ILoadable> loadable, StringT ext) = 0;
			virtual Ptr<ILoadable> loader_for_extension(StringT ext) const = 0;
			virtual void add_loader(Ptr<ILoadable> loader) = 0;

			/// Load the raw data for a given path.
			virtual Ref<IData> fetch_data_for_path (const Path & path) const = 0;

			/// Useful for loading buffers of data.
			Ref<IData> data_for_resource (const Path & resource)
			{
				return fetch_data_for_path(path_for_resource(resource));
			}
		};

		class Loader : public Object, virtual public ILoader {
		protected:
			// Mapping can be simple file extensions
			// Such as "png" or "tga" or "shader"

			LoadersT _loaders;

			Ref<FileSystem> _file_system;
			Path _current_path;

			typedef std::map<Path, Ref<IData>> CacheT;
			mutable CacheT _data_cache;

		public:
			virtual void set_loader_for_extension (Ptr<ILoadable> loadable, StringT ext);
			virtual Ptr<ILoadable> loader_for_extension (StringT ext) const;
			virtual void add_loader(Ptr<ILoadable> loader);

			Loader(Ref<FileSystem> file_system, const Path & root);
			virtual ~Loader();

			// This resource loader's current base path
			const Path & resource_path() const { return _current_path; }

			// Normalize a resource request
			virtual Path path_for_resource(Path) const;
			virtual Path path_for_resource(StringT name, StringT ext, Path dir) const;

			// Load a path directly with no processing
			virtual Ref<Object> load_path(const Path &res) const;
			virtual Ref<IData> fetch_data_for_path(const Path & path) const;

			void resources_for_type(StringT ext, Path subdir, std::vector<Path> &paths) const;

			virtual void preload_resource(const Path & path);
			virtual void preload_resources(std::vector<Path> & paths);
		};
	}
}
