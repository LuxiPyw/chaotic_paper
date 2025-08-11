#include <string>
#include <nlohmann/json.hpp>
#include <memory>
using json = nlohmann::json;

class ImageMaker {

public:
	json config;
	bool readConfig();
	static std::unique_ptr<ImagePattern> choicePattern (std::string);
};






