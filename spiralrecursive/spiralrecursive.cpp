#include<stdio.h>
#include<stdlib.h>
void spiral(int **a, int *top, int *bot, int *left, int *right,int *sw){
	if (*top > *bot || *left > *right)  return;
	if (*sw == 0){
		for (int k = *left; k <= *right; k++){
			printf("%d ",a[*top][k]);
		}
		(*top)++;
	}
	else if (*sw == 1){
		for (int k = *top; k <= *bot; k++){
			printf("%d ", a[k][*right]);
		}
		(*right)--;
	}
	else if (*sw == 2){
		for (int k = *right; k >= *left; k--){
			printf("%d ", a[*bot][k]);
		}
		(*bot)--;
	}
	else{
		for (int k = *bot; k >= *top; k--){
			printf("%d ", a[k][*left]);
		}
		(*left)++;
	}
	*sw = ((*sw) + 1) % 4;
	spiral(a, top, bot, left, right, sw);
}
int main(){
	int m, n;
	printf("enter values of m and n:");
	scanf("%d %d", &m, &n);
	int **a = (int **)malloc(sizeof(int *)*m);
	for (int i = 0; i < m; i++)   {
		a[i] = (int *)malloc(sizeof(int)*n);
		for (int j = 0; j < n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	int top = 0, bot = m - 1, left = 0, right = n - 1, sw = 0;
	spiral(a, &top, &bot, &left, &right,&sw);
	return 0;
}
