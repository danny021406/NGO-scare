#include "node.h"
#include <map>
#include <vector>

void node::initnode(int position,bool c){

    color=c;
    place=position;
    mean = 0.5;
    count = 0;
    csize = 0;
	ravecount = 0;
	ravemean = 0.5;
    memset(child,-1,sizeof(child));
    child_ptr=NULL;
}

void node::update(double score){
    if(score == color){
		// cerr<<"Am I a joke to u?"<<endl;
		// cerr<<"color"<<color<<endl;
        mean = (mean*count+1.00)/(count+1);
    }else{
        mean = (mean*count)/(count+1);
    }
    count+=1;
}

void node::update_rave(double score){
    if(score == color){
		// cerr<<"Am I a joke to u?"<<endl;
		// cerr<<"color"<<color<<endl;
        ravemean = (ravemean*ravecount+1.00)/(ravecount+1);
    }else{
        ravemean = (ravemean*ravecount)/(ravecount+1);
    }
    ravecount+=1;
}

void node::expansion(board &b, map<int , vector<node*> > &bpath, map<int , vector<node*> > &wpath){
	int record_check[BOARDSSIZE];
	bool c;
	c=!color;
	csize=0;
	for(int i=0;i<81;i++){
		if(b.check(i,c)){
			record_check[csize] = i;
			csize++;
		}
	}
	if(csize==0){
		return;
	}
	child_ptr = new node [csize];
	// cerr<<"expand"<<c<<endl;
	for(int i=0;i<csize;i++){
		// cerr<<record_check[i]<<" ";
		child[record_check[i]]=i;
		child_ptr[i].initnode(record_check[i],c);
		if ( c == 0 ) {
			bpath[record_check[i]].push_back(child_ptr+i);
		} else {
			wpath[record_check[i]].push_back(child_ptr+i);
		}
	}
	// cerr<<"End"<<endl;
}

int node::getbestmove(){
	int value;
	double max,tmp_count;
	max = -9999;
	value = -1;
	for(int i = 0;i<csize;i++){
		tmp_count = child_ptr[i].count;// * child_ptr[i].mean;
		if(tmp_count > max){
			max = tmp_count;
			value=i;
		}
	}
	return value;
}

void node::show_child(){
	for(int i=0;i<csize;i++){
		if(child_ptr[i].count<10)continue;
		cerr<< inttoGTPstring((int)child_ptr[i].place)<<' '<<child_ptr[i].mean<<' '<<child_ptr[i].count<<' '<<child_ptr[i].ravemean<<' '<<child_ptr[i].ravecount<<' '<<endl;
	}
}
float node::show_inf(int best){
		// cerr<<"total : "<< count -basenum <<endl<<"winrate :"<<(child_ptr[best].mean)<<"\n";
		return child_ptr[best].mean;
}

string node::inttoGTPstring(int i){
    string s = "A1";
    s[0]+= i / 9;
    if(s[0]>='I')s[0]++;
    s[1]+= i % 9;
    return s;
}

node::node(){
    
}
node::~node(){

    if(child_ptr != NULL) {delete [] child_ptr;child_ptr=NULL;}
}