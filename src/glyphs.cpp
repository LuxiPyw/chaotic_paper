#include "glyphs.h"
#include <Magick++.h>
using namespace Magick;

int glyphs (json& config)
{
	if(config["glyphs"]["inTiles"].get<bool>()){

	int (image_height = config["general"]["image_height"].get<int>()*
		(config["glyphs"]["font_size"].get<int>()+
		config["glyphs"]["font_padding"].get<int>()))+
		config["glyphs"]["font_padding"].get<int>();

	int image_width = config["general"]["image_height"].get<int>()*
		(config["glyphs"]["font_size"].get<int>()+
		config["glyphs"]["font_padding"].get<int>()))+
		config["glyphs"]["font_padding"].get<int>();

	}
	else{
	int image_height = config["general"]["image_height"].get<int>();
	int image_width = config["general"]["image_width"].get<int>();
	}



}

