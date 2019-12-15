#ifndef NODE_H
#define NODE_H
#include "boardtest.h"
#include <math.h>

const double UCB_WEIGHT = 0.25;

class node{
public:
	char place;
	bool color;
	char child[BOARDSSIZE+1];
	int csize;
	node* child_ptr;
	double ravecount;
	double ravemean;
	double count;
	double mean; // win rate
    void show_child();
    void initnode(int i,bool j);
    void update(double score);
	void update_rave(double score);
    int getbestmove();
    float show_inf(int child);
    void expansion(board &b, map<int , vector<node*> > &bpath, map<int , vector<node*> > &wpath);
    string inttoGTPstring(int i);
	node();
	~node();
};
#endif //NODE_H
