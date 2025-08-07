#include "makeColorSet.h"
#include <string>
using string = std::string;

void makeColorSet (int& color_set_size, string* color_set, json& config)
{
	for(int i = 0; i < color_set_size; i++){
	color_set[i] = (config["glyphs"]["color_set"][i].get<string>());
	}

}
