//
//  Resources/Loader.cpp
//  This file is part of the "Dream" project, and is released under the MIT license.
//
//  Created by Samuel Williams on 4/05/07.
//  Copyright (c) 2007 Samuel Williams. All rights reserved.
//
//

#include "Loader.hpp"

#include <iostream>
#include <map>

namespace Dream {
	namespace Resources {
		void Loader::set_loader_for_extension (Ptr<ILoadable> loadable, StringT ext) {
			_loaders[ext] = loadable;
		}

		Ptr<ILoadable> Loader::loader_for_extension (StringT ext) const {
			LoadersT::const_iterator loader = _loaders.find(ext);

			if (loader != _loaders.end()) {
				return loader->second;
			} else {
				return NULL;
			}
		}

		void Loader::add_loader(Ptr<ILoadable> loader) {
			loader->register_loader_types(this);
		}

		Loader::Loader (Ref<FileSystem> file_system, const Path & root) {
			_file_system = file_system;
			_current_path = root;
			
			// Check that the path is actually a directory that exists.
			DREAM_ASSERT(_file_system->path_type(root) == PathType::DIRECTORY);
		}

		Loader::~Loader ()
		{
			// log("Loader being deallocated:", this);

			double total_size = 0.0;
			for (auto cache : _data_cache) {
				total_size += cache.second->size();
			}

			log_debug("Freed", format_data_size(total_size), "of resource data.");
		}

		Ref<IData> Loader::load_data (const Path & path) const
		{
			CacheT::iterator c = _data_cache.find(path);

			if (c != _data_cache.end())
				return c->second;

			Ref<IData> data = _file_system->load(path);
			
			if (data) {
				log("Adding", path, "to cache.");
				_data_cache[path] = data;
			}
			
			return data;
		}

		void Loader::preload_resource (const Path & path)
		{
			log("Preloading", path, "...");

			load_data(path_for_resource(path));
		}

		void Loader::preload_resources (std::vector<Path> & paths)
		{
			for (auto path : paths)
			{
				preload_resource(path);
			}
		}

		Path Loader::path_for_resource (Path path) const {
			if (path.is_absolute()) return path;
			
			auto name_components = path.last_name_components();

			return path_for_resource(name_components.basename, name_components.extension, path.parent_path());
		}

		void Loader::resources_for_type(StringT extension, Path subdirectory, std::vector<Path> & paths) const {
			Path full_path = _current_path + subdirectory;

			if (_file_system->exists(full_path)) {
				_file_system->list(full_path, PathType::STORAGE, [&](const Path & path) {
					if (path.last_name_components().extension == extension)
						paths.push_back(path);
				});
			}
		}

		Path Loader::path_for_resource(StringT name, StringT extension, Path directory) const {
			Path full_path = _current_path + directory;

			//std::cerr << "Looking for: " << name << " ext: " << ext << " in: " << full_path << std::endl;

			if (!_file_system->exists(full_path))
				return Path();

			if (extension.empty()) {
				// Find all named resources
				FileSystem::Listing resource_paths;
				
				_file_system->list(full_path, PathType::STORAGE, [&](const Path & path){
					//std::cerr << "Looking at: " << entries[i] << std::endl;

					if (path.last_name_components().basename == name) {
						//std::cerr << "\t_found: " << entries[i] << std::endl;
						resource_paths.push_back(path);
					}
				});

				if (resource_paths.size() > 1) {
					log_warning("Multiple paths found for resource:", name, "in", full_path);

					for (auto path : resource_paths) {
						log_warning("\t", path);
					}
				}

				if (resource_paths.size() >= 1) {
					full_path = full_path + resource_paths[0];
				} else {
					full_path = Path();
				}
			} else {
				full_path = full_path + (name + "." + extension);
			}

			//std::cerr << "Full Path = " << full_path << std::endl;

			// Does a file exist, and is data?
			if (_file_system->path_type(full_path) == PathType::STORAGE)
				return full_path;

			return Path();
		}

		Ref<Object> Loader::load_path (const Path & path) const {
			if (!_file_system->exists(path)) {
				log_warning("File does not exist at path:", path);

				return Ref<Object>();
			}

			StringT extension = path.last_name_components().extension;
			Ptr<ILoadable> loader = loader_for_extension(extension);

			if (!loader) {
				// No loader for this type

				log_warning("No loader found for type:", extension, " while loading path:", path);

				return Ref<Object>();
			}

			Ref<IData> data = load_data(path);
			Ref<Object> resource = NULL;

			try {
				resource = loader->load_from_data(data, this);
			} catch (LoadError & e) {
				log_error("Exception thrown while loading resource ", path, ": ", e.what());

				throw;
			}

			if (!resource) {
				log_warning("Resource", path, "failed to load!");
			}

			return resource;
		}
	}
}
