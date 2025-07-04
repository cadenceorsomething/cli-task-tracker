#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"



namespace cad {

	using json = nlohmann::json;
	
	json		load_data			(const std::string);
	void		save_data			(const json&, const std::string);
	std::string input_task_name		();
	int			generate_id			(const json&);
	void		add_task			(json&, std::string);
	void		list_tasks			(const json&);
	bool		delete_task			(json&, int);
	bool		mark_done			(json&, int);
	bool		mark_in_progress	(json&, int);
	bool		mark_to_do			(json&, int);
	bool		update_task			(json&, std::string, int);
	void		sort_tasks			(json&);
	void		list_done			(const json&);
	void		list_in_progress	(const json&);
	void		list_to_do			(const json&);


}