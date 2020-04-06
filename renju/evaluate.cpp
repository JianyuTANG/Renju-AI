#include "define.h"
#include "evaluate.h"
#include "time.h"

int T[] = { 0,0,0,0,2,1,1,1,1,1,1,0,0 };

const int Live[] = { 0,1,40,100,1000,10000,10000,10000,10000,10000 };
const int Dead[] = { 0,1,10,30,80,10000,10000,10000,10000,10000 };
//#define

int evaluate()//��ֵ�㷨�����ع�ֵ
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
	for (int row = 0; row < GRID_NUM; row++) // �����
	{
		black_score += evaluate_line(testBoard[row], GRID_NUM, black);
		white_score += evaluate_line(testBoard[row], GRID_NUM, white);
	}
	for (int col = 0; col < GRID_NUM; col++) // �����
	{
		int line[GRID_NUM];
		for (int i = 0; i < GRID_NUM; i++)
		{
			line[i] = testBoard[i][col];
		}
		black_score += evaluate_line(line, GRID_NUM, black);
		white_score += evaluate_line(line, GRID_NUM, white);
	}
	for (int diag = 0; diag < 2*GRID_NUM-1; diag++) // ���µ����ϵĶԽ���
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
	for (int diag = 0; diag < 2 * GRID_NUM - 1; diag++) // ���ϵ����µĶԽ���
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

	for (int h = 0; h < length; h++) // ͷ����
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

			// ��4
			if (h - 1 >= 0 && line[h - 1] == blank && line[h + 1] == chess && line[h + 2] == chess && line[h + 3] == chess && h + 4 < length && line[h + 4] == blank)
			{
				score += 300000;
				h = h + 4;
				continue;
			}

			//��4A
			if (
				line[h + 1] == chess && line[h + 2] == chess && line[h + 3] == chess &&
				((h - 1 >= 0 && line[h - 1] == blank) + (h + 4 < length && line[h + 4] == blank) == 1)
				)
			{
				score += 2500;
				h = h + 4;
				continue;
			}

			//��4B/C
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

			//��3
			if (h - 1 >= 0 && line[h - 1] == blank && line[h + 1] == chess && line[h + 2] == chess && h + 3 < length && line[h + 3] == blank)
				{
					score += 3000;
					h = h + 3;
					continue;
				}

			//��3A
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

			//��3B
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

			//��3C
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

			//��3D
			if (
				(h+4<length && line[h + 4] == chess && line[h + 2] == chess && line[h + 1] == blank && line[h + 3] == blank)
				)
			{
				score += 550;
				h = h + 5;
				continue;
			}

			//��2
			if (
				h-3>=0 && line[h-3] == blank && line[h-2] == blank && line[h-1] == blank && h+4<length && line[h+1] == chess && line[h + 2] == blank && line[h + 3] == blank && line[h + 4] == blank
				)
			{
				score += 650;
				h = h + 4;
				continue;
			}

			//��2A
			if (
				h - 3 >= 0 && (line[h -3] == blank && line[h-2] == blank && line[h-1] == blank && line[h + 1] == chess && line[h + 2] != blank)
				|| (h - 1 >= 0 && line[h-1] != blank && h+4<length && line[h + 1] == chess && line[h + 2] == blank && line[h + 3] == blank && line[h + 4] == blank)
				)
			{
				score += 150;
				h = h + 2;
				continue;
			}

			//��2B
			if (
				h - 2 >= 0 && line[h-2] == blank && line[h-1] == blank && h+4<length && line[h + 1] == blank && line[h + 2] == chess && line[h + 3] == blank && line[h + 4] == blank
				)
			{
				score += 250;
				h = h + 4;
				continue;
			}

			//��2C
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


//����������������֧�Ӵ�ͨ���޷�ֱ��������ʤ���վ֣���������һ�����ʱ��Ҫ���ݾ��淵�����������
//�ο����ϣ�
//������, �⿡, ���. �������������ϵͳ�������������[J]. �����Ӧ��, 2012, 32(07):1969-1972.
//�Ჩ��. �������˹�����Ȩ�ع�ֵ�㷨[J]. ���Ա�̼�����ά��, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html