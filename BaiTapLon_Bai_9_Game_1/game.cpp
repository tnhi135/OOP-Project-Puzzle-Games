// Day la file chuong trinh chinh
#pragma once
#include "game.h"
#include "tetris.cpp"
#include "mahjong.cpp"

void listgame(game *g[], int n)
{
	for (int i = 0; i < n; i++)
	{
		g[i]->play();
	}
}

void playGame(game *g[], int n)
{
	g[n]->play();
}

void menu(string tenGame[], int v)
{
	cout << "--------------------------OOP_FinalProject--------------------------" << endl << endl;
	//cout << "               Chao mung ban den voi Pinky!" << endl << endl;
	cout << "The program has " << v << " following games:" << endl;
	for (int i = 0; i < v; i++)
	{
		cout << tenGame[i] << " ------- Please press key " << i << " to start the game!" << endl;
	}
	//cout << "Please press " << v << " to play both!" << endl;
	cout << endl;
}

void chonGame(int v, int& u)
{
	cout << "Please choose the game you want to play: ";
	cin >> u;
	cout << endl;
	while (u > v)
	{
		cout << "Sorry! The game you selected is temporarily unsupported!" << endl;
		cout << "Please re-enter the game you like according to the list above: ";
		cin >> u;
		cout << endl;
	}
}

void chonLaiGame(game *g[], int u, int v, int& l, int x)	//neu x=0 thi chay tat ca tro choi
{
	game* g1[] = {
		new tetris,
		new mahjong
	};
	cout << "Want to play again: Please press key 1" << endl;
	cout << "Want to choose a game by menu: Please press key 2" << endl;
	cout << "Want to exit: Please press other keys" << endl << endl;

	cout << "You choose: ";
	cin >> l;

	if ((l == 1) && (x == 1))
	{
		playGame(g1, u);
	}
	else if ((l == 1) && (x == 0))
	{
		listgame(g1, u);
	}
	else if (l == 2)
	{
		chonGame(v, u);
		playGame(g1, u);
	}
	else
	{
		exit(0);
	}
}
void main()
{
	const int v = 2;	//so tro choi trong game
	int u = 0;
	int l = 0;
	game *g[] = {
		new tetris,
		new mahjong
	};
	string tenGame[v] = {		//mang chua ten cac game theo thu tu
		"TETRIS",
		"MAHJONG"
	};
	menu(tenGame, v);
	chonGame(v, u);
	if (u == v)
	{
		listgame(g, u);
		while (true)
		{
			chonLaiGame(g, u, v, l, 0);

		}
	}
	else
	{
		playGame(g, u);
		while (true)
		{
			chonLaiGame(g, u, v, l, 1);
		}
	}






}