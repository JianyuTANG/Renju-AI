#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ

int searchMove();//ËÑË÷ºËÐÄ
tuple<int, int, int> maxValue(int player, int& alpha, int& beta, int depth);
tuple<int, int, int> minValue(int player, int& alpha, int& beta, int depth);
int iterationDeepening(int player);

#endif
