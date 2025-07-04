#include <iostream>
#include "json.hpp"
#include "Cad.h"
#include "command.h"

using json = nlohmann::json;

int main(int argc,char *argv[]) {
	std::string file_name = "json_file";
	json data = cad::load_data(file_name);
	

	if (argc < 2) {
		std::cout << "...you were supposed to enter a <COMMAND>" << std::endl;
		return 1;
	}

	std::string command = argv[1];


	if (command == "add")			return cmd::handle_add(data, file_name, argc, argv);
	else if (command == "list")			return cmd::handle_list(data, argc, argv);
	else if (command == "mark-done")	return cmd::handle_done(data, file_name, argc, argv);
	else if (command == "delete")		return cmd::handle_delete(data, file_name, argc, argv);
	else if (command == "update")		return cmd::handle_update(data, file_name, argc, argv);
	else if (command == "mark-to-do")	return cmd::handle_to_do(data, file_name, argc, argv);
	else if (command == "mark-in-progress")	return cmd::handle_in_progress(data, file_name, argc, argv);
	else								return cmd::default_message	();

	return 0;
}