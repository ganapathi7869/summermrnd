#include<stdio.h>
#include<stdlib.h>
int solve(int **mat, int m, int n, int starti, int startj, int endi, int endj, int **sol){
	sol[starti][startj] = 1;
	if (starti == endi && startj == endj) {
		return 1;
	}
	mat[starti][startj] = 2;
	if (startj > 0 && mat[starti][startj - 1] == 1){
		if (solve(mat, m, n, starti, startj - 1, endi, endj, sol)){
			mat[starti][startj] = 1;
			return 1;
		}
	}
	if (starti < n - 1 && mat[starti + 1][startj] == 1){
		if (solve(mat, m, n, starti + 1, startj, endi, endj, sol)){
			mat[starti][startj] = 1;
			return 1;
		}
	}
	if (startj < m - 1 && mat[starti][startj + 1]==1){
		if (solve(mat, m, n, starti, startj + 1, endi, endj, sol)){
			mat[starti][startj] = 1;
			return 1;
		}
	}
	if (starti > 0 && mat[starti - 1][startj] == 1){
		if (solve(mat, m, n, starti - 1, startj, endi, endj, sol)){
			mat[starti][startj] = 1;
			return 1;
		}
	}
	mat[starti][startj] = 1;
	sol[starti][startj] = 0;
	return 0;
}
int main(){
	int m, n,starti,startj,endi,endj;
	printf("enter values of m and n:");
	scanf("%d %d", &m, &n);
	int **mat = (int **)malloc(sizeof(int *)*m);
	int **sol = (int **)malloc(sizeof(int*)*m);
	printf("enter values of matrix 0->block 1->empty:\n");
	for (int i = 0; i < m; i++){
		mat[i] = (int *)malloc(n* sizeof(int));
		sol[i] = (int *)calloc(n, sizeof(int));
		for (int j = 0; j < n; j++){
			scanf("%d", &mat[i][j]);
		}
	}
	printf("enter starting coordinates:");
	scanf("%d %d", &starti, &startj);
	printf("enter ending coordinates:");
	scanf("%d %d", &endi, &endj);
	int solved=solve(mat, m, n, starti, startj, endi, endj, sol);
	if (!solved){
		printf("no solution");
		return 0;
	}
	printf("solution matrix:\n");
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			printf("%d ", sol[i][j]);
		}
		printf("\n");
	}
	return 0;
}
