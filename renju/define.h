
#ifndef _DEFINE_
#define _DEFINE_
//ȫ�ֱ�������

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <tuple>
using namespace std;

#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=14 && b>0 && b<=14)		//���ڼ����з��Ƿ���������
#define nextTurn(player) (3 - player)


#define GRID_NUM 15	//���̹�ģ	
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
extern int statusBoard[GRID_NUM][GRID_NUM]; //status
extern int turnNum;
extern vector<tuple<int,int,int>> chess_record; // �������ӵ�˳��
//bool gameover(struct point node, int player); //�ж��Ƿ���Ϸ����
bool gameover(); //�ж��Ƿ���Ϸ����
#endif


