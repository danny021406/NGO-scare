#include <set>
#include<iostream>
#include<map>
#include<string.h>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>

#define BOARDROW 9
#define BOARDCUL 9
#define BOARDSSIZE  81

using namespace std;

class board{
public:
    int x_tmp,y_tmp;
	int air[11][11];
	bool b[11][11];
	bool hole[11][11];
	bool doneboard[11][11];
	bool doneboard2[11][11];
    bool color;

	set<pair<int,int> > uniqset; // for not duplicate

	board(){
		clear();
	}

	void operator =(const board& b) {

		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				this->hole[i][j] = b.hole[i][j];
				this->b[i][j] = b.b[i][j];
			}
		}
	}

	void holeupdate(int x, int y, bool c) {
		doneboard[x][y] = true;
		if ( x+1 <  10 && hole[x+1][y] == false && b[x+1][y] == c && doneboard[x+1][y] == false ) holeupdate(x+1,y,c);
		if ( x-1 >   0 && hole[x-1][y] == false && b[x-1][y] == c && doneboard[x-1][y] == false ) holeupdate(x-1,y,c);
		if ( y+1 <  10 && hole[x][y+1] == false && b[x][y+1] == c && doneboard[x][y+1] == false ) holeupdate(x,y+1,c);
		if ( y-1 >   0 && hole[x][y-1] == false && b[x][y-1] == c && doneboard[x][y-1] == false ) holeupdate(x,y-1,c);
		if ( x+1 <  10 && hole[x+1][y] == true ) uniqset.insert(pair<int,int>(x+1,y));
		if ( x-1 >   0 && hole[x-1][y] == true ) uniqset.insert(pair<int,int>(x-1,y));
		if ( y+1 <  10 && hole[x][y+1] == true ) uniqset.insert(pair<int,int>(x,y+1));
		if ( y-1 >   0 && hole[x][y-1] == true ) uniqset.insert(pair<int,int>(x,y-1));
	}

	void airupdate(int x, int y, bool c, int v) {
		doneboard[x][y] = true;
		air[x][y] = v;
		if ( x+1 <  10 && hole[x+1][y] == false && b[x+1][y] == c && doneboard[x+1][y] == false ) airupdate(x+1,y,c,v);
		if ( x-1 >   0 && hole[x-1][y] == false && b[x-1][y] == c && doneboard[x-1][y] == false ) airupdate(x-1,y,c,v);
		if ( y+1 <  10 && hole[x][y+1] == false && b[x][y+1] == c && doneboard[x][y+1] == false ) airupdate(x,y+1,c,v);
		if ( y-1 >   0 && hole[x][y-1] == false && b[x][y-1] == c && doneboard[x][y-1] == false ) airupdate(x,y-1,c,v);
	}

	void airupdate_setair(int x, int y, bool c, int v) {
		doneboard2[x][y] = true;
		doneboard[x][y] = true;
		air[x][y] = v;
		if ( x+1 <  10 && hole[x+1][y] == false && b[x+1][y] == c && doneboard[x+1][y] == false ) airupdate_setair(x+1,y,c,v);
		if ( x-1 >   0 && hole[x-1][y] == false && b[x-1][y] == c && doneboard[x-1][y] == false ) airupdate_setair(x-1,y,c,v);
		if ( y+1 <  10 && hole[x][y+1] == false && b[x][y+1] == c && doneboard[x][y+1] == false ) airupdate_setair(x,y+1,c,v);
		if ( y-1 >   0 && hole[x][y-1] == false && b[x][y-1] == c && doneboard[x][y-1] == false ) airupdate_setair(x,y-1,c,v);
	}

	void update(int x, int y, bool c, bool mode) {
		bool op_c = !c ;
		b[x][y] = c;
		hole[x][y] = false;

		if ( hole[x+1][y] == false && b[x+1][y] == op_c ) {
			uniqset.clear();
			reset_doneboard();
			holeupdate(x+1,y,op_c);
			reset_doneboard();
			if ( mode )airupdate(x+1,y,op_c,uniqset.size());
			else airupdate_setair(x+1,y,op_c,uniqset.size());
		}
		if ( hole[x-1][y] == false && b[x-1][y] == op_c ) {
			uniqset.clear();
			reset_doneboard();
			holeupdate(x-1,y,op_c);
			reset_doneboard();
			if ( mode )airupdate(x-1,y,op_c,uniqset.size());
			else airupdate_setair(x-1,y,op_c,uniqset.size());
		}
		if ( hole[x][y+1] == false && b[x][y+1] == op_c ) {
			uniqset.clear();
			reset_doneboard();
			holeupdate(x,y+1,op_c);
			reset_doneboard();
			if ( mode )airupdate(x,y+1,op_c,uniqset.size());
			else airupdate_setair(x,y+1,op_c,uniqset.size());
		}	
		if ( hole[x][y-1] == false && b[x][y-1] == op_c ) {
			uniqset.clear();
			reset_doneboard();
			holeupdate(x,y-1,op_c);
			reset_doneboard();
			if ( mode )airupdate(x,y-1,op_c,uniqset.size());
			else airupdate_setair(x,y-1,op_c,uniqset.size());
		}

        uniqset.clear();
		reset_doneboard();
		holeupdate(x,y,c);
		reset_doneboard();
		if ( mode )airupdate(x,y,c,uniqset.size());
		else airupdate_setair(x,y,c,uniqset.size());

	}

	void clear() {
		reset_air();
		reset_hole();
        color = 0;
	}

	void reset_doneboard() {
		memset(&doneboard,false, sizeof(doneboard));
	}

	void reset_doneboard2() {
		memset(&doneboard2,false, sizeof(doneboard2));
	}

	void reset_air() {
		memset(&air,0, sizeof(air));
	}

	void reset_hole() {
		memset(&hole,1, sizeof(hole));
	}

	void set_air() {
		reset_doneboard2();
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				if ( doneboard2[i][j] == false && hole[i][j] == false ) {
					update(i,j,b[i][j],false);
				}
			}
		}
	}

	bool check(int i, bool c) {
        int x=i/9+1, y=i%9+1;
		if ( hole[x][y] == false ) return false;

		int holecnt = 0 ;
		bool op_c = !c;
		if ( x+1 <  10 && hole[x+1][y] == true ) holecnt++;
		if ( x-1 >   0 && hole[x-1][y] == true ) holecnt++;
		if ( y+1 <  10 && hole[x][y+1] == true ) holecnt++;
		if ( y-1 >   0 && hole[x][y-1] == true ) holecnt++;

		if ( holecnt == 0 ) {
			if ( x+1 <  10 && hole[x+1][y] == false && b[x+1][y] == op_c ){ if ( air[x+1][y] == 1 ) return false; }
			if ( x-1 >   0 && hole[x-1][y] == false && b[x-1][y] == op_c ){ if ( air[x-1][y] == 1 ) return false; }
			if ( y+1 <  10 && hole[x][y+1] == false && b[x][y+1] == op_c ){ if ( air[x][y+1] == 1 ) return false; }
			if ( y-1 >   0 && hole[x][y-1] == false && b[x][y-1] == op_c ){ if ( air[x][y-1] == 1 ) return false; }

			bool flag = false;
			if ( x+1 <  10 && hole[x+1][y] == false && b[x+1][y] == c ){ if ( air[x+1][y] != 1 ) flag = true; }
			if ( x-1 >   0 && hole[x-1][y] == false && b[x-1][y] == c ){ if ( air[x-1][y] != 1 ) flag = true; }
			if ( y+1 <  10 && hole[x][y+1] == false && b[x][y+1] == c ){ if ( air[x][y+1] != 1 ) flag = true; }
			if ( y-1 >   0 && hole[x][y-1] == false && b[x][y-1] == c ){ if ( air[x][y-1] != 1 ) flag = true; }

			if ( flag == true ) return true;
			return false;
		}else {

			if ( x+1 != 10 && hole[x+1][y] == false && b[x+1][y] == op_c ){ if ( air[x+1][y] == 1 ) return false; }
			if ( x-1 !=  0 && hole[x-1][y] == false && b[x-1][y] == op_c ){ if ( air[x-1][y] == 1 ) return false; }
			if ( y+1 != 10 && hole[x][y+1] == false && b[x][y+1] == op_c ){ if ( air[x][y+1] == 1 ) return false; }
			if ( y-1 !=  0 && hole[x][y-1] == false && b[x][y-1] == op_c ){ if ( air[x][y-1] == 1 ) return false; }
			return true;
		}
	}

	void add(int i, bool c) {
        int x=i/9 +1, y=i%9 +1;
		b[x][y] = c;
		hole[x][y] = false;
        color = !color;
	}
    bool playing_color(){
        return color;
    }

    bool simulate(bool c) {
		// bool flag = true;
		vector<int> player;
		vector<int> two;
		bool op_c = !c;
		while(1) {
			int pick=0;
			handle_available(op_c,player,two);
			if ( two.size() != 0 ) pick = two[rand()%two.size()];
			else if( player.size() != 0 ) pick = player[rand()%player.size()];
			else break;

			update(pick/9 +1,pick%9 +1,op_c,1);
			op_c = !op_c;
			player.clear();
			two.clear();
		}
        // cerr<<op_c<<"  ";
        
		return !op_c;
		// return (op_c)?1:-1;
	}

    double simulate_v(bool c){
        int i,pick,tsize,bsize,wsize;
        bool bc,wc;
        vector<int> black;
        vector<int> white;
        vector<int> two;

        handle_available_v(black, two, white);

        bsize = black.size();
        wsize = white.size();
        tsize = two.size();
		bool play_c = !c;

    FLAG:
        while(tsize>0){
            i=rand()%tsize;
            pick=two[i];
            two[i]=two[tsize-1];
            tsize--;
            bc=check(pick,0);
            wc=check(pick,1);
            if(check(pick,play_c) ){
			    update(pick/9 +1,pick%9 +1,play_c,1);
                play_c=!play_c;
                goto FLAG;
            }else{
                if(!bc && wc){
                    white.push_back(pick);
                    wsize++;
                }
                else if(bc && !wc){
                    black.push_back(pick);
                    bsize++;
                }
            }
        }
    FLAG2 :
        if(play_c==0){

            while(bsize>0){
                i=rand()%bsize;
                pick=black[i];
                black[i]=black[bsize-1];
                bsize--;
                if(check(pick,play_c)){
			        update(pick/9 +1,pick%9 +1,play_c,1);
                    play_c=!play_c;
                    goto FLAG2;
                }
            }
        }
        else{
            while(wsize>0){
                i=rand()%wsize;
                pick=white[i];
                white[i]=white[wsize-1];
                wsize--;
                if(check(pick,play_c)){
			        update(pick/9 +1,pick%9 +1,play_c,1);
                    play_c=!play_c;
                    goto FLAG2;
                }
            }
        }
        black.clear();
        white.clear();
        two.clear();
		return !play_c;
    }

	void show() {
		cerr <<  "show my board: \n";
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				if ( hole[i][j] == false ) cerr <<  b[i][j] << " " ;
				else cerr << "  ";
			}
			cerr << endl;
		}
        // show_cout();
        show_air();
        show_checker();
	}

    void handle_available(bool c, vector<int>& player, vector<int>& two ) {
		bool op_c = !c;
		for ( int i = 0 ; i < 81 ; i++ ) {
            bool ccheck = check(i,c);
            bool op_ccheck = check(i,op_c);
            if ( ccheck == true && op_ccheck == true ) two.push_back( i );
            else if ( ccheck == true ) player.push_back( i );
		}
	}
    void handle_available_v(vector<int>& black, vector<int>& two , vector<int>& white ) {
		// bool op_c = !c;
		for ( int i = 0 ; i < 81 ; i++ ) {
            bool bcheck = check(i,0);
            bool wcheck = check(i,1);
            if ( bcheck && wcheck ) two.push_back( i );
            else if ( bcheck == true ) black.push_back( i );
            else if ( wcheck == true ) white.push_back( i );
		}
	}

	void show_cout() {
		cout <<  "show my board: \n";
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				if ( hole[i][j] == false ) cout <<  b[i][j] << " " ;
				else cout << "  ";
			}
			cout << endl;
		}
	}

	void show_air() {
		cerr <<  "show my air board: \n";
        int flag = false;
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {

				if ( hole[i][j] == false ) {
                    cerr <<  air[i][j] << " " ;
                    if(air[i][j]==0)flag = true;
                }
				else cerr << "  ";
			}
			cerr << endl;
		}
        if(flag){
        }
	}

	void show_checker() {
		cerr << "black\n"; 
        int cc = 0;
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				if ( hole[i][j] == true ) cerr <<  check(cc,0) << " " ;
				else cerr << "  ";
                cc++;
			}
			cerr << endl;
		}
		cerr << "white\n";
        cc = 0;
		for ( int i = 1 ; i < 10 ; i++ ) {
			for ( int j = 1 ; j < 10 ; j++ ) {
				if ( hole[i][j] == true ) cerr <<  check(cc,1) << " " ;
				else cerr << "  ";
                cc++;
			}
			cerr << endl;
		}
	}

};
