#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//ËÑË÷ºËÐÄ

#define DEPTH 6
#define moveMAX 30

struct LINE {
	int cmove;            // depth
	int argmove[moveMAX]; // route
};

int searchMove();//ËÑË÷ºËÐÄ
tuple<int, int, int> maxValue(int player, int alpha, int beta, int depth, LINE* mLine, LINE* cLine);
tuple<int, int, int> minValue(int player, int alpha, int beta, int depth, LINE* mLine, LINE* cLine);
int iterationDeepening(int player);

void regNeighbor(int x, int y);

#endif
