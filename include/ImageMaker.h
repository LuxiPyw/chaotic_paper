#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include "ImagePattern.h"

class ImageMaker {

public:
	nlohmann::json config;
	bool readConfig();
	std::unique_ptr<ImagePattern> choicePattern (std::string);
};






