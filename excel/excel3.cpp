#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utilities.h"
struct node{
	char str[50];
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
int eval(char *inp, struct node mat[10][10], char *par){
	char *post = infixtopostfix(inp);
	int postind = 0, stack[50], top = -1;
	int intbuf = 0, strbufind = 0, r, c;
	char strbuf[5];
	while (post[postind]){
		if (post[postind] <= '9' &&  post[postind] >= '0'){
			intbuf = 0;
			while (post[postind] <= '9' &&  post[postind] >= '0'){
				intbuf = intbuf * 10 + post[postind++] - '0';
			}
			stack[++top] = intbuf;
		}
		else if (post[postind] == '+'){
			stack[top - 1] = stack[top - 1] + stack[top];
			top--;
			postind++;
		}
		else if (post[postind] == '-'){
			stack[top - 1] = stack[top - 1] - stack[top];
			top--;
			postind++;
		}
		else if (post[postind] == '*'){
			stack[top - 1] = stack[top - 1] * stack[top];
			top--;
			postind++;
		}
		else if (post[postind] == '/'){
			stack[top - 1] = stack[top - 1] / stack[top];
			top--;
			postind++;
		}
		else if (post[postind] == '%'){
			stack[top - 1] = stack[top - 1] % stack[top];
			top--;
			postind++;
		}
		else if (post[postind] <= 'z' && post[postind] >= 'a'){
			strbuf[0] = post[postind];
			strbuf[1] = post[postind + 1];
			strbuf[2] = '\0';
			if (par && !strcmp(strbuf, par)) return -1;
			c = post[postind++] - 'a';
			r = post[postind++] - '1';
			if ((intbuf = eval(mat[r][c].str, mat, par)) == -1){
				return -1;
			}
			else{
				stack[++top] = intbuf;
			}
		}
	}
	return stack[0];
}
int set(char *str, struct node mat[10][10],int isstr){
	int r, c, ind = 0, operind = 0;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	c = str[ind++] - 'a';
	r = str[ind++] - '1';
	if (str[ind++] != '=')  return 1;
	str[ind - 1] = '\0';
	if (isstr){
		strcpy(mat[r][c].str, &str[ind]);
	}
	else if (eval(&str[ind], mat, &str[ind - 3]) == -1){
		printf("invalid assignment\n>");
	}
	else{
		strcpy(mat[r][c].str, &str[ind]);
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
//int optonumber(char *str, struct node mat[10][10]){
//	int r, c;
//	if (str[0] >= 'a' && str[0] <= 'j'){
//		c = str[0] - 'a';
//		r = str[1] - '1';
//		return optonumber(mat[r][c].op1, mat);
//	}
//	int number = 0, ind = 0;
//	while (str[ind] != '\0'){
//		number = number * 10 + str[ind] - '0';
//		ind++;
//	}
//	return number;
//}
int get(char *str, struct node mat[10][10],int *header,char *outbuf){
	int r, c;
	int ind = 0;
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	c = str[ind++] - 'a';
	r = str[ind++] - '1';
	if (*header){
		if (r == 0 || c==1){
			outbuf[0] = '\0';
			strcpy(outbuf, mat[r][c].str);
			return -1;
		}
		else {
			return eval(mat[r][c].str, mat, NULL);
		}
	}
	else {
		if (c == 1){
			outbuf[0] = '\0';
			strcpy(outbuf, mat[r][c].str);
			return -1;
		}
		else{
			return eval(mat[r][c].str, mat, NULL);
		}
	}
	/*int op1, op2;
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
			printf(" %d :", eval(c, mat, NULL));
		}
		printf("\n");
	}
	return 0;
}
//void getformula(char *formula, struct node mat[10][10], int r, int c){
//	formula[0] = '\0';
//	if (mat[r][c].op){
//		char *s = (char *)malloc(sizeof(char) * 2);
//		strcat(formula, mat[r][c].op1);
//		s[0] = mat[r][c].op;
//		s[1] = '\0';
//		strcat(formula, s);
//		strcat(formula, mat[r][c].op2);
//	}
//	else{
//		strcat(formula, mat[r][c].op1);
//	}
//}
int export(char *str, struct node mat[10][10], char *storefilename){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
		if (str[ind] == '.') csvpres = 1;
		buf[bufind++] = str[ind++];
	}
	buf[bufind] = '\0';
	if (!csvpres){
		strcat(buf, ".csv");
		bufind += 4;
	}

	fptr = fopen(buf, "w");
	strcpy(storefilename, buf);
	char formula[50];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			//getformula(formula, mat, i, j);
			fprintf(fptr, "%s,", mat[i][j].str);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	return 0;
}
int import(char *str, struct node mat[10][10], char *storefilename,int *header){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'a' || str[ind]>'j')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
		if (str[ind] == '.') csvpres = 1;
		buf[bufind++] = str[ind++];
	}
	buf[bufind] = '\0';
	if (!csvpres){
		strcat(buf, ".csv");
	}
	fptr = fopen(buf, "r");
	strcpy(storefilename, buf);

	bufind = 0;
	while (str[ind]<'a' || str[ind]>'z')  ind++;
	while (str[ind] == '=' || (str[ind] >= 'a' && str[ind] <= 'z') ){
		buf[bufind++] = str[ind++];
	}
	buf[bufind] = '\0';
	if (!strcmp(buf, "header=true")) *header = 1;
	else *header = 0;

	char formula[50], cell[50];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			fscanf(fptr, "%s,", cell);
			if (!(*header)){
				if (i == 0) continue;
				formula[1] = i + '1'-1;
			}
			else{
				formula[1] = i + '1' ;
			}
			formula[0] = j + 'a';
			formula[2] = '=';
			formula[3] = '\0';
			strcat(formula, cell);
			set(formula, mat, (i == 0 || j == 1) ? 1 : 0);
		}
		fscanf(fptr, "\n");
	}
	fclose(fptr);
	return 0;
}
int main(){
	struct node mat[10][10];
	int header = 0,hold;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			mat[i][j].str[0] = '0';
			mat[i][j].str[1] = '\0';
		}
	}
	char inp[50], storefilename[50],out[50];
	storefilename[0] = '\0';
	printf(">");
	fflush(stdin);
	scanf("%[^\n]", inp);
	lower(inp);
	while (1){
		if (!strncmp(inp, "set", 3)){
			if (set(&inp[3], mat,0)){
				printf("invalid command format\n");
			}
		}
		else if (!strncmp(inp, "get", 3)){
			hold = get(&inp[3], mat, &header, out);
			if (hold==-1){ 
				printf("%s\n>", out); 
			}
			else printf("%d\n>", hold);
		}
		else if (!strncmp(inp, "print", 5)){
			if (print(&inp[5], mat)){
				printf("invalid command format\n");
			}
		}
		else if (!strncmp(inp, "import", 6)){
			import(&inp[6], mat, storefilename,&header);
		}
		else if (!strncmp(inp, "export", 6)){
			export(&inp[6], mat, storefilename);
		}
		else if (!strncmp(inp, "save", 4)){
			if (storefilename[0] == '\0'){
				printf("first export or import with a filename\n");
			}
			else{
				export(storefilename, mat, storefilename);
			}
		}
		else if (!strncmp(inp, "eval", 4)){
			printf("%d\n", eval(&inp[5], mat, NULL));
		}
		else if (!strncmp(inp, "exit", 4)){
			exit(0);
		}
		else{
			printf("invalid command\n");
		}
		printf(">");
		fflush(stdin);
		scanf("%[^\n]", inp);
	}
}