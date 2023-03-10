// Day la file khai bao, dinh nghia lop, ham game tetris 

#pragma once

#include<conio.h>
#include "Header.h"
#include "game.h"

class tetris :public game
{
	const int M = 20;
	const int N = 10;

	int field[20][10] = { 0 };

	struct Point
	{
		int x = 0;
		int y = 0;
	} a[4], b[4];


	int figures[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};

	bool check()
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i].x < 0 || a[i].x >= 10 || a[i].y >= 20)
			{
				return 0;
			}
			else if (field[a[i].y][a[i].x])
			{
				return 0;
			}
		}
			
		return 1;
	}

public:
	
	virtual void play() 
	{
		int n = 0;
		srand(int(time(0)));
		RenderWindow window(VideoMode(320, 480), "TETRIS!");

		Texture t1, t2;
		t1.loadFromFile("C:\\Users\\nnhi\\source\\repos\\OOP_Project\\BaiTapLon_Bai_9_Game_1\\tiles.png");
		t2.loadFromFile("C:\\Users\\nnhi\\source\\repos\\OOP_Project\\BaiTapLon_Bai_9_Game_1\\background.png");

		Sprite s(t1), background(t2);

		int dx = 0; bool rotate = 0; int colorNum = 1;
		double timer = 0, delay = 0.3;

		Clock clock;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window.close();
				}

				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::Up)
					{
						rotate = true;
					}
					else if (e.key.code == Keyboard::Left)
					{
						dx = -1;
					}
					else if (e.key.code == Keyboard::Right)
					{
						dx = 1;
					}
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				delay = 0.05;
			}

			// Di chuyen
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];
				a[i].x += dx;
			}
			if (!check()) //neu check tra ve 0
			{
				for (int i = 0; i < 4; i++)
				{
					a[i] = b[i];
				}
			}

			//Xoay
			if (rotate)
			{

				Point p = a[1]; //tâm xoay
				for (int i = 0; i < 4; i++)
				{
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}

			//thoi gian
			if (timer > delay)
			{
				for (int i = 0; i < 4; i++)
				{

					b[i] = a[i];
					a[i].y += 1;
				}

				if (!check())
				{
					for (int i = 0; i < 4; i++)
					{
						field[b[i].y][b[i].x] = colorNum;
					}
					int n = rand() % 7;
					colorNum = 1 + rand() % 7;
					for (int i = 0; i < 4; i++)
					{
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				}

				timer = 0;
			}

			//kiem tra dong
			int k = M - 1;
			for (int i = M - 1; i > 0; i--)
			{
				int count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[i][j])
					{
						count++;
					}
					field[k][j] = field[i][j];
				}
				if (count < 10)
				{
					k--;
				}
				else
				{
					n++;
				}
			}

			dx = 0; rotate = 0; delay = 0.3;

			//Ve
			window.clear(Color::White);
			window.draw(background);
			int count1 = 0;
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
				{
					if (field[19][j] != 0)
					{
						count1++;
					}
					if (field[1][j] != 0)
					{
						count1++;
						if (count1 >= 2)
						{
							window.close();
						}
					}
					if (field[i][j] == 0)
					{
						continue;
					}
					s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
					s.setPosition(float(j * 18), float(i * 18));
					s.move(28, 31); //offset
					window.draw(s);
				}
			for (int i = 0; i < 4; i++)
			{
				s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
				s.setPosition(float(a[i].x * 18), float(a[i].y * 18));
				s.move(28, 31); //offset
				window.draw(s);
			}
			window.display();
		}
		cout << "SO DONG BAN DA XOA DUOC: " << n << endl << endl;
	}
};