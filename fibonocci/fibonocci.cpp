#include<stdio.h>
#include<stdlib.h>
int main(){
	long n, i=2,prev1=0,prev2=1,temp;
	scanf("%ld", &n);
	if (n < 0) return 1;
	if (n == 0){
		printf("0"); return 0;
	}
	if (n == 1){
		printf("1"); return 0;
	}
	while (i<=n){
		temp = prev2;
		prev2 = prev1 + prev2;
		prev1 = temp;
		i++;
	}
	printf("%d ", prev2);
	return 0;
}
