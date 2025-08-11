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
};
