#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "interaction.h"
#include "evaluate.h"

int main()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	cout << "输入: move x y  表示落子点" << endl;
	clock_t startTime, endTime;
	startTime = clock();
	for(int i=0;i<100000;i++)
	evaluate();
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) << "ms" << endl;
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
			cout << "输入不合法，请重新输入22" << endl;
			newgame = false;
		}
	}

	while (1)
	{
		if ((turn % 2) == aiTurn)
		{
			makeMove();
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
