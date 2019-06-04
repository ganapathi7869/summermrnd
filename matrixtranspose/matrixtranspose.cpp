#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *next;
};
struct node * createnode(int val){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->val = val;
	temp->next = NULL;
	return temp;
}
struct node *createtestlist(int *list, int len){
	struct node *head = createnode(list[0]);
	struct node *temp=head;
	for (int i = 1; i < len; i++){
		temp->next = createnode(list[i]);
		temp = temp->next;
	}
	return head;
}
struct node *cutoutknodes(struct node *head, int k,int *c){
	int i = 0;
	while (head){
		i++;
		if (i == k) {
			struct node *temp = head->next;
			head->next = NULL;
			*c = k;
			return temp;
		}
		head = head->next;
	}
	*c = i;
	return NULL;
}
struct node *reverse(struct node *head){
	if (!head)  return NULL;
	struct node *prev=NULL,*temp=head;
	while (temp){
		head = temp->next;
		temp->next = prev;
		prev = temp;
		temp = head;
	}
	return prev;
}
void printlist(struct node *head){
	while (head){
		printf("%d ", head->val);
		head = head->next;
	}
}
int main(){
	int list[] = { 1, 2, 3, 4, 5, 6, 7, 8 },k,c;
	struct node *newhead = NULL, *connector = NULL, *uvlist = createtestlist(list, sizeof(list) / sizeof(int)),*newuvlist,*reversedhead;
	scanf("%d", &k);
	while (uvlist){
		newuvlist = cutoutknodes(uvlist, k,&c);
		if (c==k){
			reversedhead=reverse(uvlist);
			if (connector){
				connector->next = reversedhead;
				connector = uvlist;
			}
			else{
				newhead = reversedhead;
				connector = uvlist;
			}
			uvlist = newuvlist; continue;
		}
		connector->next = uvlist;
		break;
	}
	printlist(newhead);
	return 0;
}
