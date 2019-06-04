#include<stdio.h>
#include<stdlib.h>
void print(int *buf, int ind, int k,char *map){
	if (ind == k) {
		int num = 0;
		for (int i = 0; i < k; i++){
			num = num * 10 + buf[i];
		}
		printstr(num, k, map);
		return;
	}
	for (int i = 0; i <= 9; i++){
		buf[ind] = i;
		print(buf, ind + 1, k,map);
	}
}
int main(){
	int k;
	scanf("%d", &k);
	int *buf = (int *)malloc(sizeof(int)*(k-1));
	char map[] = {'0','1','2','E','h','5','9','L','8','6'};
	print(buf,0,k-1,map);
	return 0;
}
