#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
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
int eval(char *inp, struct node mat[9][10], char *par){
	char *post = infixtopostfix(inp);
	int postind = 0, stack[50], top = -1;
	int intbuf = 0, strbufind = 0, r, c;
	char strbuf[10];
	while (post[postind]){
		if (post[postind] == ','){
			postind++;
			if (post[postind] <= '9' &&  post[postind] >= '0'){
				intbuf = 0;
				while (post[postind] <= '9' &&  post[postind] >= '0'){
					intbuf = intbuf * 10 + post[postind++] - '0';
				}
				stack[++top] = intbuf;
			}
			else if (post[postind] <= 'J' && post[postind] >= 'A'){
				strbuf[0] = post[postind];
				strbuf[1] = post[postind + 1];
				strbuf[2] = '\0';
				if (par && !strcmp(strbuf, par)) return -1;
				c = post[postind++] - 'A';
				r = post[postind++] - '1';
				if ((intbuf = eval(mat[r][c].str, mat, par)) == -1){
					return -1;
				}
				else{
					stack[++top] = intbuf;
				}
			}
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
		
	}
	return stack[0];
}
int set(char *str, struct node mat[9][10]){
	int r, c, ind = 0;
	while (str[ind]<'A' || str[ind]>'J' )  ind++;
	c = str[ind++] - 'A';
	r = str[ind++] - '1';
	if (str[ind++] != '=')  return 1;
	str[ind - 1] = '\0';
	if (str[ind] == '"'){
		strcpy(mat[r][c].str, &str[ind]);
	}
	else if (eval(&str[ind], mat, &str[ind - 3]) == -1){
		printf("invalid assignment\n");
	}
	else{
		strcpy(mat[r][c].str, &str[ind]);
	}
	return 0;
	
}

int get(char *str, struct node mat[9][10], char *outbuf){
	int r, c;
	int ind = 0;
	while (str[ind]<'A' || str[ind]>'J')  ind++;
	c = str[ind++] - 'A';
	r = str[ind++] - '1';
	if (mat[r][c].str[0]=='"'){
		outbuf[0] = '\0';
		strcpy(outbuf, mat[r][c].str);
		return -1;
	}
	return eval(mat[r][c].str, mat, NULL);
}
int print(char *str, struct node mat[9][10]){
	int ind = 0; char c[3];
	while (str[ind] != '\0'){
		if (str[ind] != ' ')  return 1;
		ind++;
	}
	printf("           ");  //11 spaces
	for (int i = 0; i < 10; i++){       /***********************************/
		printf("%10c:", i + 'A');
	}
	printf("\n");
	for (int i = 0; i < 11; i++){       /***********************************/
		printf("___________", i + 'A');   //11 _
	}
	printf("\n");
	for (int i = 0; i < 9; i++){
		printf("%10d|", i + 1);
		for (int j = 0; j < 10; j++){
			printf("%10s|", mat[i][j].str);
		}
		printf("\n");
	}
	return 0;
}
float avg(char col, struct node mat[9][10], int *header){
	int r, c = col - 'A';
	float sum = 0, n = 0;
	char str[5];
	str[0] = col;
	str[2] = '\0';

	if (!(*header)) r = 0;
	else r = 1;
	if (mat[r][c].str[0] == '"')  return -1;
	for (; r < 8; r++){
		str[1] = r + '1';
		sum += eval(str, mat, NULL);
		n += 1;
	}
	return sum / n;
}
int min(char col, struct node mat[9][10], int *header){
	int r, c = col - 'A';
	int min = INT_MAX,hold;
	char str[5];
	str[0] = col;
	str[2] = '\0';

	if (!(*header)) r = 0;
	else r = 1;
	if (mat[r][c].str[0] == '"')  return -1;
	for (; r < 8; r++){
		str[1] = r + '1';
		hold = eval(str, mat, NULL);
		if (hold < min) min = hold;
	}
	return min;
}
int max(char col, struct node mat[9][10], int *header){
	int r, c = col - 'A';
	int max = INT_MIN, hold;
	char str[5];
	str[0] = col;
	str[2] = '\0';

	if (!(*header)) r = 0;
	else r = 1;
	if (mat[r][c].str[0] == '"')  return -1;
	for (; r < 8; r++){
		str[1] = r + '1';
		hold = eval(str, mat, NULL);
		if (hold > max) max = hold;
	}
	return max;
}
int export(char *str, struct node mat[9][10], char *storefilename){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'A' || (str[ind]>'Z' && str[ind]<'a') || str[ind]>'z')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'A' && str[ind] <= 'Z') || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
		if (str[ind] == '.') csvpres = 1;
		buf[bufind++] = str[ind++];
	}
	buf[bufind] = '\0';
	if (!csvpres){
		strcat(buf, ".csv");
	}

	fptr = fopen(buf, "w");
	strcpy(storefilename, buf);
	char formula[50];
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 10; j++){
			//getformula(formula, mat, i, j);
			fprintf(fptr, "%s,", mat[i][j].str);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	return 0;
}
//student.csv
int import(char *str, struct node mat[9][10], char *storefilename, int *header){
	FILE *fptr;
	int ind = 0, bufind = 0, csvpres = 0;
	char buf[50];
	while (str[ind]<'A' || (str[ind]>'Z' && str[ind]<'a') || str[ind]>'z')  ind++;
	while (str[ind] == '.' || (str[ind] >= 'A' && str[ind] <= 'Z') || (str[ind] >= 'a' && str[ind] <= 'z') || (str[ind] >= '0' && str[ind] <= '9')){
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
	while (str[ind] == '=' || (str[ind] >= 'a' && str[ind] <= 'z')){
		buf[bufind++] = str[ind++];
	}
	buf[bufind] = '\0';
	if (!strcmp(buf, "header=true")) *header = 1;
	else *header = 0;

	char formula[50], cell[50];
	for (int i = 0; i < 9; i++){            /***********************************/
		for (int j = 0; j < 10; j++){
			fscanf(fptr, "%[^,\n]s,", cell);
			fscanf(fptr, ",");
			if (!(*header)){
				if (i == 0) continue;
				formula[1] = i + '1' - 1;
			}
			else{
				formula[1] = i + '1';
			}
			formula[0] = j + 'A';
			formula[2] = '=';
			formula[3] = '\0';
			strcat(formula, cell);
			set(formula, mat);
		}
		fscanf(fptr, "\n");
	}
	fclose(fptr);
	return 0;
}
int main(){
	struct node mat[9][10];
	int header = 0, hold;
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 10; j++){
			mat[i][j].str[0] = '0';
			mat[i][j].str[1] = '\0';
		}
	}
	char inp[50], storefilename[50], out[50];
	storefilename[0] = '\0';
	printf(">");
	fflush(stdin);
	scanf("%[^\n]", inp);
	while (1){
		//lower(inp);
		if (!strncmp(inp, "set", 3)){
			if (set(&inp[3], mat)){
				printf("invalid command format\n");
			}
		}
		else if (!strncmp(inp, "get", 3)){
			hold = get(&inp[3], mat, out);
			if (hold == -1){
				printf("%s\n", out);
			}
			else printf("%d\n", hold);
		}
		else if (!strncmp(inp, "print", 5)){
			if (print(&inp[5], mat)){
				printf("invalid command format\n");
			}
		}
		else if (!strncmp(inp, "import", 6)){
			import(&inp[6], mat, storefilename, &header);
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
		else if (!strncmp(inp, "avg(", 4)){
			float holdf = avg(inp[4],mat, &header);
			if (holdf == -1){
				printf("operation invalid!\n"); continue;
			}
			printf("%f\n",holdf);
		}
		else if (!strncmp(inp, "min(", 4)){
			hold = min(inp[4], mat, &header);
			if (hold == -1){
				printf("operation invalid!\n"); continue;
			}
			printf("%d\n", hold);
		}
		else if (!strncmp(inp, "max(", 4)){
			hold = max(inp[4], mat, &header);
			if (hold == -1){
				printf("operation invalid!\n"); continue;
			}
			printf("%d\n", hold);
		}
		else{
			printf("invalid command\n");
		}
		printf(">");
		fflush(stdin);
		scanf("%[^\n]", inp);
	}
}
//int get(char *str, struct node mat[9][10], int *header, char *outbuf){
//	int r, c;
//	int ind = 0;
//	while (str[ind]<'a' || str[ind]>'j')  ind++;
//	c = str[ind++] - 'a';
//	r = str[ind++] - '1';
//	if (*header){
//		if (r == 0 || c == 1){
//			outbuf[0] = '\0';
//			strcpy(outbuf, mat[r][c].str);
//			return -1;
//		}
//		else {
//			return eval(mat[r][c].str, mat, NULL);
//		}
//	}
//	else {
//		if (c == 1){           /***********************************/
//			outbuf[0] = '\0';
//			strcpy(outbuf, mat[r][c].str);
//			return -1;
//		}
//		else{
//			return eval(mat[r][c].str, mat, NULL);
//		}
//	}
//}