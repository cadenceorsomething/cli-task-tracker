#pragma once
#include "json.hpp"

using json = nlohmann::json;

namespace cmd {
	int handle_add			(json&, const std::string&, int, char* []);
	int handle_list			(const json&);
	int handle_completed	(json&, const std::string&, int, char* []);
	int handle_delete		(json&, const std::string&, int, char* []);
	int handle_incomplete	(json&, const std::string&, int, char* []);
	int handle_update		(json&, const std::string&, int, char* []);

	
	int default_message	();
}
