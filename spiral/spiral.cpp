#include<stdio.h>
#include<stdlib.h>
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
	int *b = (int *)malloc(sizeof(int)*(m*n));
	int indofb = 0;
	int top = 0, bot = m - 1, left = 0, right = n - 1,sw=0;
	while (top <= bot && left <= right){
		if (sw == 0){
			for (int k = left; k <= right; k++){
				b[indofb++] = a[top][k];
			}
			top++;
		}
		else if (sw == 1){
			for (int k = top; k <= bot; k++){
				b[indofb++] = a[k][right];
			}
			right--;
		}
		else if (sw == 2){
			for (int k = right; k >= left; k--){
				b[indofb++] = a[bot][k];
			}
			bot--;
		}
		else{
			for (int k = bot; k >= top; k--){
				b[indofb++] = a[k][left];
			}
			left++;
		}
		sw = (sw + 1) % 4;
	}
	for (int i = 0; i < (m*n); i++){
		printf("%d ", b[i]);
	}
	return 0;
}
