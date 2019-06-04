#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *next;
	struct node *rand;
};
struct node *createnode(int val){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->val = val;
	temp->next = NULL;
	temp->rand = NULL;
	return temp;
}
struct node *createstcase(){
	struct node *head=createnode(1);
	head->next = createnode(2);
	head->next->next = createnode(3);
	head->next->next->next = createnode(4);
	head->next->next->rand = head;
	head->next->rand = head->next->next->next;
	return head;
}
struct node *clone(struct node *head){
	if (!head) return NULL;
	struct node *temp = head;
	struct node *clone;
	while (temp){
		clone = createnode(temp->val);
		clone->next = temp->next;
		temp->next = clone;
		temp = clone->next;
	}
	temp = head;
	struct node *clonehead = temp->next,*prev=NULL;
	while (temp){
		if (temp->rand){
			temp->next->rand = temp->rand->next;
		}
		if (prev){
			prev->next = temp->next;
			temp->next = temp->next->next;
			temp = temp->next;
			prev = prev->next;
		}
		else{
			prev = temp->next;
			temp->next = temp->next->next;
			temp = temp->next;
		}
	}
	return clonehead;
}
void printlist(struct node *head){
	printf("elem : random\n");
	struct node *temp = head;
	while (temp){
		if (temp->rand)  printf("%d    : %d\n", temp->val,temp->rand->val);
		else             printf("%d    :\n", temp->val);
		temp = temp->next;
	}
}
int main(){
	struct node *head = createstcase();
	struct node *clonehead = clone(head);
	printlist(clonehead);
	return 0;
}
