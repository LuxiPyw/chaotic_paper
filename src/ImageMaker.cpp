#include <iostream>
#include <fstream>
#include "ImageMaker.h"
#include "GlyphPattern.h"

static std::unique_ptr<ImagePattern> ImageMaker::choicePattern(std::string userInput)
{
	switch(userInput){
		case "Glyph":
			return std::make_unique<GlyphPattern>(config);
		/*
		case "Wave":
			return std::make_unique<WavePattern>(config);
		case "Worm":
			return std::make_unique<WormPattern>(config);
		*/
		default:
			std::cerr << "Error. Unknown pattern, try again."
			return nullptr;
	}
}

bool ImagePattern::readConfig()
{
	//TODO make path to config like parameter, and give user 
	//change path in runtime
	std::ifstream file("config/config.json");
	if (!file.is_open()) {
		std::cerr << "Error. Can't open config file\n";
		return 0;
	}

	try {
		file >> config;
	}
	catch (const json::parse_error &e) {
		std::cerr << "JSON parse error: " << e.what()
			<< "\nByte position: " << e.byte << "\n";
		return 0;
	}
	return 1;
}
