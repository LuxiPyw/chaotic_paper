#include "ImageMaker.h"
#include <iostream>
#include <string>
#include <Magick++.h>
using namespace Magick;
using json = nlohmann::json;


int main (int argc,char *argv[])
{
	InitializeMagick(*argv);
	ImageMaker image;
	image.readConfig();
	std::string userInput;
	std::cin >> userInput;
	image.choicePattern(userInput);
	return 0;

}
