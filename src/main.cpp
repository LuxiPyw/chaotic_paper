#include "ImageMaker.h"
#include <iostream>
#include <string>
#include <Magick++.h>


int main (int argc,char *argv[])
{
	Magick::InitializeMagick(*argv);
	ImageMaker image;
	image.readConfig();
	std::string userInput;
	std::cin >> userInput;
	auto temp = image.choicePattern(userInput);
	temp->draw();
	return 0;

}
