#include <iostream>
#include <Magick++.h>
#include <nlohmann/json.hpp>
#include "config_reader.h"
#include "glyphs.h"
using namespace Magick;
using json = nlohmann::json;

int makeImage ()
{
	json config;
	if(readConfig(config) != 0){
	std::cout << "Aborting";
			return 1;
	}
	int test = glyphs(config);
	std::cout << test;
	return 0;
	
}

int main ()
{
	makeImage();
	return 0;

}
