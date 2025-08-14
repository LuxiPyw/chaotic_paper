#include <string>
#include <vector>
#include "ImagePattern.h"

class GlyphPattern : public ImagePattern{
public:
	GlyphPattern (json&);
	void draw() override;
protected:
	int fontSize;
	int fontPadding;
	std::string fontFamilySet;
	std::string glyphSet;
	int colorSetSize;
	std::vector<std::string> colorSet;
	bool antiAliasing;
	std::map<char, Image> cache;

private:
	void makeGlyphPreRender();
	void initializeImage(Image&);
};
