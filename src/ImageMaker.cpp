#include <iostream>
#include <fstream>
#include "ImageMaker.h"
#include "GlyphPattern.h"
#include "WebPattern.h"

std::unique_ptr<ImagePattern> ImageMaker::choicePattern(std::string userInput)
{
	if (userInput == "Glyph") return std::make_unique<GlyphPattern>(config);

	else if (userInput == "Web"){
		return std::make_unique<WebPattern>(config);
	}
		/*
			return std::make_unique<WavePattern>(config);
		case "Worm":
			return std::make_unique<WormPattern>(config);
		*/
	else{
		std::cerr << "Error. Unknown pattern, try again.";
		return nullptr;
	}
}

bool ImageMaker::readConfig()
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
	catch (const nlohmann::json::parse_error &e) {
		std::cerr << "JSON parse error: " << e.what()
			<< "\nByte position: " << e.byte << "\n";
		return 0;
	}
	return 1;
}
