#ifndef MCTS_H
#define MCTS_H
#include "node.h"
#include <math.h>
class mcts{
public:
	int selectlist[BOARDSSIZE];
	int slsize;
	node* root;
	board root_board;
    mcts();
    ~mcts();
    vector<node*> path;
    map<int , vector<node*> > bpath;
    map<int , vector<node*> > wpath;

    double getscore( node* nodeptr, int child);
    node* getbestchild(node* nodeptr);
    void find_best_node(board &b);
    void update(double result);
    void run();
    void reset(board &b, int c);
    void clear();
    string inttostring(int i);
    string inttoGTPstring(int i);
};


#endif // MCTS_H

double mcts::getscore( node* node_ptr, int child){
	node *child_node = (node_ptr->child_ptr)+child;
	double &count = child_node->count ; 
	double &ravecount = child_node->ravecount ; 
	double ret = child_node->mean*count + child_node->ravemean*ravecount +  sqrt( log(node_ptr->count)  )* UCB_WEIGHT;
	return ret/ (count + ravecount);
}

node* mcts::getbestchild(node* node_ptr){
	if(node_ptr->csize == 0)return NULL;
	int i,ret=0;
	double max,score,score_delta;
	max=getscore(node_ptr,0);
	selectlist[0]=0;
	slsize = 1;
	for(i=1;i<(node_ptr->csize);i++){

		score = getscore(node_ptr,i);
		score_delta = score-max;
		if( score_delta > -0.0001 ){
		
			if(score_delta > 0.0001){
				selectlist[0]=i;
				slsize = 1;
				max = score;
			}else{
				selectlist[slsize]=i;
				slsize ++ ;
			}
		}
	}
	ret = selectlist[ rand() % slsize ];
	return (node_ptr->child_ptr +ret);
}

void mcts::find_best_node(board &b){ // init

	node* node_ptr = root;
	path.clear();
	path.push_back(node_ptr);
	while(node_ptr->child_ptr != NULL && node_ptr->csize != 0){
		node_ptr = getbestchild(node_ptr);
		path.push_back(node_ptr);
		b.add(node_ptr->place,node_ptr->color);
	}
}
void mcts::update(double result){
	for(int i=0;i<path.size();i++){
		path[i]->update(result);
        if ( path[i]->color == 0 ){
            for ( auto j : bpath[path[i]->place] ) {
                j->update_rave(result);
            }
        } 
        else{
            for ( auto j : wpath[path[i]->place] ) {
                j->update_rave(result);
            }
        }
	}
}
void mcts::run(){
	board b;
	double result;
	b =root_board;
	find_best_node(b);
	node &last=(*(path.back()));
	node *node_ptr;
	b.set_air();
	if(last.csize==0 && last.count > 0 ){ // > 0 means have expanded itself
		last.expansion(b, bpath, wpath);
	}

	result=b.simulate_v(last.color);
	update(result);
}
void mcts::reset(board &b, int c){
	root_board=b;
	root = new node;

    bpath.clear();
    wpath.clear();
    // init map's vector
    for ( int i=0;i<81;i++ ) {
        if ( root_board.check(i,0) ) {
            vector<node*> tmp;
            bpath[i] = tmp;
        }
        if ( root_board.check(i,1) ) {
            vector<node*> tmp;
            wpath[i] = tmp;
        }
    }
	root->initnode(0, c);
	root-> expansion(b, bpath, wpath);
}

void mcts::clear(){
	if( root != NULL)delete root;
}

mcts::mcts(){
	;
}

mcts::~mcts(){
	;
}