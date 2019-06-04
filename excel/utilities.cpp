#include<stdio.h>
#include<stdlib.h>
#include "utilities.h"
int emptystack(char *post, int postind, char *stack, int *top){
	while (*top > -1){
		post[postind++] = stack[(*top)--];
	}
	return postind;
}
int pushaddition(char *post, int postind, char *stack, int *top){
	while (*top > -1 && stack[*top] != '('){
		post[postind++] = stack[(*top)--];
	}
	stack[++(*top)] = '+';
	return postind;
}
char *infixtopostfix(char *inp){
	char *post = (char *)malloc(sizeof(char) * 50);
	char *stack = (char *)malloc(sizeof(char) * 50);
	int postind = 0, top = -1;
	int ind = 0;
	while (inp[ind]){
		if (inp[ind] == '('){
			stack[++top] = '(';
			ind++;
		}
		else if (inp[ind] == ')'){
			while (stack[top] != '('){
				post[postind++] = stack[top--];
			}
			top--;
			ind++;
		}
		else if (inp[ind] == '+' || inp[ind] == '-'){
			postind = pushaddition(post, postind, stack, &top);
			ind++;
		}
		else if (inp[ind] == '*' || inp[ind] == '/' || inp[ind] == '%'){
			stack[++top] = inp[ind];
			ind++;
		}
		else{
			post[postind++] = inp[ind++];
		}
	}
	postind=emptystack(post, postind, stack, &top);
	post[postind] = '\0';
	free(stack);
	return post;
}
//struct token *createtoken(char *inp){
//	struct token *temp = (struct token *)malloc(sizeof(struct token));
//	strcpy(temp->str, inp);
//	temp->next = NULL;
//	return temp;
//}
//int givenexttoken(char *inp, int ind, char *token){
//	int tokenind = 0;
//	int id = 0;
//	while (inp[ind]){
//		if ( (inp[ind] >= 'a' && inp[ind] <= 'z') || (inp[ind] <= '9' && inp[ind] >= '0')){
//			id = 1;
//			token[tokenind++] = inp[ind];
//		}
//		else if (id == 1){
//			token[tokenind] = '\0';
//			return ind;
//		}
//		else{
//			token[tokenind++] = inp[ind++];
//			token[tokenind] = '\0';
//			return ind;
//		}
//		ind++;
//	}
//
//}
//struct token *createexpression(char *inp){
//	int ind = 0;
//	char *token = (char *)malloc(sizeof(char) * 5);
//	while (inp[ind]){
//		ind=givenexttoken(inp,ind,token);
//
//	}
//}