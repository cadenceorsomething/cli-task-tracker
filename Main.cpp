#include <iostream>
#include "json.hpp"
#include "Cad.h"

using json = nlohmann::json;


int main(int argc,char *argv[]) {
	std::string file_name = "json_file";
	json data = cad::load_data(file_name);


	if (argc < 2) {
		std::cout << "...you were supposed to enter a <COMMAND>" << std::endl;
		return 1;
	}

	std::string command = argv[1];

	if (command == "add") {
		if (argc < 3) {
			std::cerr << "...missing task description" << std::endl;
			return 1;
		}
		std::string description = argv[2];
		cad::add_task(data, description);
	}
	if (command == "list") {
		cad::list_tasks(data);
	}


	cad::sort_tasks	(data);
	cad::save_data	(data, file_name);

	return 0;
}