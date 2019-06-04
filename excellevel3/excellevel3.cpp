#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unordered_set>
using namespace std;
#include<string>
#include "utilities.h"
struct node{
	char op1[5];
	char op;
	char op2[5];
};
void lower(char *str){
	int i = 0;
	while (str[i] != '\0'){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = 'a' + str[i] - 'A';
		}
		i++;
	}
}
int validate(char *str, struct node mat[10][10], unordered_set<string> stringset){
	int r, c, ind = 0, operind = 0;
	char *hold;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	c = str[ind++] - 'a';
	r = str[ind++] - '1';
	if (mat[r][c].op == '\0') {

	}
}
int set(char *str, struct node mat[10][10]){
	int r, c, ind = 0, operind = 0;
	char *hold;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	c = str[ind++] - 'a';
	r = str[ind++] - '1';
	if (str[ind++] != '=')  return 1;
	if (hold = strchr(&str[ind], '+')){
		while (&str[ind] != hold){
			mat[r][c].op1[operind++] = str[ind++];
		}
		mat[r][c].op1[operind] = '\0';
		mat[r][c].op = '+';
		ind++;
		operind = 0;
		while ((str[ind] >= '0' && str[ind] <= '9') || (str[ind] >= 'a'&& str[ind] <= 'j')){
			mat[r][c].op2[operind++] = str[ind++];
		}
		mat[r][c].op2[operind] = '\0';
	}
	else if (hold = strchr(&str[ind], '-')){
		while (&str[ind] != hold){
			mat[r][c].op1[operind++] = str[ind++];
		}
		mat[r][c].op1[operind] = '\0';
		mat[r][c].op = '-';
		ind++;
		operind = 0;
		while ((str[ind] >= '0' && str[ind] <= '9') || (str[ind] >= 'a'&& str[ind] <= 'j')){
			mat[r][c].op2[operind++] = str[ind++];
		}
		mat[r][c].op2[operind] = '\0';
	}
	else if (hold = strchr(&str[ind], '*')){
		while (&str[ind] != hold){
			mat[r][c].op1[operind++] = str[ind++];
		}
		mat[r][c].op1[operind] = '\0';
		mat[r][c].op = '*';
		ind++;
		operind = 0;
		while ((str[ind] >= '0' && str[ind] <= '9') || (str[ind] >= 'a'&& str[ind] <= 'j')){
			mat[r][c].op2[operind++] = str[ind++];
		}
		mat[r][c].op2[operind] = '\0';
	}
	else if (hold = strchr(&str[ind], '/')){
		while (&str[ind] != hold){
			mat[r][c].op1[operind++] = str[ind++];
		}
		mat[r][c].op1[operind] = '\0';
		mat[r][c].op = '/';
		ind++;
		operind = 0;
		while ((str[ind] >= '0' && str[ind] <= '9') || (str[ind] >= 'a'&& str[ind] <= 'j')){
			mat[r][c].op2[operind++] = str[ind++];
		}
		mat[r][c].op2[operind] = '\0';
	}
	else{
		while ((str[ind] >= '0' && str[ind] <= '9') || (str[ind] >= 'a'&& str[ind] <= 'j')){
			mat[r][c].op1[operind++] = str[ind++];
		}
		mat[r][c].op1[operind] = '\0';
	}
	return 0;
	/*int r, c,value=0;
	int ind = 0;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	r = str[ind++] - 'a';
	c = str[ind++] - '0'-1;
	if (str[ind++] != '=')  return 1;
	while (str[ind] >= '0' && str[ind] <= '9'){
	value = value * 10 + str[ind++] - '0';
	}
	mat[r][c] = value;
	while (str[ind] != '\0'){
	if (str[ind] != ' ')  return 1;
	ind++;
	}
	return 0;*/
}
int optonumber(char *str, struct node mat[10][10]){
	int r, c;
	if (str[0] >= 'a' && str[0] <= 'j'){
		c = str[0] - 'a';
		r = str[1] - '1';
		return optonumber(mat[r][c].op1, mat);
	}
	int number = 0, ind = 0;
	while (str[ind] != '\0'){
		number = number * 10 + str[ind] - '0';
		ind++;
	}
	return number;
}
int get(char *str, struct node mat[10][10], int print){
	int r, c;
	int ind = 0;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	c = str[ind++] - 'a';
	r = str[ind++] - '1';
	/*while (str[ind] != '\0'){
	if (str[ind] != ' ')  return 1;
	ind++;
	}*/
	int op1, op2;
	op1 = optonumber(mat[r][c].op1, mat);
	if (mat[r][c].op){
		op2 = optonumber(mat[r][c].op2, mat);
		if (mat[r][c].op == '+') op1 = op1 + op2;
		else if (mat[r][c].op == '-') op1 = op1 - op2;
		else if (mat[r][c].op == '*') op1 = op1*op2;
		else  op1 = op1 / op2;
	}
	if (print) printf(">%d\n", op1);
	else  return op1;
	return 0;
	/*int r, c;
	int ind = 0;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	r = str[ind++] - 'a';
	c = str[ind++] - '0'-1;
	while (str[ind] != '\0'){
	if (str[ind] != ' ' )  return 1;
	ind++;
	}
	printf("%d\n>", mat[r][c]);
	return 0;*/
}
int print(char *str, struct node mat[10][10]){
	int ind = 0; char c[3];
	while (str[ind] != '\0'){
		if (str[ind] != ' ')  return 1;
		ind++;
	}
	printf("   :");
	for (int i = 0; i < 10; i++){
		printf(" %c :", i + 'A');
	}
	printf("\n");
	for (int i = 0; i < 10; i++){
		printf(" %d :", i + 1);
		for (int j = 0; j < 10; j++){
			c[0] = 'a' + j; c[1] = '1' + i; c[2] = '\0';
			printf(" %d :", get(c, mat, 0));
		}
		printf("\n");
	}
	return 0;
}
void getformula(char *formula, struct node mat[10][10], int r, int c){
	formula[0] = '\0';
	if (mat[r][c].op){
		char *s = (char *)malloc(sizeof(char) * 2);
		strcat(formula, mat[r][c].op1);
		s[0] = mat[r][c].op;
		s[1] = '\0';
		strcat(formula, s);
		strcat(formula, mat[r][c].op2);
	}
	else{
		strcat(formula, mat[r][c].op1);
	}
}
int export(char *str, struct node mat[10][10], char *storefilename){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
		if (str[ind] == '.') csvpres = 1;
		buf[bufind++] = str[ind++];
	}
	if (!csvpres){
		strcat(buf, ".csv");
	}
	buf[bufind] = '\0';
	fptr = fopen(buf, "w");
	strcpy(storefilename, buf);
	char formula[50];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			getformula(formula, mat, i, j);
			fprintf(fptr, "%s ,", formula);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}
