#include "GlyphPattern.h"
#include <cstdlib>

GlyphPattern::GlyphPattern(json& config)
{
	height = config["general"]["image_height"].get<int>();
	width = config["general"]["image_width"].get<int>();

	if(config["glyphs"]["inTiles"].get<bool>()){
		image_height = (image_height*(font_size+font_padding)+font_padding);
		image_width = (image_width*(font_size+font_padding)+font_padding);
	}

	fontSize = config["glyphs"]["font_size"].get<int>();
	fontPadding = config["glyphs"]["font_padding"].get<int>();
	resizeScale = config["general"]["image_scale"].get<int>();
	font_family_set = "fonts/";
	font_family_set += config["glyphs"]["font_family_set"].get<std::string>();
	glyph_set = config["glyphs"]["glyph_set"].get<string>();

	color_set_size = config["glyphs"]["color_set_size"].get<int>();
	backGroundColor (config["general"]["background_color"].get<string>());
	color_set [color_set_size];
	for(int i = 0; i < color_set_size; i++){
	color_set[i] = (config["glyphs"]["color_set"][i].get<string>());
	}
}

void GlyphPattern::draw() override
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
	Image canvas;
	canvas.size(Geometry(image_width,image_height));
	canvas.backgroundColor(Color(backgroundColor));

	canvas.font(font_family_set);
    canvas.fontPointsize(font_size);
	
	//antialias
	canvas.strokeAntiAlias(false);
	canvas.textAntiAlias(false);

	for (int y = font_padding; y + font_size <= image_height; y += font_size+font_padding) {
		for (int x = font_padding; x + font_size <= image_width; x += font_size+font_padding) {


			std::string rand_glyph = string(1, glyph_set[rand() % glyph_set.size()]);
			std::string rand_color = color_set[rand() % color_set_size];


			canvas.fillColor(rand_color);
            canvas.annotate(rand_glyph, Geometry(0, 0, x, y), NorthWestGravity);

		}
	}
	canvas.filterType(PointFilter);
	canvas.resize(Geometry(image_width*image_scale,image_height*image_scale));
	canvas.write("output.png");
}
