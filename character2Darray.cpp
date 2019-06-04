#include<stdio.h>
#include<stdlib.h>
void extract(char **mat, int m, int n,int mind,int nind, char *str, int len, int *a, int ind,int dir){
	if (ind == len - 1){
		printf("%d %d:%d %d\n", a[0], a[1], mind, nind); return;
	}
	if (dir == 0){
		if (mind == 0 || str[ind + 1] != mat[mind - 1][nind]) return;
		extract(mat, m, n, mind - 1, nind, str, len, a, ind + 1, dir);
	}
	else if (dir == 1){
		if (mind == 0 || nind == n - 1 || str[ind + 1] != mat[mind - 1][nind + 1]) return;
		extract(mat, m, n, mind - 1, nind+1, str, len, a, ind + 1, dir);
	}
	else if (dir == 2){
		if (nind == n - 1 || str[ind + 1] != mat[mind][nind + 1])  return;
		extract(mat, m, n, mind , nind+1, str, len, a, ind + 1, dir);
	}
	else if (dir == 3){
		if (mind == m - 1 || nind == n - 1 || str[ind + 1] != mat[mind + 1][nind + 1]) return;
		extract(mat, m, n, mind +1, nind+1, str, len, a, ind + 1, dir);
	}
	else if (dir == 4){
		if (mind == m - 1 || str[ind + 1] != mat[mind + 1][nind])  return;
		extract(mat, m, n, mind + 1, nind, str, len, a, ind + 1, dir);
	}
	else if (dir == 5){
		if (mind == m - 1 || nind == 0 || str[ind + 1] != mat[mind + 1][nind - 1]) return;
		extract(mat, m, n, mind + 1, nind-1, str, len, a, ind + 1, dir);
	}
	else if (dir == 6){
		if (nind == 0 || str[ind + 1] != mat[mind][nind - 1]) return;
		extract(mat, m, n, mind , nind-1, str, len, a, ind + 1, dir);
	}
	else{
		if (mind == 0 || nind == 0 || str[ind + 1] != mat[mind - 1][nind - 1])  return;
		extract(mat, m, n, mind - 1, nind-1, str, len, a, ind + 1, dir);
	}
}
void searchword(char **mat,int m,int n, char *str, int len,int *a){
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			if (mat[i][j] == str[0]) {
				a[0] = i; a[1] = j;
				for (int k = 0; k < 8; k++){
					extract(mat, m, n,i,j ,str, len, a, 0,k);
				}
			}
		}
	}
}
int main(){
	char *mat[] = { "abcd", "efgh", "ijkl" };
	char str[] = "be";
	int m = 3, n = 4;
	int *a = (int *)malloc(sizeof(int) * 4);
	searchword(mat, m, n, str, sizeof(str) / sizeof(char)-1, a);

	return 0;

}