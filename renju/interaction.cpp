#pragma once
#include "interaction.h"

void input(bool isBlack)
{
	string temp;
	int i, j;
	bool valid = false;
	fflush(stdin);
	char a;
	cin >> a;
	while (!valid)
	{
		cin.clear();
		getline(cin, temp);
		printf("666");
		int len = temp.size();
		auto pos = temp.find(' ');
		if (pos != 4)
		{
			cout << "���벻�Ϸ�������������1" << endl;
			continue;
		}
		if (temp.substr(0, pos) != "move")
		{
			cout << "���벻�Ϸ�������������" << endl;
			continue;
		}
		temp.erase(0, pos + 1);
		pos = temp.find(' ');
		if (pos == string::npos)
		{
			cout << "���벻�Ϸ�������������" << endl;
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
			cout << "���벻�Ϸ�������������" << endl;
			continue;
		}

		if (inboard(i, j) && chessBoard[i][j] == blank)
		{
			break;
		}
		cout << "���벻�Ϸ�������������" << endl;
	}
	if (isBlack)
		chessBoard[i][j] = white;
	else
		chessBoard[i][j] = black;
}