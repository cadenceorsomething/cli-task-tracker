#include "command.h"
#include "Cad.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;


namespace cmd {
	int handle_add			(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing task description" << std::endl;
			return 1;
		}
		std::string description = argv[2];
		cad::add_task(data, description);
		cad::sort_tasks(data);
		cad::save_data(data, file_name);
		return 0;
	}
	int handle_list			(const json& data, int argc, char* argv[]) {
		if (argc < 3) {
			cad::list_tasks(data);
			return 0;
		}
		
		std::string command = argv[2];

		if      (command == "done")			cad::list_done			(data);
		else if (command == "in-progress")	cad::list_in_progress	(data);
		else if (command == "to-do")		cad::list_to_do			(data);
		else {
			std::cerr << "...invalid progress mark" << std::endl;
			return 1;
		}
		return 0;
	}
	int handle_done			(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing id" << std::endl;
			return 1;
		}

		int id = std::stoi(argv[2]);
		if (!cad::mark_done(data, id)) {
			std::cerr << "...couldn't find id" << std::endl;
			return 1;
		}
		cad::save_data(data, file_name);

		return 0;
	}
	int handle_delete		(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing id" << std::endl;
			return 1;
		}

		int id = std::stoi(argv[2]);
		if (!cad::delete_task(data, id)) {
			std::cerr << "...couldn't find id" << std::endl;
			return 1;
		}
		cad::save_data(data, file_name);
		return 0;
	}
	int handle_to_do		(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing id" << std::endl;
			return 1;
		}

		int id = std::stoi(argv[2]);
		if (!cad::mark_to_do(data, id)) {
			std::cerr << "...couldn't find id" << std::endl;
			return 1;
		}
		cad::save_data(data, file_name);

		return 0;
	}
	int handle_in_progress	(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing id" << std::endl;
			return 1;
		}

		int id = std::stoi(argv[2]);
		if (!cad::mark_in_progress(data, id)) {
			std::cerr << "...couldn't find id" << std::endl;
			return 1;
		}
		cad::save_data(data, file_name);

		return 0;
	}
	int handle_update		(json& data, const std::string& file_name, int argc, char* argv[]) {
		if (argc < 3) {
			std::cerr << "...missing id" << std::endl;
			return 1;
		}
		int id = std::stoi(argv[2]);
		if (argc < 4) {
			std::cerr << "... you were supposed to enter ''UPDATED TASK''." << std::endl;
			return 1;
		}
		std::string updated_desc = argv[3];
		cad::update_task(data, updated_desc, id);
		cad::save_data(data, file_name);
	}

	int default_message	() {
		std::cout << "...enter a valid <COMMAND>" << std::endl;
		return 1;
	}
}

