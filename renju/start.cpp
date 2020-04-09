#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "interaction.h"
#include "evaluate.h"
#include <chrono>

using namespace std;

int main()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	cout << "输入: move x y  表示落子点" << endl;

	//evaluate();

	//auto start = std::chrono::steady_clock::now();
	//for(int i=0;i<100000;i++)
	//	evaluate();
	//auto end = std::chrono::steady_clock::now();
	//auto duration = std::chrono::duration<float, std::milli>(end - start);
	//cout << "Totle Time : " << duration.count() << "ms" << endl;

	print();
	
	bool newgame = false;
	bool isBlack = false;
	int turn = black;
	int aiTurn;
	while (!newgame)
	{
		newgame = true;
		string temp;
		cin >> temp;
		if (temp == "newblack")
		{
			aiTurn = black;
			cout << "电脑先手，您后手" << endl;
		}
		else if (temp == "newwhite")
		{
			aiTurn = white;
			cout << "电脑后手，您先手" << endl;
		}
			
		else
		{
			cout << "输入不合法，请重新输入" << endl;
			newgame = false;
		}
	}
	string temp;
	getline(cin, temp);
	if (aiTurn == black)
	{
		cout << "AI走棋" << endl;
		chessBoard[8][8] = black;
		print();
		turn++;
	}

	while (1)
	{
		if ((turn % 2) == (aiTurn % 2))
		{
			
			int temp = iterationDeepening(aiTurn);
			if (temp == 1)
			{
				cout << "您已获胜" << endl;
				return 0;
			}
			else if (temp == 2)
			{
				cout << "AI获胜" << endl;
				return 0;
			}
			cout << "AI走棋" << endl;
		}
		else
		{
			input(aiTurn);
		}
		print();

		if (gameover())
		{
			if ((turn % 2) == aiTurn)
				cout << "AI获胜" << endl;
			else
				cout << "您获得了胜利" << endl;
			break;
		}
		turn++;
	}
	return 0;
}
