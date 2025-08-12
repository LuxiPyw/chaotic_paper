#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include "ImagePattern.h"
using json = nlohmann::json;

class ImageMaker {

public:
	json config;
	bool readConfig();
	std::unique_ptr<ImagePattern> choicePattern (std::string);
};






