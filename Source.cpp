#include <iostream>
#include "nlohmann/json.hpp"
#include <string>
#include <fstream>

using json = nlohmann::json;


json load_data(const std::string filename) {
	std::ifstream in_file(filename);
	json data;

	if (in_file) {
		in_file >> data;
	}
	else {
		data["tasks"] = json::array();
	}

	return data;
}

void save_data(const json& data, const std::string filename) {
	std::ofstream out_file(filename);
	out_file << data.dump(4);
}

std::string input_task_name() {
	std::string task;
	std::cout << "Enter task name: ";
	std::getline(std::cin, task);
	return task;
}

void add_task(json& data) {
	std::string task = input_task_name();
	data["tasks"].push_back({ {"name", task}, {"done", false} });
}

void list_tasks(const json& data) {
	const auto& tasks = data["tasks"];
	for (size_t i = 0; i < tasks.size(); ++i) {
		std::cout << i << ": " << tasks[i]["name"] << (tasks[i]["done"] ? " [x]" : " [ ]") << std::endl;
	}
}


int main(int argc,char *argv[]) {
	std::string file_name = "json_file";

	json data = load_data(file_name);
	

	add_task(data);


	save_data(data, file_name);

	list_tasks(data);

	return 0;
}