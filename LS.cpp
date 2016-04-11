/* 
Program Description: Link State. Implemented by Dijstra Algorithm. for CMPT371 Project 2
Author: Yu Xiao  301267080
Teammate: Shuyang Dai
Date: 2014/11/30
Version: 1.0
*/

#include <cstdio>
#include <cstdlib>

int N,L;	// number of nodes & number of links

const int MAXN = 27 +1;	// max number of nodes

char names[MAXN];	// name of nodes

int Matrix[MAXN][MAXN];	// direct distance between every pair of nodes. -1 means no link
int dist[MAXN];		// current shortest distance from start node to every other node
int tried[MAXN];	// record if a node's shortest distance has been calculated already
int pre[MAXN];		// the preceding node on the path to a node

int find(char c){	// find the serial number of a name
	for(int i=0;i<N;i++) if(c==names[i]) return i;
	return N;
}

void readin(FILE *fin){	// read input
	// read name of input file
	/*
	char fname[100];
	printf("Please input the name of input file: ");
	gets(fname);

	FILE *fin;
	if( (fin = fopen(fname,"r")) == NULL){	// if cannot open input file
		printf("Cannot open input file!\n");
		exit(1);
	}
	*/

	fscanf(fin,"%d %d",&N,&L);

	// initializing global variables
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			Matrix[i][j] = -1;	// -1: no link
	for(int i=0;i<N;i++) 
		Matrix[i][i] = 0;	// 0 distance to self

	// read direct links
	for(int i=0;i<N;i++) fscanf(fin," %c",&names[i]);
	for(int i=0;i<L;i++){
		char x,y;
		int z;
		fscanf(fin," %c %c %d",&x,&y,&z);
		int ix=find(x),iy=find(y);
		Matrix[ix][iy] = Matrix[iy][ix] = z;
	}
}

void Dijstra(int s){	// calculate shortest distance from node s to every other node using Dijstra Algorithm
	// initializing important tracking variables
	for(int i=0;i<N;i++) tried[i] = 0;
	tried[s] = 1;	// add start node s to the set where shortest distance is calculated
	for(int i=0;i<N;i++) dist[i] = Matrix[s][i];	// current distance from s to every node
	for(int i=0;i<N;i++) 
		if(dist[i]>0) pre[i] = s;	// if connected, set its preceding node as s
		else pre[i] = -1;	// if not connected directly, set its preceding node as -1
	
	// add other N-1 nodes once per iteration
	for(int k=1;k<N;k++){
		int min;
		int mini=-1;	// the i when min gets its minimum
		for(int i=0;i<N;i++) if(!tried[i] && dist[i]!=-1){	// if not added and connected
			// renew min value and mini
			if(mini==-1){ mini=i; min = dist[i]; }
			else if(min > dist[i]) { min = dist[i]; mini=i; }
		}
		if(mini==-1) break;	// in case the graph is not connected
		tried[mini]=1;	// add node mini to the set
		// renew distance from s to all other un-added nodes
		for(int i=0;i<N;i++) if(!tried[i] && Matrix[mini][i]!=-1 && i!=mini){
			if(dist[i]==-1 || dist[i] > dist[mini] + Matrix[mini][i]){
				dist[i] = dist[mini] + Matrix[mini][i];
				pre[i] = mini;
			}
		}
	}
}

void output_recur(int p){ // print the path to p recursively
	if(pre[p]==-1) printf("%c",names[p]);
	else{
		output_recur(pre[p]);
		printf("-%c",names[p]);
	}
}

void output(){ // print the path from 0 to every other node
	for(int i=1;i<N;i++){
		printf("%c: ",names[i]);
		if(dist[i]>=0) output_recur(i);
		printf(" %d\n",dist[i]);
	}
}

int main(int argc,char **argv){
	if(argc==1){ printf("No Input File\n"); exit(1); }

	FILE *fin;
	if( (fin = fopen(argv[1],"r")) == NULL){ printf("Cannot Open Input File!\n"); exit(1); }

	readin(fin);	// read input
	fclose(fin);

	Dijstra(0);	// calculate shortest distance from 0 to every other node
	output();	// print the path from 0 to every other node

	return 0;	// exit normally
}
