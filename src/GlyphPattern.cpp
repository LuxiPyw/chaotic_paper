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
	antiAliasing = config["glyphs"]["antiAliasing"].get<bool>();
}
//REMAKE THIS. Because this code need in evry drawPart() call

//this need run in draw() but use threads and different image obj, because otherwise it doesn't thread-safe
//void GlyphPattern::drawPart();

void GlyphPattern::draw() 
{
	makeGlyphPreRender();

	std::srand(static_cast<unsigned int>(time(nullptr)));

	Image canvas;
	canvas.size(Geometry(width,height));
	canvas.backgroundColor(Color(backGroundColor));

	for (int y = fontPadding; y + fontSize <= height; y += fontSize+fontPadding) {
		for (int x = fontPadding; x + fontSize <= width; x += fontSize+fontPadding) {


			std::string randGlyph = std::string(1, glyphSet[rand() % glyphSet.size()]);
			Image preRenderedGlyph = cache[randGlyph[0]];
			std::string randColor = colorSet[rand() % colorSetSize];
			Color finalColor(randColor);

			preRenderedGlyph.colorize(100,finalColor);
			canvas.composite(preRenderedGlyph, x, y, OverCompositeOp);

		}
	}
	canvas.filterType(PointFilter);
	canvas.resize(Geometry(width*resizeScale,height*resizeScale));
	canvas.write("output.png");
}

void GlyphPattern::makeGlyphPreRender()
{
	for(int i = 0; i < glyphSet.size(); i++){
		Image glyphImage (Geometry(fontSize, fontSize), "transparent");
		initializeImage(glyphImage);
		glyphImage.annotate(std::string(1,glyphSet[i]), Magick::CenterGravity);
		cache[glyphSet[i]] = glyphImage;
	}

}

void GlyphPattern::initializeImage(Image& img)
{
	img.font(fontFamilySet);
	img.fillColor("white"); 
	img.fontPointsize(fontSize);
	//antialiasing
	if(antiAliasing){
		img.strokeAntiAlias(false);
		img.textAntiAlias(false);
	}

}
