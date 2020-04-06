#include "define.h"
bool gameover()//ÅĞ¶ÏÊÇ·ñÓÎÏ·½áÊø
{
	// check rows
	for (int i = 1; i <= 15; i++)
	{
		int last = chessBoard[i][1];
		int cnt = 0;
		if (last != blank)
			cnt++;
		for (int j = 2; j <= 15; j++)
		{
			if (last == chessBoard[i][j] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i][j];
				cnt = 1;
			}
		}
	}

	// check columns
	for (int j = 1; j <= 15; j++)
	{
		int last = chessBoard[1][j];
		int cnt = 0;
		if (last != blank)
			cnt++;
		for (int i = 2; i <= 15; i++)
		{
			if (last == chessBoard[i][j] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i][j];
				cnt = 1;
			}
		}
	}

	// check diagnals(left->right)
	for (int i = 1; i <= 11; i++)
	{
		int last = -1;
		int cnt = 0;
		//if (last != blank)
		//	cnt++;
		for (int j = 1; j <= 16 - i; j++)
		{
			if (last == chessBoard[i + j - 1][j] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i + j - 1][j];
				cnt = 1;
			}
		}
	}
	for (int j = 2; j <= 11; j++)
	{
		int last = -1;
		int cnt = 0;
		/*int last = chessBoard[1][j];
		int cnt = 0;
		if (last != blank)
			cnt++;*/
		for (int i = 1; i <= 16 - j; i++)
		{
			if (last == chessBoard[i][i + j - 1] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i][i + j - 1];
				cnt = 1;
			}
		}
	}

	//check diagnals(right to left)
	for (int i = 1; i <= 11; i++)
	{
		int last = -1;
		int cnt = 0;
		/*int last = chessBoard[i][15];
		int cnt = 0;
		if (last != blank)
			cnt++;*/
		for (int j = 15; j >= i; j--)
		{
			if (last == chessBoard[i - j + 15][j] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i - j + 15][j];
				cnt = 1;
			}
		}
	}
	for (int j = 5; j < 15; j++)
	{
		int last = -1;
		int cnt = 0;
		/*int last = chessBoard[1][j];
		int cnt = 0;
		if (last != blank)
			cnt++;*/
		for (int i = 1; i <= j; i++)
		{
			if (last == chessBoard[i][j - i + 1] && last != blank)
			{
				cnt++;
				if (cnt == 5)
					return true;
			}
			else
			{
				last = chessBoard[i][j - i + 1];
				cnt = 1;
			}
		}
	}

	return false;
}
