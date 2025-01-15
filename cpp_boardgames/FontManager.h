//FontManager.h
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class FontManager {
private:
	sf::Font font;
public:
	FontManager();
	sf::Font& loadArialFont(const std::string& filename) {
		if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
			std::cerr << "Warning: Failed to load font" << std::endl;
		}
	};

};
#endif // FONTMANAGER_H
