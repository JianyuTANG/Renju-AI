#pragma once
#include "interaction.h"

void input(bool isBlack)
{
	string temp;
	int i, j;
	bool valid = false;
	fflush(stdin);
	getline(cin, temp);
	while (!valid)
	{
		cin.clear();
		getline(cin, temp);
		// cout << temp;
		int len = temp.size();
		auto pos = temp.find(' ');
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
	if (isBlack)
		chessBoard[i][j] = white;
	else
		chessBoard[i][j] = black;
}
