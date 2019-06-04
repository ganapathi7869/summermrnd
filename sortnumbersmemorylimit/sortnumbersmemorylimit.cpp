#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int compare(const void *p, const void *q){
	return *(int *)p - *(int *)q;
}

void writetofile(int *buf, int len, FILE *fptr){
	for (int i = 0; i < len; i++){
		fprintf(fptr, "%d\n", buf[i]);
	}
	fclose(fptr);
}
int main(){
	FILE *filear[100],*inpptr,*outptr,*fptr;
	char filename[20],num[20];
	int nooffiles = 0,buf[5],bufind,i,min,minind;
	inpptr = fopen("input.txt", "r");
	while (1){
		bufind = -1;
		for (i = 0; i < 5; i++){
			if (EOF == fscanf(inpptr, "%d", &buf[++bufind])){
				bufind--; break;
			}
		}
		if (bufind == -1) break;
		qsort(buf, bufind + 1, sizeof(int),&compare);
		filename[0] = 'f';
		filename[1] = '\0'; //strcat(strcat(filename,_itoa(nooffiles+1,num,10)),".txt") 
		fptr = fopen(strcat(strcat(filename, _itoa(nooffiles + 1, num, 10)), ".txt"), "w");
		filear[nooffiles++] = fptr;
		//if (!filear[nooffiles - 1])  printf("ksjdfd");
		writetofile(buf, bufind + 1, filear[nooffiles - 1]);
		if (i < 5) break;
	}
	for (int i = 0; i < nooffiles; i++){
		filear[i]=fopen(strcat(strcat(filename, _itoa(nooffiles + 1, num, 10)), ".txt"), "r");
	}
	outptr = fopen("output.txt", "w");
	for (i = 0; i < nooffiles; i++){
		if (fscanf(filear[i], "%d", &buf[i]) == EOF){
			buf[i] = -1;
		}
	}
	while (1){
		min = 10000001; minind = -1;
		for (i = 0; i < nooffiles; i++){
			if (buf[i] < min){
				min = buf[i];
				minind = i;
			}
		}
		if (minind == -1) break;
		fprintf(outptr, "%d\n", min);
		if (feof(filear[minind])){
			buf[minind] = 10000001;
		}
		else fscanf(filear[minind], "%d", &buf[minind]); 
	}
	fclose(outptr);
	fclose(inpptr);
	for (int i = 0; i < nooffiles; i++){
		fclose(filear[i]);
	}
	return 0;
}
