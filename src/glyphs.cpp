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
	std::srand(static_cast<unsigned int>(time(nullptr)));
	//general settings
	int image_height = config["general"]["image_height"].get<int>();
	int image_width = config["general"]["image_width"].get<int>();
	int font_size = config["glyphs"]["font_size"].get<int>();
	int font_padding = config["glyphs"]["font_padding"].get<int>();
	int image_scale = config["general"]["image_scale"].get<int>();

	if(config["glyphs"]["inTiles"].get<bool>()){

		image_height = (image_height*(font_size+font_padding)+font_padding);
		image_width = (image_width*(font_size+font_padding)+font_padding);

	}

	//colors
	int color_set_size = config["glyphs"]["color_set_size"].get<int>();
	string backgroundColor (config["general"]["background_color"].get<string>());
	string color_set [color_set_size];
	makeColorSet(color_set_size, color_set,config);

	Image canvas;
	canvas.size(Geometry(image_width,image_height));
	canvas.backgroundColor(Color(backgroundColor));
	//font
	string font_family_set = "fonts/";
	font_family_set += config["glyphs"]["font_family_set"].get<string>();
	canvas.font(font_family_set);
    canvas.fontPointsize(font_size);

	//antialias
	canvas.strokeAntiAlias(false);
	canvas.textAntiAlias(false);

	string glyph_set = config["glyphs"]["glyph_set"].get<string>();

	std::cout << image_height << "\n";
	std::cout << image_width << "\n";

	for (int y = font_padding; y + font_size <= image_height; y += font_size+font_padding) {
		for (int x = font_padding; x + font_size <= image_width; x += font_size+font_padding) {


			string rand_glyph = string(1, glyph_set[rand() % glyph_set.size()]);
			string rand_color = color_set[rand() % color_set_size];


			canvas.fillColor(rand_color);
            canvas.annotate(rand_glyph, Geometry(0, 0, x, y), NorthWestGravity);

		}
	}

	canvas.filterType(PointFilter);
	canvas.resize(Geometry(image_width*image_scale,image_height*image_scale));
	canvas.write("output.png");
	return 0;

}

