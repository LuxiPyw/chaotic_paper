#include "ImagePattern.h"
#include <vector>

class WebPattern : public ImagePattern {
public:
	WebPattern(nlohmann::json&);

	void draw() override;

private:

	struct Point {
		bool operator==(const Point& other) const;
		Point(int, int);
		int x;
		int y;
	};

	void placeNode (std::vector<WebPattern::Point>&);

	void makeConnetions (Magick::Image&, std::vector<WebPattern::Point>&);

	int numberOfNodes;
	int maxNumberOfconnections;
	int minNumberOfconnections;
	std::string nodeColor;
	std::string connectionColor;
};
