#include "define.h"
#include "interaction.h"
#include "searchmove.h"

vector<tuple<int, int, int>> chess_record;

void input(int player)
{
	string temp;
	int i = 0, j = 0;
	bool valid = false;
	cout << "请您走棋" << endl;
	while (!valid)
	{
		cin.clear();
		getline(cin, temp);
		// cout << temp;
		int len = temp.size();
		auto pos = temp.find(' ');
		if (temp == "regret") // 悔棋
		{
			if (chess_record.size() > 1)
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
				turnNum--;
				return;
			}
			else
			{
				cout << "不可悔棋" << endl;
				turnNum--;
				return;
			}
		}
		if (pos != 4)
		{
			cout << "输入不合法，请重新输入" << endl;
			continue;
		}
		if (temp.substr(0, pos) != "move")
		{
			cout << "输入不合法，请重新输入" << endl;
			continue;
		}
		temp.erase(0, pos + 1);
		pos = temp.find(' ');
		if (pos == string::npos)
		{
			cout << "输入不合法，请重新输入" << endl;
			continue;
		}

		try
		{
			i = stoi(temp.substr(0, pos));
			temp.erase(0, pos + 1);
			j = stoi(temp);
		}
		catch (exception e)
		{
			cout << "输入不合法，请重新输入" << endl;
			continue;
		}

		if (inboard(i, j) && chessBoard[i][j] == blank)
		{
			break;
		}
		cout << "输入不合法，请重新输入" << endl;
	}

	chessBoard[i][j] = nextTurn(player);

	chess_record.push_back(make_tuple(nextTurn(player), i, j));

	regNeighbor(i, j);
}
