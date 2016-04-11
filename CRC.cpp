/*
Program Description:  CRC check program for CMPT371 Project 2
Author: Yu Xiao   301267080
Teammate: Shuyang Dai
Date: 2014/11/30
Version: 1.0
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

// for debug
#ifdef debug
#define ll unsigned int 
#else 
#define ll unsigned long long
#endif

// read each binary data
ll  readb(FILE *fin){
	// read as a string
	char s[65];
	fgets(s,66,fin);
	int len = strlen(s);
	if(s[len-1]!='1' && s[len-1]!='0') s[len-1] = '\0';
	//puts(s);
	//printf("len: %d\n",strlen(s));
	
	// transform the string into an integer
	ll ans=0;
	len = strlen(s);
	for(int i=0;i<len;i++) ans = ans * 2 + s[i]-'0';
	// return the integer
	return ans;
}

// count the binary length 
int cntlen(ll x){
	int len = 0;
	while(x){
		x = x >> 1;
		len++;
	}
	return len;
}

// print number as a binary number
void print(ll x){
	int len=cntlen(x);
	for(int i=len-1;i>=0;i--) printf("%d", (x & (1<<i)) > 0 );
	printf("\n");
}

// check if G,D,R form the correct data
int check(ll G,ll D,ll R){
	int g=cntlen(G);
	int r=g-1;
	if(cntlen(R) > r) return -1;

	D = (D << r) ^ R;
	int d=cntlen(D);

	#ifdef debug
	printf("G: "); print(G);
	printf("D: "); print(D);
	printf("R: "); print(R);
	#endif

	while(d>=g){
		D = D ^ (G << (d-g));	// binary subtraction
		while( (D & (1<<(d-1))) == 0 && d>0) d--;	// renew d according to new D
		#ifdef debug
		printf("D(%d): ",d); print(D);
		#endif
	}
	return (D==0);
}

int main(int argc,char **argv){
	ll G,D,R;

	FILE *fin;
	if(argc==1){ printf("No Input File!\n"); exit(1); }
	else{
		if( (fin = fopen(argv[1],"r")) == NULL) {
			printf("Cannot Open Input File!\n");
			exit(1);
		}
	}

	// read input
	G = readb(fin);
	D = readb(fin);
	R = readb(fin);

	fclose(fin);

	// output result
	int ans = check(G,D,R);
	if(ans==1) printf("Yes\n");
	else if(ans==0) printf("No\n");
	else if(ans==-1) printf("Unreasonable Input\n");

	return 0;
}
