#include <nlohmann/json.hpp>
#include <Magick++.h>
using namespace Magick;
using json = nlohmann::json;

void makeColorSet (int&, Color*, json& );
