#include "WebPattern.h"
#include <vector>
#include <algorithm>
#include <random>

WebPattern::Point::Point (int x, int y) : x{x}, y{y} {}

bool WebPattern::Point::operator == (const Point& point) const
{
	if(x == point.x && y == point.y) return true;

	return false;
}

WebPattern::WebPattern(nlohmann::json& config)
{
	height = config["general"]["height"].get<int>();
	width = config["general"]["width"].get<int>();
	backGroundColor = (config["general"]["backGroundColor"].get<std::string>());
	resizeScale = config["general"]["resizeScale"].get<int>();

	numberOfNodes = config["web"]["numberOfNodes"].get<int>();
	maxNumberOfconnections = config["web"]["maxNumberOfconnections"].get<int>();
	if(maxNumberOfconnections > numberOfNodes)maxNumberOfconnections = numberOfNodes;
	minNumberOfconnections = config["web"]["minNumberOfconnections"].get<int>();
	if(minNumberOfconnections > numberOfNodes)minNumberOfconnections = numberOfNodes;
	nodeColor = config["web"]["nodeColor"].get<std::string>();
	connectionColor = config["web"]["connectionColor"].get<std::string>();
}

void WebPattern::draw ()
{
	Magick::Image canvas;
	canvas.size(Magick::Geometry(width,height));
	canvas.backgroundColor(Magick::Color(backGroundColor));

	std::vector<Point> points;
	placeNode(points);
	makeConnetions(canvas, points);

	canvas.resize(Magick::Geometry(width*resizeScale,height*resizeScale));
	canvas.write("output.png");
}

void WebPattern::placeNode(std::vector<Point>& points) 
{
	std::random_device random;
	std::mt19937 gen(random());
	for(int i = 0; i < numberOfNodes; i++){
		int x = gen() % width;
		int y = gen() % height;
		points.emplace_back(x,y);
	}
}

void WebPattern::makeConnetions(Magick::Image& img, std::vector<Point>& points)
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dist(minNumberOfconnections,maxNumberOfconnections);

	for(int nodeIdex = 0; nodeIdex < numberOfNodes; nodeIdex++){
		std::vector<Point> samplePoints(points);
		samplePoints.erase(std::begin(samplePoints) + nodeIdex);

		img.pixelColor(points[nodeIdex].x, points[nodeIdex].y,Magick::Color(nodeColor));
		int numberOfConnections = dist(gen);
		std::shuffle(std::begin(samplePoints),std::end(samplePoints),random);

		for(int connectionIdex = 0; connectionIdex < numberOfConnections; connectionIdex++){
			img.strokeColor(Magick::Color(connectionColor));
			img.strokeWidth(1);
			img.draw(Magick::DrawableLine(points[nodeIdex].x, points[nodeIdex].y,
			samplePoints[connectionIdex].x, samplePoints[connectionIdex].y));
		}
	}
}
