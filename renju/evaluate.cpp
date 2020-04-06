#include "define.h"
#include "evaluate.h"
#include "time.h"

int T[] = { 0,0,0,0,2,1,1,1,1,1,1,0,0 };

const int Live[] = { 0,1,40,100,1000,10000,10000,10000,10000,10000 };
const int Dead[] = { 0,1,10,30,80,10000,10000,10000,10000,10000 };
//#define

int evaluate()//估值算法，返回估值
{
	// 1 denotes black, 2 denotes white and 0 denotes empty site.
	int testBoard[15][15] = {   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
	int black_score = 0;
	int white_score = 0;
	for (int row = 0; row < GRID_NUM; row++) // 检查行
	{
		black_score += evaluate_line(testBoard[row], GRID_NUM, black);
		white_score += evaluate_line(testBoard[row], GRID_NUM, white);
	}
	for (int col = 0; col < GRID_NUM; col++) // 检查列
	{
		int line[GRID_NUM];
		for (int i = 0; i < GRID_NUM; i++)
		{
			line[i] = testBoard[i][col];
		}
		black_score += evaluate_line(line, GRID_NUM, black);
		white_score += evaluate_line(line, GRID_NUM, white);
	}
	for (int diag = 0; diag < 2*GRID_NUM-1; diag++) // 左下到右上的对角线
	{
		int line[GRID_NUM];
		int len_line = -1;
		if (diag < GRID_NUM)
		{
			len_line = 1 + diag;
			for (int i = 0; i < len_line; i++)
			{
				line[i] = testBoard[len_line - 1 - i][i];
			}
		}
		else
		{
			len_line = 2*GRID_NUM -1 - diag;
			for (int i = 0; i < len_line; i++)
			{
				line[i] = testBoard[GRID_NUM - 1 - i][diag - GRID_NUM + 1 + i];
			}
		}
		black_score += evaluate_line(line, len_line, black);
		white_score += evaluate_line(line, len_line, white);
	}
	for (int diag = 0; diag < 2 * GRID_NUM - 1; diag++) // 左上到右下的对角线
	{
		int line[GRID_NUM];
		int len_line = -1;
		if (diag < GRID_NUM)
		{
			len_line = 1 + diag;
			for (int i = 0; i < len_line; i++)
			{
				line[i] = testBoard[GRID_NUM - len_line + i][i];
			}
		}
		else
		{
			len_line = 2 * GRID_NUM - 1 - diag;
			for (int i = 0; i < len_line; i++)
			{
				line[i] = testBoard[i][diag - GRID_NUM + 1 + i];
			}
		}
		black_score += evaluate_line(line, len_line, black);
		white_score += evaluate_line(line, len_line, white);
	}
	
	//cout << "black score: " << black_score << " white score: " << white_score << endl;

	return  0;
}

int evaluate_line(int* line, int length, int chess)
{
	int score = 0;

	// The form of a consecutive chesses is based on itself and two neibours of it.

	for (int h = 0; h < length; h++) // 头棋子
	{
		if (line[h] == chess) // score of chess
		{
			//5
			if (line[h + 1] == chess && line[h + 2] == chess && line[h + 3] == chess && line[h + 4] == chess)
			{
				score += 10000000;
				h = h + 5;
				continue;
			}

			// 活4
			if (h - 1 >= 0 && line[h - 1] == blank && line[h + 1] == chess && line[h + 2] == chess && line[h + 3] == chess && h + 4 < length && line[h + 4] == blank)
			{
				score += 300000;
				h = h + 4;
				continue;
			}

			//死4A
			if (
				line[h + 1] == chess && line[h + 2] == chess && line[h + 3] == chess &&
				((h - 1 >= 0 && line[h - 1] == blank) + (h + 4 < length && line[h + 4] == blank) == 1)
				)
			{
				score += 2500;
				h = h + 4;
				continue;
			}

			//死4B/C
			if (
				(h+4<length && line[h + 4] == chess)
				&& ((line[h + 1] == chess) + (line[h + 2] == chess) + (line[h + 3] == chess) == 2)
				&& ((line[h + 1] == blank) + (line[h + 2] == blank) + (line[h + 3] == blank) == 1)
				)
			{
				score += 2800;
				h = h + 5;
				continue;
			}

			//活3
			if (h - 1 >= 0 && line[h - 1] == blank && line[h + 1] == chess && line[h + 2] == chess && h + 3 < length && line[h + 3] == blank)
				{
					score += 3000;
					h = h + 3;
					continue;
				}

			//死3A
			if (
				(line[h + 1] == chess && line[h + 2] == chess)
				&& ((h - 1 >= 0 && line[h - 1] == blank) + (h + 3 < length && line[h + 3] == blank) == 1)
				&& ((h - 1 >= 0 && line[h - 1] == blank && h - 2 >= 0 && line[h - 2] == blank) || (h + 3 < length && line[h + 3] == blank && h + 4 < length && line[h + 4] == blank))
				)
			{
				score += 500;
				h = h + 3;
				continue;
			}

			//死3B
			if (
				(h + 3<length && line[h + 3] == chess)
				&& ((line[h + 1] == chess) + (line[h + 2] == chess) == 1)
				&& ((line[h + 1] == blank) + (line[h + 2] == blank) == 1)
				&& ((h - 1 >= 0 && line[h - 1] == blank) || (h + 4 < length && line[h + 4] == blank) )
				)
			{
				score += 800;
				h = h + 4;
				continue;
			}

			//死3C
			if (
				(h+4<length && line[h + 4] == chess)
				&& ((line[h + 1] == blank) + (line[h + 2] == blank) + (line[h + 3] == blank) == 2)
				&& ((line[h + 1] == chess) + (line[h + 2] == chess) + (line[h + 3] == chess) == 1)
				)
			{
				score += 600;
				h = h + 5;
				continue;
			}

			//死3D
			if (
				(h+4<length && line[h + 4] == chess && line[h + 2] == chess && line[h + 1] == blank && line[h + 3] == blank)
				)
			{
				score += 550;
				h = h + 5;
				continue;
			}

			//活2
			if (
				h-3>=0 && line[h-3] == blank && line[h-2] == blank && line[h-1] == blank && h+4<length && line[h+1] == chess && line[h + 2] == blank && line[h + 3] == blank && line[h + 4] == blank
				)
			{
				score += 650;
				h = h + 4;
				continue;
			}

			//死2A
			if (
				h - 3 >= 0 && (line[h -3] == blank && line[h-2] == blank && line[h-1] == blank && line[h + 1] == chess && line[h + 2] != blank)
				|| (h - 1 >= 0 && line[h-1] != blank && h+4<length && line[h + 1] == chess && line[h + 2] == blank && line[h + 3] == blank && line[h + 4] == blank)
				)
			{
				score += 150;
				h = h + 2;
				continue;
			}

			//死2B
			if (
				h - 2 >= 0 && line[h-2] == blank && line[h-1] == blank && h+4<length && line[h + 1] == blank && line[h + 2] == chess && line[h + 3] == blank && line[h + 4] == blank
				)
			{
				score += 250;
				h = h + 4;
				continue;
			}

			//死2C
			if (
				h - 1 >= 0 && line[h -1] == blank && h+4<length && line[h + 1] == blank && line[h + 2] == blank && line[h + 3] == chess && line[h + 4] == blank
				)
			{
				score += 200;
				h = h + 4;
				continue;
			}

		}
	}

	return score;
}


//由于五子棋搜索分支庞大，通常无法直接搜索到胜负终局，当搜索到一定深度时需要根据局面返回搜索结果。
//参考资料：
//张明亮, 吴俊, 李凡长. 五子棋机器博弈系统评估函数的设计[J]. 计算机应用, 2012, 32(07):1969-1972.
//裴博文. 五子棋人工智能权重估值算法[J]. 电脑编程技巧与维护, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html