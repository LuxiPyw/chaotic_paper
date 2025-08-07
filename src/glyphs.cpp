#include <iostream>
#include "glyphs.h"
#include "makeColorSet.h"
#include <string>
#include <Magick++.h>
using namespace Magick;
using string = std::string;


int glyphs (json& config)
{
	int image_height = 0;
	int image_width = 0;
	if(config["glyphs"]["inTiles"].get<bool>()){

	image_height = (config["general"]["image_height"].get<int>()*
		(config["glyphs"]["font_size"].get<int>()+
		config["glyphs"]["font_padding"].get<int>()))+
		config["glyphs"]["font_padding"].get<int>();

	image_width = (config["general"]["image_height"].get<int>()*
		(config["glyphs"]["font_size"].get<int>()+
		config["glyphs"]["font_padding"].get<int>()))+
		config["glyphs"]["font_padding"].get<int>();

	}
	else{
	image_height = config["general"]["image_height"].get<int>();
	image_width = config["general"]["image_width"].get<int>();
	}

	int color_set_size = config["glyphs"]["color_set_size"].get<int>();
	Color backgroundColor (config["general"]["background_color"].get<string>());
	Color color_set [color_set_size];
	makeColorSet(color_set_size, color_set,config);

	string glyph_set = config["glyphs"]["glyph_set"].get<string>();
	
	Image canvas;
	canvas.size(Geometry(image_width,image_height));
	canvas.backgroundColor(Color(backgroundColor));

	return 0;

}

