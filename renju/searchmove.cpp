#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "printchessboard.h"
#include "searchmove.h"
#include <tuple>
#include <chrono>

tuple<int, int, int> maxValue(int player, int& alpha, int& beta, int depth)
{
	if (gameover())
		return make_tuple(INT32_MIN, 0, 0);
	if (depth == 0)
		return make_tuple(evaluate(), 0, 0);

	int v = INT32_MIN;
	int ai, aj;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (chessBoard[i][j] == blank)
			{
				chessBoard[i][j] = player;
				auto temp = minValue(nextTurn(player), alpha, beta, depth - 1);
				int val = get<0>(temp);
				if (val > v)
				{
					v = val;
					ai = i;
					aj = j;
					if (v >= beta)
					{
						return make_tuple(v, ai, aj);
					}
					if (v > alpha)
					{
						alpha = v;
					}
				}
				chessBoard[i][j] = blank;
			}
		}
	}
	return make_tuple(v, ai, aj);
}

tuple<int, int, int> minValue(int player, int& alpha, int& beta, int depth)
{
	if (gameover())
		return make_tuple(INT32_MAX, 0, 0);
	if (depth == 0)
		return make_tuple(evaluate(), 0, 0);

	int v = INT32_MAX;
	int ai, aj;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (chessBoard[i][j] == blank)
			{
				chessBoard[i][j] = player;
				auto temp = maxValue(nextTurn(player), alpha, beta, depth - 1);
				int val = get<0>(temp);
				if (val < v)
				{
					v = val;
					ai = i;
					aj = j;
					if (v <= alpha)
					{
						return make_tuple(v, ai, aj);
					}
					if (v < beta)
					{
						beta = v;
					}
				}
				chessBoard[i][j] = blank;
			}
		}
	}
	return make_tuple(v, ai, aj);
}

void iterationDeepening(int player)
{
	tuple<int, int, int> ans;
	for (int depth = 1; depth < 30; depth++)
	{
		auto start = std::chrono::steady_clock::now();

		int alpha = INT32_MIN, beta = INT32_MAX;
		ans = maxValue(player, alpha, beta, depth);

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration<float, std::milli>(end - start);
		if (duration.count() > 1000)
		{
			break;
		}
	}
	int i = get<1>(ans), j = get<2>(ans);
	chessBoard[i][j] = player;
}

int searchMove() //ËÑË÷º¯ÊýÖ÷Ìå
{

	return 0;
}
