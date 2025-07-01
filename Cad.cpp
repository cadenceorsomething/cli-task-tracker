#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Cad.h"


namespace CAD {

	using json = nlohmann::json;

	json		load_data		(const std::string filename) {
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
	void		save_data		(const json& data, const std::string filename) {
		std::ofstream out_file(filename);
		out_file << data.dump(4);
	}
	std::string input_task_name	() {
		std::string task;
		std::cout << "Enter task name: ";
		std::getline(std::cin, task);
		return task;
	}
	int			generate_id		(const json& data) {
		const auto& tasks = data["tasks"];
		int id = 1;

		while (true) {
			bool found = false;

			for (const auto& task : tasks) {
				if (task.contains("id") && task["id"] == id) {
					found = true;
					break;
				}
			}

			if (!found)
				return id;

			++id;
		}
	}
	void		add_task		(json& data) {
		std::string task = input_task_name();
		data["tasks"].push_back({ {"id", generate_id(data)}, {"name", task}, {"done", false} });
	}
	void		list_tasks		(const json& data) {
		const auto& tasks = data["tasks"];
		for (size_t i = 0; i < tasks.size(); ++i) {
			std::cout << tasks[i]["id"] << ": " << tasks[i]["name"] << (tasks[i]["done"] ? " [x]" : " [ ]") << std::endl;
		}
	}
	bool		delete_task		(json& data, int id_to_delete) {
		auto& tasks = data["tasks"];

		for (auto it = tasks.begin(); it != tasks.end(); ++it) {
			if (it->contains("id") && (*it)["id"] == id_to_delete) {
				tasks.erase(it);
				return true;
			}
		}
		return false;
	}
	bool		cross_out		(json& data, int id) {
		auto& tasks = data["tasks"];
		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["done"] = true;
				return true;
			}

		}
		return false;
	}
	bool		remove_cross	(json& data, int id) {
		auto& tasks = data["tasks"];
		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["done"] = false;
				return true;
			}

		}
		return false;
	}
	bool		update_task		(json& data, std::string new_name, int id) {
		auto& tasks = data["tasks"];

		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["name"] = new_name;
				return true;
			}
		}


		return false;
	}
	inline bool	contains_id		(json::iterator it) {
		return it->contains("id");
	}
	void		sort_tasks		(json& data) {
		json& tasks = data["tasks"];

		if (tasks.size() <= 1) return;

		bool not_sorted = true;

		while (not_sorted) {
			not_sorted = false;

			json::iterator current_it = tasks.begin();
			json::iterator next_it = std::next(current_it);

			for (; next_it != tasks.end(); ++current_it, ++next_it) {
				if (!contains_id(current_it) || !contains_id(next_it)) return;

				if ((*current_it)["id"] > (*next_it)["id"]) {
					not_sorted = true;
					std::swap(*current_it, *next_it);
				}
			}
		}
	}
}