#include <iostream>
#include <fstream>
#include "config_reader.h"

using json = nlohmann::json;

int readConfig(json& json_value)
{
	
	std::ifstream file("config.json");
	if (!file.is_open()) {
		std::cerr << "Error. Can't open config file\n";
		return 1;
	}
	try {
		file >> json_value;
	}
	catch (const json::parse_error &e) {
		std::cerr << "JSON parse error: " << e.what()
			<< "\nByte position: " << e.byte << "\n";
		return 1;
	}	
	return 0;
}
