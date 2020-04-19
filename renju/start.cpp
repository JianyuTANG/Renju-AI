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
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	cout << "输入: move x y  表示落子点" << endl;
	cout << "输入: regret    悔棋一手" << endl;
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
			cout << "输入不合法，请重新输入" << endl;
		}
	}

	string temp;
	getline(cin, temp);
	while (1)
	{
		
		if( aiTurn == black)
			cout << "电脑先手，您后手" << endl;
		else
			cout << "电脑后手，您先手" << endl;
		aiTurn = new_game(aiTurn); // 进行一场游戏

		if (aiTurn == black || aiTurn == white) // 新的游戏前，清空棋盘
		{
			chess_record.clear();
			for(int i=0;i<GRID_NUM;i++)
				for (int j = 0; j < GRID_NUM; j++)
				{
					chessBoard[i][j] = blank;
					statusBoard[i][j] = 0;
				}
		}
		else // 否则游戏结束
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
		cout << "AI走棋" << endl;
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
			
			int temp = iterationDeepening(aiTurn); // AI行棋
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
			input(aiTurn); // 玩家行棋
		}
		print();

		if (gameover())
		{
			if ((turnNum % 2) == (aiTurn % 2))
				cout << "AI获胜" << endl;
			else
				cout << "您获得了胜利" << endl;

			cout << "输入: newblack  新的对局，电脑先手" << endl;
			cout << "输入: newwhite  新的对局，电脑后手" << endl;
			cout << "输入: regret    悔棋一手" << endl;
			cout << "输入: replay    开始复盘" << endl;

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
				else if (temp == "regret") // 悔棋
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
					cout << "悔棋一步" << endl;

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
					cout << "复盘结束\n" << endl;
					cout << "输入: newblack  新的对局，电脑先手" << endl;
					cout << "输入: newwhite  新的对局，电脑后手" << endl;
					cout << "输入: regret    悔棋一手" << endl;
					cout << "输入: replay    开始复盘" << endl;
				}
				else
				{
					cout << "输入不合法，请重新输入" << endl;
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
	cout << "左右箭头切换1步，上下箭头切换5步，按‘q’退出复盘" << endl;

	while (1)
	{
		int arrow = getch();
		if (arrow == 75) // 左
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
		else if (arrow == 77) // 右
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
		else if (arrow == 72) // 上
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
		else if (arrow == 80) // 下
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
		cout << "左右箭头切换1步，上下箭头切换5步，按‘q’退出复盘" << endl;
	}

}
