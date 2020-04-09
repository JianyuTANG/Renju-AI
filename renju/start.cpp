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
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;

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
			cout << "�������֣�������" << endl;
		}
		else if (temp == "newwhite")
		{
			aiTurn = white;
			cout << "���Ժ��֣�������" << endl;
		}
			
		else
		{
			cout << "���벻�Ϸ�������������" << endl;
			newgame = false;
		}
	}
	string temp;
	getline(cin, temp);
	if (aiTurn == black)
	{
		cout << "AI����" << endl;
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
				cout << "���ѻ�ʤ" << endl;
				return 0;
			}
			else if (temp == 2)
			{
				cout << "AI��ʤ" << endl;
				return 0;
			}
			cout << "AI����" << endl;
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
