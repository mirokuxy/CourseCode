/* 
Program Description: Distance Vector. Implemented by Bellman-Ford Algorithm. for CMPT371 Project 2
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
int dist[MAXN][MAXN][MAXN];		// current distance vectors stored at each node

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

	fclose(fin);
}

void output(int);	// defined later. declar here only for debug (used in Bellman_Ford())

int Bellman_Ford(){ // Calculate Distance Vector, using Bellman-Ford Algorithm
	int count = 1;	// count number of round

	// initializing distance vector
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			for(int k=0;k<N;k++)
				dist[i][j][k] = -1;	// no connection

	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			dist[i][i][j] = Matrix[i][j];	// connected with its neighbour

	bool notover;	// if distance vector has not converged
	do{	// keep updating distance vectors

		// debug use
		#ifdef debug
		output(count);
		#endif 

		// update distance vectors from neighbors
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++) if(i!=j && Matrix[i][j]>=0)
				for(int k=0;k<N;k++)
					dist[i][j][k] = dist[j][j][k];

		// for each node, update its own new distance vectors
		notover = 0;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++) if(j!=i && Matrix[i][j]>=0) // if j is neighbor to i
				for(int k=0;k<N;k++) if(k!=i && k!=j && dist[i][j][k]>=0){	// if j has a path to k
					if(dist[i][i][k] <0 || dist[i][i][k] > Matrix[i][j] + dist[i][j][k]){ // if i->j-K is a better path
						dist[i][i][k] = Matrix[i][j] +dist[i][j][k];
						notover = 1;	// update occurs, distance vectors have not converged yet.
					}
				}
		
		count++;
	}while(notover);

	return count;	// return the number of Rounds needed to converge
}

void output(int Round){	// output the current distance vectors for every node
	printf("------- Round %d ---------\n",Round);
	for(int k=0;k<N;k++){
		printf("[%c] ",names[k]);
		for(int i=0;i<N;i++) printf("   %c",names[i]);
		printf("\n");
		for(int i=0;i<N;i++){
			printf("%c:  ",names[i]);
			for(int j=0;j<N;j++) printf("%4d",dist[k][i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

int main(int argc,char **argv){
	if(argc==1){ printf("No Input File\n"); exit(1); }

	FILE *fin;
	if( (fin = fopen(argv[1],"r")) == NULL){ printf("Cannot Open Input File!\n"); exit(1); }

	readin(fin);	// read input
	fclose(fin);

	int count = Bellman_Ford();	// calculate the Distance Vectors
	printf("The program finishes in %d round.\n",count);	// print the round taken to finish the process
	output(count);	// print the distance vector for each node

	return 0;	// exit normally
}
