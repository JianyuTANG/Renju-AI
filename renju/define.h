
#ifndef _DEFINE_
#define _DEFINE_
//全局变量定义

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

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define inf 1000000		
#define inboard(a,b) (a>0 && a<=14 && b>0 && b<=14)		//用于检验招法是否在棋盘上
#define nextTurn(player) (3 - player)


#define GRID_NUM 15	//棋盘规模	
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
extern int statusBoard[GRID_NUM][GRID_NUM]; //status
extern int turnNum;
extern vector<tuple<int,int,int>> chess_record; // 依次落子的顺序
//bool gameover(struct point node, int player); //判断是否游戏结束
bool gameover(); //判断是否游戏结束
#endif