int import(char *str, struct node mat[10][10]){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
		if (str[ind] == '.') csvpres = 1;
		buf[bufind++] = str[ind++];
	}
	if (!csvpres){
		strcat(buf, ".csv");
	}
	buf[bufind] = '\0';
	fptr = fopen(buf, "r");
	char formula[50], cell[50];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			formula[0] = j + 'a';
			formula[1] = i + '1';
			formula[2] = '=';
			formula[3] = '\0';
			fscanf(fptr, "%s ,", cell);
			strcat(formula, cell);
			set(formula, mat);
		}
		fscanf(fptr, "\n");
	}
	fclose(fptr);
}
int main(){
	struct node mat[10][10];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			mat[i][j].op1[0] = '0';
			mat[i][j].op1[1] = '\0';
			mat[i][j].op = '\0';
			mat[i][j].op2[0] = '\0';
		}
	}
	char inp[50], storefilename[50];
	storefilename[0] = '\0';
	printf(">");
	fflush(stdin);
	scanf("%[^\n]", inp);
	lower(inp);
	unordered_set<string> stringset;
	while (1){
		if (!strncmp(inp, "set", 3)){
			if (validate(&inp[3], mat, stringset)){
				printf("loop detected, enter valid formula\n>");
			}
			else if (set(&inp[3], mat)){
				printf("invalid command format\n>");
			}
		}
		else if (!strncmp(inp, "get", 3)){
			if (get(&inp[3], mat, 1)){
				printf("invalid command format\n>");
			}
		}
		else if (!strncmp(inp, "print", 5)){
			if (print(&inp[5], mat)){
				printf("invalid command format\n>");
			}
		}
		else if (!strncmp(inp, "import", 6)){
			if (import(&inp[6], mat)){
				printf("invalid command format\n");
			}
		}
		else if (!strncmp(inp, "export", 6)){
			if (export(&inp[6], mat, storefilename)){
				printf("invalid command format\n>");
			}
		}
		else if (!strncmp(inp, "save", 4)){
			if (storefilename[0] == '\0'){
				printf("save with a filename\n>");
			}
			else{
				export(storefilename, mat, storefilename);
			}
		}
		else if (!strncmp(inp, "exit", 4)){
			exit(0);
		}
		else{
			printf("invalid command\n>");
		}
		printf(">");
		fflush(stdin);
		scanf("%[^\n]", inp);
	}
}
