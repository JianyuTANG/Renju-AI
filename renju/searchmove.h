#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//��������

#define DEPTH 6

int searchMove();//��������
tuple<int, int, int> maxValue(int player, int& alpha, int& beta, int depth);
tuple<int, int, int> minValue(int player, int& alpha, int& beta, int depth);
int iterationDeepening(int player);

void regNeighbor(int x, int y);

#endif
