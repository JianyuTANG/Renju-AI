#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
#include "searchmove.h"
#include <tuple>
#include <chrono>

bool checkNeighbor(int x, int y)
{
	for (int i = x - 2; i <= x + 2; i++)
	{
		if (i < 1 || i > 14)
			continue;
		for (int j = y - 2; j <= y + 2; j++)
		{
			if (j < 1 || j > 14)
				continue;
			if (chessBoard[i][j])
				return true;
		}
	}
	return false;
}

void regNeighbor(int x, int y)
{
	for (int i = x - 2; i <= x + 2; i++)
	{
		if (i < 1 || i > 14)
			continue;
		for (int j = y - 2; j <= y + 2; j++)
		{
			if (j < 1 || j > 14)
				continue;
			if (!statusBoard[i][j])
				statusBoard[i][j] = turnNum;
		}
	}
}

void regNeighbor2(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (i < 1 || i > 14)
			continue;
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j < 1 || j > 14)
				continue;
			if (!statusBoard[i][j])
				statusBoard[i][j] = turnNum;
		}
	}
}

void unregNeighbor(int x, int y)
{
	for (int i = x - 2; i <= x + 2; i++)
	{
		if (i < 1 || i > 14)
			continue;
		for (int j = y - 2; j <= y + 2; j++)
		{
			if (j < 1 || j > 14)
				continue;
			if (statusBoard[i][j] == turnNum)
				statusBoard[i][j] = 0;
		}
	}
}

void unregNeighbor2(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (i < 1 || i > 14)
			continue;
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (j < 1 || j > 14)
				continue;
			if (statusBoard[i][j] == turnNum)
				statusBoard[i][j] = 0;
		}
	}
}

tuple<int, int, int> maxValue(int player, int alpha, int beta, int depth)
{
	if (gameover())
		return make_tuple(INT32_MIN, 0, 0);
	if (depth == 0)
	{
		int score = evaluate();
		if (player == black)
			score = score;
		else
			score = -score;
		return make_tuple(score, 0, 0);
	}

	int v = INT32_MIN;
	int ai = 0, aj = 0;
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 14; j++)
		{
			if (chessBoard[i][j] == blank && statusBoard[i][j])
			{
				chessBoard[i][j] = player;
				regNeighbor2(i, j);
				turnNum++;
				auto temp = minValue(nextTurn(player), alpha, beta, depth - 1);
				int val = get<0>(temp);
				if (val > v)
				{
					v = val;
					ai = i;
					aj = j;
					if (v >= beta)
					{
						chessBoard[i][j] = blank;
						turnNum--;
						unregNeighbor2(i, j);
						return make_tuple(v, ai, aj);
					}
					if (v > alpha)
					{
						alpha = v;
					}
				}
				chessBoard[i][j] = blank;
				turnNum--;
				unregNeighbor2(i, j);
			}
		}
	}
	return make_tuple(v, ai, aj);
}

tuple<int, int, int> minValue(int player, int alpha, int beta, int depth)
{
	if (gameover())
		return make_tuple(INT32_MAX, 0, 0);
	if (depth == 0)
	{
		int score = evaluate();
		if (player == black)
			score = score;
		else
			score = -score;
		return make_tuple(score, 0, 0);
	}
		

	int v = INT32_MAX;
	int ai = 0, aj = 0;
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 14; j++)
		{
			if (chessBoard[i][j] == blank && checkNeighbor(i, j))
			{
				chessBoard[i][j] = player;
				regNeighbor2(i, j);
				turnNum++;
				auto temp = maxValue(nextTurn(player), alpha, beta, depth - 1);
				int val = get<0>(temp);
				if (val < v)
				{
					v = val;
					ai = i;
					aj = j;
					if (v <= alpha)
					{
						chessBoard[i][j] = blank;
						turnNum--;
						unregNeighbor2(i, j);
						return make_tuple(v, ai, aj);
					}
					if (v < beta)
					{
						beta = v;
					}
				}
				chessBoard[i][j] = blank;
				turnNum--;
				unregNeighbor2(i, j);
			}
		}
	}
	return make_tuple(v, ai, aj);
}

int iterationDeepening(int player)
{
	tuple<int, int, int> ans;
	for (int depth = 1; depth < DEPTH; depth++)
	{
		auto start = std::chrono::steady_clock::now();

		// int alpha = INT32_MIN, beta = INT32_MAX;
		ans = maxValue(player, INT32_MIN, INT32_MAX, depth);

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration<float, std::milli>(end - start);
		if (duration.count() > 100)
		{
			cout << "timeout: level " << depth << endl;
			break;
		}
	}
	int i = get<1>(ans), j = get<2>(ans), score = get<0>(ans);
	if (i == 0 && j == 0)
	{
		cout << score << endl;
	}
	if (score == INT32_MIN)
	{
		return 1;
	}
	else if (score == INT32_MAX)
	{
		return 2;
	}
	
	chessBoard[i][j] = player;
	regNeighbor(i, j);
	//turnNum++;
	return 0;
}

int searchMove() //ËÑË÷º¯ÊýÖ÷Ìå
{

	return 0;
}
