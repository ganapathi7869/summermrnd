#include<stdio.h>
#include<stdlib.h>
void printarray(int *ar, int len){
	for (int i = 0; i < len; i++){
		printf("%d ", ar[i]);
	}
	printf("\n");
}
void printpermutations(int *ar,int ind, int len){
	if (ind == len-1){
		printarray(ar, len);
		return;
	}
	int temp;
	printpermutations(ar, ind + 1, len);
	for (int i = ind + 1; i < len; i++){
		temp = ar[i];
		ar[i] = ar[ind];
		ar[ind] = temp;
		printpermutations(ar, ind + 1, len);
		temp = ar[i];
		ar[i] = ar[ind];
		ar[ind] = temp;
	}
}
int main(){
	int ar[] = { 1,3,5};
	printpermutations(ar,0, sizeof(ar) / sizeof(int));
	return 0;
}
