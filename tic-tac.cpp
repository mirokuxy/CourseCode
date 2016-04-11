/*
CMPT310 Assignment 5 Basic version
Author: Yu Xiao
Date: 2014/11/25
Version: 1.0

Compile command: 
	g++ tic-tac.cpp -o tic-tac
Usage:
	tic-tac [input file]
Notes:
	This is the basic version, thus not using any kind of pruning.
	If provided with an input file with large space to fill in,
	this program may take huge amount of time to execute.

*/


#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 4+1;
const int MAXSTATE = 50000000;

int size;
int player;

typedef int Matrix [MAXN][MAXN];
Matrix board;

int crow[3][MAXN],ccol[3][MAXN];
int cdigu[3],cdigd[3];
int cntall;

bool tried[MAXSTATE]; // 1: searched; 0: not searched;
int state[MAXSTATE];  // 2: X wins; 1: O wins; 0: draw; 
					  // [the optimal result for whomever made the state]


int trans(char c){
	if(c=='X') return 2;
	if(c=='O') return 1;
	return 0;
}

char reverse(int p){
	if(p==2) return 'X';
	if(p==1) return 'O';
	return '-';
}

int readin(const char *FIN){
	FILE *fin = fopen(FIN,"r");
	char c;

	fscanf(fin,"SIZE: %d",&size);
	fscanf(fin," PLAYER: %c",&c);
	player = trans(c);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			fscanf(fin," %c",&c);
			board[i][j] = trans(c);
		}
	fclose(fin);

	return 0;
}

int init(){
	for(int j=0;j<3;j++)
		for(int i=0;i<size;i++)
			crow[j][i] = ccol[j][i] = 0;
	for(int j=0;j<3;j++) cdigu[j] = cdigd[j] = 0;
	cntall=0;
	
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			crow[board[i][j]][i]++;
			ccol[board[i][j]][j]++;
		}

	
	for(int i=0;i<size;i++){
		cdigd[board[i][i]]++;
		cdigu[board[i][size-i-1]]++;
	}

	int cnt[3]={0,0,0};
	for(int j=1;j<3;j++)
		for(int i=0;i<size;i++) 
			cnt[j] += crow[j][i];
	cntall = cnt[1] + cnt[2];
	if(cnt[player]+1 != cnt[3-player] && cnt[player] != cnt[3-player]) return -1;



	return 0;
}

int check(int p){
	for(int i=0;i<size;i++) if(crow[p][i] == size || ccol[p][i] == size) return 1;
	if(cdigu[p] == size || cdigd[p] == size) return 1;
	return 0;
}

int get_num(){
	int ans=0;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			ans = ans*3 + board[i][j];
	return ans;
}

int better(int a,int b,int p){
	if(a==p && b!=p) return 1;
	if(a==0 && b==3-p) return 1;
	return 0;
}

void put(int i,int j,int p){
	board[i][j] = p;
	crow[p][i]++; ccol[p][j]++; cntall++;
	if(i==j) cdigd[p]++;
	if(i+j == size-1) cdigu[p]++;	
}

void take(int i,int j,int p){
	board[i][j] = 0;
	crow[p][i]--; ccol[p][j]--; cntall--;
	if(i==j) cdigd[p]--;
	if(i+j == size-1) cdigu[p]--;
}

void refresh(){
	memset(tried,sizeof(tried),0);
}

void print_board(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++)
			printf("%c",reverse(board[i][j]));
		printf("\n");
	}
	printf("\n");
}

int make_move(int p,int depth){
	//printf("into depth %d\n",depth);
	//print_board();

	if(check(3-p)) { /* printf("out depth 1:%d (%d)\n",depth,3-p); */ return 3-p; }
	if(cntall == size*size) { /* printf("out depth 2:%d (%d)\n",depth,0); */ return 0; }

	int flag=0;
	int ans;

	int x,y;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++) if(board[i][j]==0){
			put(i,j,p);
			
			int st = get_num();
			if(! tried[st]) { tried[st]=1; state[st] = make_move(3-p,depth+1); }

			take(i,j,p);

			if(!flag) { flag=1; ans = state[st]; x=i; y=j; }
			else if(better(state[st],ans,p)) { ans=state[st]; x=i; y=j; }
		}

	if(depth==0) put(x,y,p);

	//printf("out depth 3:%d (%d)\n",depth,ans);
	return ans;
}

void read_move(){
	printf("Enter your move [row col] separated by a space: ");
	int i,j;
	while(scanf("%d %d",&i,&j)!=2 || i<0 || i>=size || j<0 || j>=size || board[i][j]!=0){
		if ( !(i<0 || i>=size || j<0 || j>=size || board[i][j]!=0)) printf("Wrong format\n"); 
		else printf("Wrong move!\n");
		printf("Enter your move [row col] separated by a space: ");
	}
	put(i,j,3-player);
}

int main(int argc,char **argv){
	readin(argv[1]);
	if(init()==-1){
		printf("unreasonable input\n");
		exit(1);
	}
	if(check(2)) { printf("X Wins\n"); return 0;}
	if(check(1)) { printf("O Wins\n"); return 0;}

	printf("--- You are player %c ---\n",reverse(3-player));

	while(1){
		print_board();
		if(check(3-player)) { printf("You win!\n"); return 0; }
		if(cntall == size*size) { printf("Draw\n"); return 0; }
		refresh();
		make_move(player,0);
		print_board();
		if(check(player)) { printf("You lose!\n"); return 0; }
		if(cntall == size*size) { printf("Draw\n"); return 0; }
		read_move();
	}

	return 0;
}



	
