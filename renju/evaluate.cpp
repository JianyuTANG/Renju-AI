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
								{0, 0, 0, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 2, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
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
			int t = h + 1; // β����
			int space = 0; // empty inside
			int loc_space = -1;
			//cout << "length:"<<length << endl;
			for (t=h+1; t < length; t++)
			{
				//cout<<"now t is:"<<t<<endl;
				if (line[t] == chess)
				{ 
					continue;
				}
				else if (line[t - 1] == chess && line[t] == blank && t+1<length && line[t + 1] == chess)
				{
					space++;
					loc_space = t;
				}
				else
				{
					break;
				}
			}
			t--;
			//cout << t << endl;
			int len_chess = t - h + 1 - space;
			//cout << "len_chess:" << len_chess<<" h:"<<h<<" t:"<<t << "space"<<space<<endl;
			int life = (h - 1 >= 0 && line[h - 1] == blank) +(t + 1 < length && line[t + 1] == blank);
			//cout <<"life:" <<life << endl;
			if ( life==2 ) //����Ϊ�գ�������
			{
				if (len_chess <= 3)
					score += Live[len_chess];
				else if (len_chess >= 4)
				{
					if (t - h + 1 == len_chess) // ������
						score += Live[len_chess];
					else // ��������
					{
						score += Live[3]; //��ɻ�3
					}
				}
			}
			else if (life == 1) // һ��Ϊ�գ�������
			{
				if (len_chess <= 3)
					score += Dead[len_chess];
				else if (len_chess >= 4)
				{
					if (t - h + 1 == len_chess) // ������
						score += Dead[len_chess];
					else // ��������
					{
						score += Dead[4]; //�����4
					}
				}
			}

			//������һ������
			if (loc_space == -1)
				h = t + 1;
			else
				h = loc_space;
		}
	}

	return score;
}


















//����������������֧�Ӵ�ͨ���޷�ֱ��������ʤ���վ֣���������һ�����ʱ��Ҫ���ݾ��淵�����������
//�ο����ϣ�
//������, �⿡, ���. �������������ϵͳ�������������[J]. �����Ӧ��, 2012, 32(07):1969-1972.
//�Ჩ��. �������˹�����Ȩ�ع�ֵ�㷨[J]. ���Ա�̼�����ά��, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html