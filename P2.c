//First, assume Alpha=0.125 and open test.in; Second, get array sRTT[] from test.in; Third, assume eRTT[0]=100ms, and calculate eRTT[n]=(1-Alpha)*eRTT[n-1]+Alpha*sRTT[n] and output answer;
//To be precise, need to decide whether to round up or round down by comparing with 0.5
/*
                k=eRTT[i]*100;
                j=(int)(k);
                if(k-j>=0.5)
                   j++;
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char *argv[ ]){
	FILE *fp;
        double Alpha=0.125,k;
	int n,i,j;
	int RTT[100000];
        double eRTT[100000];
	if((fp=fopen(argv[1],"r"))==NULL){     //open test.in
		printf("File open error! \n");
		exit(0);
	}
	fscanf(fp,"%d",&n);
	i=0;
	for(i=0;i<n;i++){           //get array sRTT[]
		fgetc(fp);
		fscanf(fp,"%d",RTT+i);
	}
        eRTT[0]=100;            //assume eRTT[0]=100ms
        printf("Assume Alpha as %lf\n",Alpha);
        printf("eRTT0:100.00ms\n");
        for(i=1;i<=n;i++){
                eRTT[i]=(1-Alpha)*eRTT[i-1]+Alpha*RTT[i-1];//calculate eRTT[n]
                k=eRTT[i]*100;
                j=(int)(k);
                if(k-j>=0.5)     //decide whether to round up or round down
                   j++;
                eRTT[i]=(double)j/100;
                printf("eRTT%d:%.2lfms\n",i,eRTT[i]);
        }
	fclose(fp);
	return 0;
}
