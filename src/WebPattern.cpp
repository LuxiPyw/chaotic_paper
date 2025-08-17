#include "WebPattern.h"
#include <vector>
#include <iostream>
#include <random>

//I NEED REMAKE ALL FILES TO REMOVE ALL USING & USING NAMESPACE

WebPattern::Point::Point (int x, int y) : x{x}, y{y} {}

bool WebPattern::Point::operator == (const Point& point) const
{
	if(x == point.x && y == point.y) return true;

	return false;
}

WebPattern::WebPattern(json& config)
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
	std::cout << "2";
	Image canvas;
	canvas.size(Geometry(width,height));
	canvas.backgroundColor(Color(backGroundColor));

	std::vector<Point> points;
	placeNode(points);
	makeConnetions(canvas, points);

	canvas.resize(Geometry(width*resizeScale,height*resizeScale));
	canvas.write("output.png");
}

void WebPattern::placeNode(std::vector<Point>& points) 
{
	std::cout << "3";
	std::random_device random;
	std::mt19937 gen(random());
	for(int i = 0; i < numberOfNodes; i++){
		int x = gen() % width;
		int y = gen() % height;
		points.emplace_back(x,y);
	}
}

void WebPattern::makeConnetions(Image& img, std::vector<Point>& points)
{
	std::cout << "4";
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<> dist(minNumberOfconnections,maxNumberOfconnections);

	for(int i = 0; i < numberOfNodes; i++){
		std::vector<Point> usedPoints;
		usedPoints.push_back(points[i]);

		img.pixelColor(points[i].x, points[i].y,Color(nodeColor));
		int numberOfConnections = dist(gen);

		for(int j = 0; j < numberOfConnections; j++){
			findPoint:
			int randomPoint = gen() % points.size();

			for(int k = 0; k < usedPoints.size(); k++){
				if(points[randomPoint] == usedPoints[k]){
					goto findPoint;
				}
			}
			usedPoints.push_back(points[randomPoint]);
			
			img.strokeColor(Color(connectionColor));
			img.strokeWidth(1);
			img.draw(Magick::DrawableLine(points[i].x, points[i].y, points[randomPoint].x, points[randomPoint].y));
			//WHERE I NEED MAKE DRAW LINE AND CONFIG THIS LINE
		}
	}
	
}
