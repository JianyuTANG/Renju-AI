#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include "interaction.h"
#include "evaluate.h"
#include <conio.h>
#include <chrono>

using namespace std;

int new_game(int);
void replay();

int main()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
	cout << "����: regret    ����һ��" << endl;
	print();

	int aiTurn;
	while (1)
	{
		string temp;
		cin >> temp;
		if (temp == "newblack")
		{
			aiTurn = black;
			break;
		}
		else if (temp == "newwhite")
		{
			aiTurn = white;
			break;
		}
		else
		{
			cout << "���벻�Ϸ�������������" << endl;
		}
	}

	string temp;
	getline(cin, temp);
	while (1)
	{
		
		if( aiTurn == black)
			cout << "�������֣�������" << endl;
		else
			cout << "���Ժ��֣�������" << endl;
		aiTurn = new_game(aiTurn); // ����һ����Ϸ

		if (aiTurn == black || aiTurn == white) // �µ���Ϸǰ���������
		{
			chess_record.clear();
			for(int i=0;i<GRID_NUM;i++)
				for (int j = 0; j < GRID_NUM; j++)
				{
					chessBoard[i][j] = blank;
					statusBoard[i][j] = 0;
				}
		}
		else // ������Ϸ����
		{
			break;
		}
	}

	return 0;
}

int new_game(int aiTurn)
{
	turnNum = 1;
	if (aiTurn == black)
	{
		cout << "AI����" << endl;
		chessBoard[8][8] = black;
		chess_record.push_back(make_tuple(black, 8, 8));
		regNeighbor(8, 8);
		turnNum++;
	}

	print();

	while (1)
	{
		if ((turnNum % 2) == (aiTurn % 2))
		{
			
			int temp = iterationDeepening(aiTurn); // AI����
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
			input(aiTurn); // �������
		}
		print();

		if (gameover())
		{
			if ((turnNum % 2) == (aiTurn % 2))
				cout << "AI��ʤ" << endl;
			else
				cout << "�������ʤ��" << endl;

			cout << "����: newblack  �µĶԾ֣���������" << endl;
			cout << "����: newwhite  �µĶԾ֣����Ժ���" << endl;
			cout << "����: regret    ����һ��" << endl;
			cout << "����: replay    ��ʼ����" << endl;

			while (1)
			{
				string temp;
				getline(cin, temp);
				int game_end = -1;
				if (temp == "newblack")
				{
					cin.clear();
					return black;
				}
				else if (temp == "newwhite")
				{
					cin.clear();
					return white;
				}
				else if (temp == "regret") // ����
				{
					auto last_ai_chess = chess_record.back();
					chess_record.pop_back();
					auto last_player_chess = chess_record.back();
					chess_record.pop_back();
					int i = get<1>(last_ai_chess);
					int j = get<2>(last_ai_chess);
					chessBoard[i][j] = blank;
					i = get<1>(last_player_chess);
					j = get<2>(last_player_chess);
					chessBoard[i][j] = blank;
					cout << "����һ��" << endl;

					if ((turnNum % 2) == (aiTurn % 2))
						turnNum -= 2;
					else
						turnNum -= 1;

					print();
					break;
				}
				else if (temp == "replay")
				{
					replay();
					cout << "���̽���\n" << endl;
					cout << "����: newblack  �µĶԾ֣���������" << endl;
					cout << "����: newwhite  �µĶԾ֣����Ժ���" << endl;
					cout << "����: regret    ����һ��" << endl;
					cout << "����: replay    ��ʼ����" << endl;
				}
				else
				{
					cout << "���벻�Ϸ�������������" << endl;
				}
			}
		}
		turnNum++;
	}

	return 0;
}

void replay()
{

	int chess_number = chess_record.size();
	int current_number = 0;

	vector<tuple<int, int, int>> chess_show;

	for (int i = 0; i < GRID_NUM; i++)
		for (int j = 0; j < GRID_NUM; j++)
		{
			chessBoard[i][j] = blank;
		}

	print();
	cout << "���Ҽ�ͷ�л�1�������¼�ͷ�л�5��������q���˳�����" << endl;

	while (1)
	{
		int arrow = getch();
		if (arrow == 75) // ��
		{
			if (current_number > 0)
			{
				current_number--;
				auto sub_chess = chess_show.back();
				int i = get<1>(sub_chess);
				int j = get<2>(sub_chess);
				chessBoard[i][j] = blank;

				chess_show.pop_back();
			}
		}
		else if (arrow == 77) // ��
		{
			if (current_number < chess_number)
			{ 
				current_number ++;
				auto add_chess = chess_record[current_number - 1];
				int chess = get<0>(add_chess);
				int i = get<1>(add_chess);
				int j = get<2>(add_chess);
				chessBoard[i][j] = chess;

				chess_show.push_back(add_chess);
			}
		}
		else if (arrow == 72) // ��
		{
			for(int t=0;t<5;t++)
				if (current_number > 0)
				{
					current_number--;
					auto sub_chess = chess_show.back();
					int i = get<1>(sub_chess);
					int j = get<2>(sub_chess);
					chessBoard[i][j] = blank;

					chess_show.pop_back();
				}
		}
		else if (arrow == 80) // ��
		{
			for (int t = 0; t < 5; t++)
				if (current_number < chess_number)
				{
					current_number++;
					auto add_chess = chess_record[current_number - 1];
					int chess = get<0>(add_chess);
					int i = get<1>(add_chess);
					int j = get<2>(add_chess);
					chessBoard[i][j] = chess;

					chess_show.push_back(add_chess);
				}
		}
		else if (arrow == 'q') // quit
		{
			return;
		}
		else
		{
			continue;
		}

		print();
		cout << "���Ҽ�ͷ�л�1�������¼�ͷ�л�5��������q���˳�����" << endl;
	}

}
