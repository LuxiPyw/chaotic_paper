#include <cstdlib>
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

	int font_size = config["glyphs"]["font_size"].get<int>();
	int font_padding = config["glyphs"]["font_padding"].get<int>();

	int color_set_size = config["glyphs"]["color_set_size"].get<int>();
	string backgroundColor (config["general"]["background_color"].get<string>());
	string color_set [color_set_size];
	makeColorSet(color_set_size, color_set,config);

	//!!!!TODO MAKE FONT CHOICE IN JSON CONFIG
	Image canvas;
	canvas.size(Geometry(image_width,image_height));
	canvas.backgroundColor(Color(backgroundColor));
	//font
	canvas.font("fonts/Tinyunicode.ttf");
    canvas.fontPointsize(font_size);
	//Antialias
	canvas.strokeAntiAlias(false);
	canvas.textAntiAlias(false);

	string glyph_set = config["glyphs"]["glyph_set"].get<string>();

	for (int x = font_padding; x < image_width; x += font_size+font_padding) {

		for (int y = font_padding; y < image_height; y += font_size+font_padding) {

			string rand_glyph = string(1, glyph_set[rand() % glyph_set.size()]);
			string rand_color = color_set[rand() % color_set_size];

			int cx = x + font_size / 2;
			int cy = y + font_size / 2;

			canvas.fillColor(rand_color);
            canvas.annotate(rand_glyph, Geometry(0, 0, cx, cy), NorthWestGravity);

		}
	}

	canvas.write("output.png");
	return 0;

}

