#include <string>
#include <Magick++.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace Magick;

class ImagePattern {
public:
	virtual ~ImagePattern() = default;
	virtual void draw() = 0;
protected:
	int width;
	int height;
	int resizeScale;
	std::string backGroundColor;
};
