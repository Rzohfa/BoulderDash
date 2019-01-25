// BoulderDash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

void readLevel(char **map, int lvl) {
	std::string name = "maps/map" + std::to_string(lvl) + ".txt";
	std::cout << name << "\n";
	std::ifstream is;
	is.open(name);
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 103; j++)
			is >> map[i][j];
}

struct player {
	unsigned short int x, y, points = 0, p_rem = 0, _x, _y, hp;
};

void drawMap(char **map, sf::Sprite *sprites, sf::Sprite **bar, sf::RenderTarget &window, int off_x, int off_y, player P) {
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 103; j++) {
			if (map[i][j] == 'B') {
				sprites[0].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[0]);
			}
			else if (map[i][j] == 'S') {
				sprites[2].setPosition(sf::Vector2f(j*64.f + off_x*64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[2]);
			}
			else if (map[i][j] == 'L') {
				sprites[6].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[6]);
			}
			else if (map[i][j] == 'X') {
				sprites[5].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[5]);
			}
			else if (map[i][j] == 'E') {
				sprites[4].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[4]);
			}
			else if (map[i][j] == 'D') {
				sprites[1].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[1]);
			}
			else if (map[i][j] == 'P') {
				sprites[3].setPosition(sf::Vector2f(j*64.f + off_x * 64.f, i*64.f + off_y * 64.f));
				window.draw(sprites[3]);
			}
		}
	}
	

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(), "Boulder Dash", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	player P;

	int level = 1;

	int off_y = window.getSize().y / 180, off_x = window.getSize().x / 180;

	sf::Texture texture;
	if (!texture.loadFromFile("BDtex.png"))
		std::cout << "Texture load fail\n";
	else
		std::cout << "Texture load successful!\n";

	sf::Texture text;
	if (!texture.loadFromFile("text.png"))
		std::cout << "Texture load fail\n";
	else
		std::cout << "Texture load successful!\n";

	sf::Sprite **bar = new sf::Sprite*[4];
	bar[0] = new sf::Sprite[3];
	bar[1] = new sf::Sprite[1];
	bar[2] = new sf::Sprite[4];
	bar[3] = new sf::Sprite[3];

	for (int i = 0; i < 3; i++)
		bar[0][i].setTexture(text);
	bar[1][0].setTexture(text);
	for (int i = 0; i < 4; i++)
		bar[2][i].setTexture(text);
	for (int i = 0; i < 3; i++)
		bar[3][i].setTexture(text);

	bar[0][0].setTextureRect(sf::IntRect(0,6,20,5));
	bar[2][0].setTextureRect(sf::IntRect(0,12,24,5));
	bar[3][0].setTextureRect(sf::IntRect(0,18,24,5));

	if (P.p_rem == 10) {
		bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
		bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
	}
	else
		bar[0][1].setTextureRect(sf::IntRect((P.p_rem + P.p_rem * 3), 0, 3, 5));

	for(int i=0;i<P.hp;i++)
		bar[1][i].setTextureRect(sf::IntRect(42, 0, 7, 6));

	bar[2][3].setTextureRect(sf::IntRect(((level % 10) * 3) + (level % 10), 0, 3, 5));
	bar[2][2].setTextureRect(sf::IntRect((((level / 10) % 10) * 3) + ((level / 10) % 10), 0, 3, 5));
	bar[2][1].setTextureRect(sf::IntRect((((level / 100) % 10) * 3) + ((level / 100) % 10), 0, 3, 5));

	bar[3][2].setTextureRect(sf::IntRect(((level % 10) * 3) + (level % 10), 0, 3, 5));
	bar[3][1].setTextureRect(sf::IntRect((((level/10) % 10) * 3) + ((level / 10) % 10), 0, 3, 5));
	
	sf::Sprite *sprites = new sf::Sprite[7];

	for (int i = 0; i < 6; i++)
		sprites[i].setTexture(texture);

	sprites[0].setTextureRect(sf::IntRect(0, 0, 64, 64));
	sprites[1].setTextureRect(sf::IntRect(64, 0, 64, 64));
	sprites[2].setTextureRect(sf::IntRect(128, 0, 64, 64));
	sprites[3].setTextureRect(sf::IntRect(192, 0, 64, 64));
	sprites[4].setTextureRect(sf::IntRect(64, 64, 64, 64));
	sprites[5].setTextureRect(sf::IntRect(128, 64, 64, 64));
	sprites[6].setTextureRect(sf::IntRect(192, 64, 64, 64));



	char** map = new char*[17];
	for (int i = 0; i < 17; i++)
		map[i] = new char[103];

	

	readLevel(map, level);

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 103; j++) {
				std::cout << map[i][j] << "";
				if (map[i][j] == 'X') {
					P.x = j;
					P.y = i;
					P._x = j;
					P._y = i;
				}
				else if (map[i][j] == 'P')
					P.p_rem++;
			}
			std::cout << "\n";
	}

	while (window.isOpen())
	{
		window.clear();
		drawMap(map, sprites, bar, window, off_x, off_y, P);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) {
					if (map[P.y - 1][P.x] != 'B' && map[P.y - 1][P.x] != 'S' && map[P.y - 1][P.x] != 'E') {
						if (map[P.y - 1][P.x] == 'P')
							P.points++;
						map[P.y][P.x] = 'A';
						P.y--;
						map[P.y][P.x] = 'X';
						off_y++;
					}
				}
				else if (event.key.code == sf::Keyboard::S) {
					if (map[P.y + 1][P.x] != 'B' && map[P.y + 1][P.x] != 'S' && map[P.y + 1][P.x] != 'E') {
						if (map[P.y + 1][P.x] == 'P')
							P.points++;
						map[P.y][P.x] = 'A';
						P.y++;
						map[P.y][P.x] = 'X';
						off_y--;
					}
				}
				else if (event.key.code == sf::Keyboard::A) {
					if (map[P.y][P.x - 1] != 'B' && map[P.y][P.x - 1] != 'S' && map[P.y][P.x - 1] != 'E') {
						if (map[P.y][P.x - 1] == 'P')
							P.points++;
						map[P.y][P.x] = 'A';
						P.x--;
						map[P.y][P.x] = 'X';
						off_x++;
					}
				}
				else if (event.key.code == sf::Keyboard::D) {
					if (map[P.y][P.x + 1] != 'B' && map[P.y][P.x + 1] != 'S' && map[P.y][P.x + 1] != 'E') {
						if (map[P.y][P.x + 1] == 'P')
							P.points++;
						map[P.y][P.x] = 'A';
						P.x++;
						map[P.y][P.x] = 'X';
						off_x--;
					}
				}
				
			}
		}

		/*for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 103; j++) {
				if (map[i][j] == 'B') {
					sprites[0].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[0]);
				}
				else if (map[i][j] == 'S') {
					sprites[2].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[2]);
				}
				else if (map[i][j] == 'L') {
					sprites[6].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[6]);
				}
				else if (map[i][j] == 'X') {
					sprites[5].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[5]);
				}
				else if (map[i][j] == 'E') {
					sprites[4].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[4]);
				}
				else if (map[i][j] == 'D') {
					sprites[1].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[1]);
				}
				else if (map[i][j] == 'P') {
					sprites[3].setPosition(sf::Vector2f(j*64.f, i*64.f));
					window.draw(sprites[3]);
				}
			}
		}*/

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			readLevel(map, level);
			P.x = P._x;
			P.y = P._y;
			P.points = 0;
			off_y = window.getSize().y / 180;
			off_x = window.getSize().x / 180;
			sprites[4].setTextureRect(sf::IntRect(64, 64, 64, 64));
		}
		if (P.points == 10)
			sprites[4].setTextureRect(sf::IntRect(0, 64, 64, 64));

		std::cout << P.points << "\n";
		
	}

	return 0;
}
