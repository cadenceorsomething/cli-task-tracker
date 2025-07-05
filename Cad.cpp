#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "json.hpp"
#include "Cad.h"

// global names of the task categories
const std::string
_tasks			= "tasks",
_name			= "name",
_id				= "id",
_done			= "done",
_time_created	= "time created",
_time_updated	= "time updated";


namespace cad {
	using json = nlohmann::json;

	// time functions
	std::string get_date	(const std::chrono::system_clock::time_point& now) {
		using namespace std::chrono;	// to avoid verbosity

		// takes in current time and rounds it to the nearest whole day, removing the time of day portion.
		auto today = floor<days>(now);
		year_month_day date = year_month_day{ today };

		std::ostringstream oss;
		oss << static_cast<unsigned>(date.month()) << "/"
			<< static_cast<unsigned>(date.day()) << "/"
			<< static_cast<int>(date.year());

		return oss.str();
	}
	std::string get_time	(const std::chrono::system_clock::time_point& now) {
		using namespace std::chrono;
		std::time_t t = system_clock::to_time_t(now);

		std::tm local_tm;

		if (localtime_s(&local_tm, &t) != 0) return "...invalid time";

		std::ostringstream oss;
		oss << std::put_time(&local_tm, "%I:%M %p");
		return oss.str();
	}
	std::string current_time() {
		std::ostringstream oss;
		auto now = std::chrono::system_clock::now();

		oss << get_date(now) << " " << get_time(now);

		return oss.str();
	}




	// literally everything else
	void		display				(const json& tasks, const int& i, const bool show_progress = false) {
		const json& task = tasks[i];


		std::cout << task[_id] << ": " << task[_name];
		if (show_progress == true) std::cout << "    -status: " << task[_done];
		std::cout << std::endl;



		if (task.contains(_time_created)) {
			std::cout << "    -time created: " << task[_time_created];
		}
		else if (task.contains(_time_updated)) {
			std::cout << "    -time updated: " << task[_time_updated];
		}
		std::cout << std::endl;

		bool both_exist = task.contains(_time_updated) && task.contains(_time_created);

		if (both_exist && (task[_time_updated] != task[_time_created])) {
			std::cout << "    -time updated: " << task["time updated"];
		}

		std::cout << std::endl;
	}
	json		load_data			(const std::string filename) {
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
	void		save_data			(const json& data, const std::string filename) {
		std::ofstream out_file(filename);
		out_file << data.dump(4);
	}
	int			generate_id			(const json& data) {
		const json& tasks = data[tasks];
		int id = 1;

		while (true) {
			bool found = false;

			for (const auto& task : tasks) {
				if (task.contains(_id) && task[_id] == id) {
					found = true;
					break;
				}
			}

			if (!found)
				return id;

			++id;
		}
	}
	void		add_task			(json& data, std::string task) {
		std::string now = current_time(); //so they can both match & less computation

		data[_tasks].push_back({ 
			{_id, generate_id(data)}, 
			{_name, task}, 
			{_done, "to do"},
			{_time_created, now},
			{_time_updated, now}});
	}
	void		list_tasks			(const json& data) {
		const auto& tasks = data[_tasks];
		for (size_t i = 0; i < tasks.size(); ++i) {
			display(tasks, i, true);
		}
	}
	bool		delete_task			(json& data, int id_to_delete) {
		auto& tasks = data[_tasks];

		for (auto it = tasks.begin(); it != tasks.end(); ++it) {
			if (it->contains(_id) && (*it)[_id] == id_to_delete) {
				tasks.erase(it);
				return true;
			}
		}
		return false;
	}
	bool		mark_done			(json& data, int id) {
		auto& tasks = data["tasks"];
		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["done"] = "done";
				task["time updated"] = current_time();
				return true;
			}

		}
		return false;
	}
	bool		mark_in_progress	(json& data, int id) {
		auto& tasks = data["tasks"];
		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["done"] = "in progress";
				task["time updated"] = current_time();
				return true;
			}

		}
		return false;
	}
	bool		mark_to_do			(json& data, int id) {
		auto& tasks = data["tasks"];
		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["done"] = "to do";
				return true;
				task["time updated"] = current_time();
			}

		}
		return false;
	}
	bool		update_task			(json& data, std::string new_name, int id) {
		auto& tasks = data["tasks"];

		for (auto& task : tasks) {
			if (task.contains("id") && task["id"] == id) {
				task["name"] = new_name;
				task["time updated"] = current_time();

				return true;
			}
		}


		return false;
	}
	inline bool	contains_id			(json::iterator it) {
		return it->contains("id");
	}
	void		sort_tasks			(json& data) {
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
	void		list_done			(const json& data) {
		const auto& tasks = data["tasks"];
		for (size_t i = 0; i < tasks.size(); ++i) {
			if (tasks[i]["done"] == "done") {
				display(tasks, i);
			}
		}
	}
	void		list_in_progress	(const json& data) {
		const auto& tasks = data["tasks"];
		for (size_t i = 0; i < tasks.size(); ++i) {
			if (tasks[i]["done"] == "in progress") {
				display(tasks, i);
			}
		}
	}
	void		list_to_do			(const json& data) {
		const auto& tasks = data["tasks"];
		for (size_t i = 0; i < tasks.size(); ++i) {
			if (tasks[i]["done"] == "to do") {
				display(tasks, i);
			}
		}
	}
}