#include "GlyphPattern.h"
#include <iostream>
#include <cstdlib>

GlyphPattern::GlyphPattern(json& config)
{
	height = config["general"]["height"].get<int>();
	width = config["general"]["width"].get<int>();

	fontSize = config["glyphs"]["fontSize"].get<int>();
	fontPadding = config["glyphs"]["fontPadding"].get<int>();
	resizeScale = config["general"]["resizeScale"].get<int>();
	fontFamilySet = "fonts/";
	fontFamilySet += config["glyphs"]["fontFamilySet"].get<std::string>();
	glyphSet = config["glyphs"]["glyphSet"].get<std::string>();

	if(config["glyphs"]["inTiles"].get<bool>()){
		height = (height*(fontSize+fontPadding)+fontPadding);
		width = (width*(fontSize+fontPadding)+fontPadding);
	}

	colorSetSize = config["glyphs"]["colorSetSize"].get<int>();
	backGroundColor = (config["general"]["backGroundColor"].get<std::string>());
	for(int i = 0; i < colorSetSize; i++){
	colorSet.push_back( (config["glyphs"]["colorSet"][i].get<std::string>()) );
	}
}

void GlyphPattern::draw() 
{
	std::srand(static_cast<unsigned int>(time(nullptr)));
	Image canvas;
	canvas.size(Geometry(width,height));
	canvas.backgroundColor(Color(backGroundColor));

	canvas.font(fontFamilySet);
    canvas.fontPointsize(fontSize);
	
	//antialias
	canvas.strokeAntiAlias(false);
	canvas.textAntiAlias(false);

	for (int y = fontPadding; y + fontSize <= height; y += fontSize+fontPadding) {
		for (int x = fontPadding; x + fontSize <= width; x += fontSize+fontPadding) {


			std::string randGlyph = std::string(1, glyphSet[rand() % glyphSet.size()]);
			std::string randColor = colorSet[rand() % colorSetSize];


			canvas.fillColor(randColor);
            canvas.annotate(randGlyph, Geometry(0, 0, x, y), NorthWestGravity);

		}
	}
	canvas.filterType(PointFilter);
	canvas.resize(Geometry(width*resizeScale,height*resizeScale));
	canvas.write("output.png");
}
