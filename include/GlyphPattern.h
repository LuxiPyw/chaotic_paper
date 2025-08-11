#include "ImagePattern.h"

class GlyphPattern : public ImagePattern{
public:
	GlyphPattern (json&);
	void draw() override;
protected:
	int fontSize;
	int fontPadding;
	std::string font_family_set;
	std::string glyph_set;
	int color_set_size;
	std::string color_set;
};
