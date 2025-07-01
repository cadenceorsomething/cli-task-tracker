#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"



namespace cad {

	using json = nlohmann::json;
	
	json		load_data		(const std::string);
	void		save_data		(const json&, const std::string);
	std::string input_task_name	();
	int			generate_id		(const json&);
	void		add_task		(json&, std::string);
	void		list_tasks		(const json&);
	bool		delete_task		(json&, int);
	bool		cross_out		(json&, int);
	bool		remove_cross	(json&, int);
	bool		update_task		(json&, std::string, int);
	void		sort_tasks		(json&);

}