#include <iostream>
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include "Cad.h"

using json = nlohmann::json;


int main(int argc,char *argv[]) {
	std::string file_name = "json_file";

	json data = CAD::load_data(file_name);
	
	CAD::sort_tasks(data);

	CAD::save_data(data, file_name);

	CAD::list_tasks(data);

	return 0;
}