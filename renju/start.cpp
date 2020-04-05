#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "interaction.h"
#include "evaluate.h"

int main()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
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
			cout << "�������֣�������" << endl;
		}
		else if (temp == "newwhite")
		{
			aiTurn = white;
			cout << "���Ժ��֣�������" << endl;
		}
			
		else
		{
			cout << "���벻�Ϸ�������������22" << endl;
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
				cout << "AI��ʤ" << endl;
			else
				cout << "�������ʤ��" << endl;
			break;
		}
		turn++;
	}
	return 0;
}
