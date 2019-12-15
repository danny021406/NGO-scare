#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <sstream>
#include"mcts.h"
using namespace std;

string toSGFstring(int i){
	string s="aa";
	s[0] += (i/BOARDCUL);
	s[1] += (i%BOARDCUL);
	return s;
}

int GTPstringtoint(string s){
	if(s[0]>='a'&&s[0]<='z')
	{
		int x=s[0]-'a';
		if(s[0]>'i')x--;
		int y=s[1]-'1';
		return x*BOARDCUL+y;
	}else
	{
		int x=s[0]-'A';
		if(s[0]>'I')x--;
		int y=s[1]-'1';
		return x*BOARDCUL+y;
	}
	
}
string inttoGTPstring(int i){
	string s = "A1";
    s[0]+= i / 9;
    if(s[0]>='I')s[0]++;
    s[1]+= i % 9;
    return s;
}
mcts tree;

int main(int argc, char** argv){
	int i,k;
	// int simulationCnt=50000;
	double TIME;
	string s,c,p;
	TIME=10000;
	if (argc == 2){
		istringstream (string(argv[1])) >> TIME;
		cerr << "TIME: " << TIME << endl;
	}
	bool color;
	board b;
	tree.clear();
	b.clear();
	srand(time(NULL)) ;
	vector<float> policy;
	float value;
    
	while(cin>>s){
		if(s=="play"||s=="p"){
			cin>>c>>p;
			if(c[0]=='b' || c[0]=='B')color=0;
			else color=1;
            i = GTPstringtoint(p);
			b.update( i/9 +1, i%9 +1,color,1 );
			cout<<"="<<endl<<endl;
		}
        else if(s[0]=='g' || s == "reg_genmove"){
			bool j,f=false;
			int START,END;
			cin>>c;
			if(c[0]=='b' || c[0]=='B')color=0;
			else color=1;

			tree.reset(b, !color);
			for(i=0;i<81;i++){
				if(b.check(i,color)){
					f=true;
					break;
				}
			}
			if(!f){
                cerr<<"pp"<<endl;
				cout<<"=resign"<<endl<<endl;
				continue;
			}
			START = END = clock();
			// while(simulationFinishedCnt < simulationCnt)
			while(END-START<TIME){
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				tree.run();
				END=clock();
			}
			k= tree.root -> getbestmove();
			node* tmp = tree.root -> child_ptr;
			int best_move = (tmp+k)->place;
			tree.root ->show_child();
			if(s != "reg_genmove"){
		        // if(b.check((int)best_move, color))cerr<<"wrong move  "<<endl;
			    b.update( best_move/9 +1, best_move%9 +1,color,1 );
            }
			cout<<"="<<inttoGTPstring(best_move)<<endl<<endl;
            b.show();
			tree.clear();

		}
		else if(s[0]=='c'){
			b.clear();
			cout<<"="<<endl<<endl;
		}
		else if (s == "value"){
			cout << value << endl;
		}
		else if (s == "protocol_version"){
			cout<<"=2\n\n";
		}
		else if (s == "version"){
			cout<<"=666\n\n";
		}
		else if (s == "list_commands"){
			cout<<"=\n\n";
		}
		else if(s== "name"){
			cout<<"=dannyyyyy" << "\n\n";
		}
        else if(s == "boardsize"){
			cin>>s;
			cout<<"="<<endl<<endl;
		}
		else{
			cout<<"="<<endl<<endl;
		}
	}
}