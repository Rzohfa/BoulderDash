// BoulderDash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <Windows.h>
#include "backend.h"

void readLevel(char **map, int lvl) {
	std::string name = "maps/map" + std::to_string(lvl) + ".txt";
	std::cout << name << "\n";
	std::ifstream is;
	is.open(name);
	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 103; j++)
			is >> map[i][j];
}

void moveStoneTh(char **map, player P, bool **moves) {
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		Sleep(1000);
		for (int i = 0; i < 16; i++) {
			for (int j = 1; j < 102; j++) {
				if (moves[i][j] == true && map[i][j] == 'S' && map[i + 1][j] == 'X') {
					P.decHP();
					std::cout << "ded" << P.hp << "\n";
					moves[i][j] = false;
				}
				if (map[i][j] == 'S') {
					if (map[i + 1][j] == 'A') {
						map[i][j] = 'A';
						map[i + 1][j] = 'S';
						moves[i + 1][j] = true;
						moves[i][j] = false;
					}
					else if (map[i + 1][j + 1] == 'A' && map[i][j + 1] != 'D') {
						map[i][j] = 'A';
						map[i][j + 1] = 'S';
						moves[i][j + 1] = true;
						moves[i][j] = false;
					}
					else if (map[i + 1][j - 1] == 'A' && map[i][j - 1] != 'D') {
						map[i][j] = 'A';
						map[i][j - 1] = 'S';
						moves[i][j - 1] = true;
						moves[i][j] = false;
					}
				}
			}
		}
	}
}

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
	
	bar[0][0].setPosition(sf::Vector2f(4.f, 4.f));
	bar[0][1].setPosition(sf::Vector2f(100.f, 4.f));
	bar[0][2].setPosition(sf::Vector2f(115.f, 4.f));
	bar[0][0].setScale(4, 4);
	bar[0][1].setScale(4, 4);
	bar[0][2].setScale(4, 4);
	window.draw(bar[0][0]);
	window.draw(bar[0][1]);
	if(P.p_rem - P.points == 10)
		window.draw(bar[0][2]);

	bar[1][0].setScale(4, 4);
	for (int i = 0; i < 3; i++) {
		if (i < P.hp) {
			bar[1][0].setPosition(sf::Vector2f(170 + i * 30, 4.f));
			window.draw(bar[1][0]);
		}
		else {
			bar[1][1].setPosition(sf::Vector2f(170 + i * 30, 4.f));
			window.draw(bar[1][1]);
		}
	}

	for (int i = 0; i < 3; i++)
		bar[3][i].setScale(4, 4);

	bar[3][0].setPosition(sf::Vector2f(300.f, 4.f));
	bar[3][1].setPosition(sf::Vector2f(420.f, 4.f));
	bar[3][2].setPosition(sf::Vector2f(435.f, 4.f));

	for (int i = 0; i < 3; i++)
		window.draw(bar[3][i]);

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(), "Boulder Dash", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	player P;

	int level = 1;

	int off_y = window.getSize().y / 180, off_x = window.getSize().x / 180;

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

	sf::Texture texture;
	if (!texture.loadFromFile("BDtex.png"))
		std::cout << "Texture load fail\n";
	else
		std::cout << "Texture load successful!\n";
	
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

	sf::Texture text;
	if (!text.loadFromFile("text.png"))
		std::cout << "Texture load fail\n";
	else
		std::cout << "Texture load successful!\n";

	sf::Sprite **bar = new sf::Sprite*[4];
	bar[0] = new sf::Sprite[3];
	bar[1] = new sf::Sprite[2];
	bar[2] = new sf::Sprite[4];
	bar[3] = new sf::Sprite[3];

	for (int i = 0; i < 3; i++)
		bar[0][i].setTexture(text);
	for (int i = 0; i < 2; i++)
		bar[1][0].setTexture(text);
	for (int i = 0; i < 4; i++)
		bar[2][i].setTexture(text);
	for (int i = 0; i < 3; i++)
		bar[3][i].setTexture(text);

	bar[0][0].setTextureRect(sf::IntRect(0,6,20,5));
	bar[2][0].setTextureRect(sf::IntRect(0,12,24,5));
	bar[3][0].setTextureRect(sf::IntRect(0,18,24,5));

	if (P.p_rem - P.points == 10) {
		bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
		bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
	}
	else
		bar[0][1].setTextureRect(sf::IntRect(((P.p_rem-P.points) + (P.p_rem - P.points) * 3), 0, 3, 5));

	bar[1][0].setTextureRect(sf::IntRect(42, 0, 7, 6));
	bar[1][1].setTextureRect(sf::IntRect(42, 20, 7, 6));

	bar[2][3].setTextureRect(sf::IntRect(((level % 10) * 3) + (level % 10), 0, 3, 5));
	bar[2][2].setTextureRect(sf::IntRect((((level / 10) % 10) * 3) + ((level / 10) % 10), 0, 3, 5));
	bar[2][1].setTextureRect(sf::IntRect((((level / 100) % 10) * 3) + ((level / 100) % 10), 0, 3, 5));

	bar[3][2].setTextureRect(sf::IntRect(((level % 10) * 3) + (level % 10), 0, 3, 5));
	bar[3][1].setTextureRect(sf::IntRect((((level/10) % 10) * 3) + ((level / 10) % 10), 0, 3, 5));

	bool** movedStone = new bool*[17];
	for (int i = 0; i < 17; i++)
		movedStone[i] = new bool[103];

	for (int i = 0; i < 17; i++)
		for (int j = 0; j < 103; j++)
			movedStone[i][j] = false;

	std::thread t1(moveStoneTh, map, P, movedStone);

	while (window.isOpen())
	{
		window.clear();
		drawMap(map, sprites, bar, window, off_x, off_y, P);
		sf::Event event;
		
		bar[1][0].setScale(4, 4);
		for (int i = 0; i < P.hp; i++) {
			bar[1][0].setPosition(sf::Vector2f(170 + i * 30, 4.f));
			window.draw(bar[1][0]);
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W) {
					if (P.p_rem == P.points && map[P.y - 1][P.x] == 'E') {
						level++;
						readLevel(map, level);
						P.finished = 1;
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
									P.points++;
							}
							std::cout << "\n";
							off_y = window.getSize().y / 180;
							off_x = window.getSize().x / 180;
						}
					}
					else if (map[P.y - 1][P.x] != 'B' && map[P.y - 1][P.x] != 'S' && map[P.y - 1][P.x] != 'E') {
						if (map[P.y - 1][P.x] == 'P') {
							P.points++;
							if (P.p_rem - P.points == 10) {
								bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
								bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
							}
							else
								bar[0][1].setTextureRect(sf::IntRect(((P.p_rem - P.points) + (P.p_rem - P.points) * 3), 0, 3, 5));
						}
						map[P.y][P.x] = 'A';
						P.y--;
						map[P.y][P.x] = 'X';
						off_y++;
					}
				}
				else if (event.key.code == sf::Keyboard::S) {
					if (P.p_rem == P.points && map[P.y + 1][P.x] == 'E') {
						level++;
						readLevel(map, level);
						P.finished = 1;
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
									P.points++;
							}
							std::cout << "\n";
						}
						off_y = window.getSize().y / 180;
						off_x = window.getSize().x / 180;
					}
					else if (map[P.y + 1][P.x] != 'B' && map[P.y + 1][P.x] != 'S' && map[P.y + 1][P.x] != 'E') {
						if (map[P.y + 1][P.x] == 'P') {
							P.points++;
							if (P.p_rem - P.points == 10) {
								bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
								bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
							}
							else
								bar[0][1].setTextureRect(sf::IntRect(((P.p_rem - P.points) + (P.p_rem - P.points) * 3), 0, 3, 5));
						}
						map[P.y][P.x] = 'A';
						P.y++;
						map[P.y][P.x] = 'X';
						off_y--;
					}
				}
				else if (event.key.code == sf::Keyboard::A) {
					if (P.p_rem == P.points && map[P.y][P.x - 1] == 'E') {
						level++;
						readLevel(map, level);
						P.finished = 1;
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
									P.points++;
							}
							std::cout << "\n";
						}
						off_y = window.getSize().y / 180;
						off_x = window.getSize().x / 180;
					}
					else if (map[P.y][P.x - 1] != 'B' && map[P.y][P.x - 1] != 'S' && map[P.y][P.x - 1] != 'E') {
						if (map[P.y][P.x - 1] == 'P') {
							P.points++;
							if (P.p_rem - P.points == 10) {
								bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
								bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
							}
							else
								bar[0][1].setTextureRect(sf::IntRect(((P.p_rem - P.points) + (P.p_rem - P.points) * 3), 0, 3, 5));
						}
						map[P.y][P.x] = 'A';
						P.x--;
						map[P.y][P.x] = 'X';
						off_x++;
					}
				}
				else if (event.key.code == sf::Keyboard::D) {
					if (P.p_rem == P.points && map[P.y][P.x + 1] == 'E') {
						level++;
						readLevel(map, level);
						P.finished = 1;
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
									P.points++;
							}
							std::cout << "\n";
						}
						off_y = window.getSize().y / 180;
						off_x = window.getSize().x / 180;

					}
					else if (map[P.y][P.x + 1] != 'B' && map[P.y][P.x + 1] != 'S' && map[P.y][P.x + 1] != 'E') {
						if (map[P.y][P.x + 1] == 'P') {
							P.points++;
							if (P.p_rem - P.points == 10) {
								bar[0][1].setTextureRect(sf::IntRect(4, 0, 3, 5));
								bar[0][2].setTextureRect(sf::IntRect(0, 0, 3, 5));
							}
							else
								bar[0][1].setTextureRect(sf::IntRect(((P.p_rem - P.points) + (P.p_rem - P.points) * 3), 0, 3, 5));
						}
						map[P.y][P.x] = 'A';
						P.x++;
						map[P.y][P.x] = 'X';
						off_x--;
					}
				}
				
			}
		}

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			t1.join();
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			std::cout << P.hp << "\n";
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

		//std::cout << P.points << "\n";
		
	}

	return 0;
}
