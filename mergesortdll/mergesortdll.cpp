#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *prev;
	struct node *next;
};
struct node *createnode(int val){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->val = val;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}
struct node *createtestcase(){
	struct node *head = createnode(1);
	head->next = createnode(2);
	head->next->prev = head;
	head->next->next = createnode(3);
	head->next->next->prev = head->next;
	head->next->next->next = createnode(4);
	head->next->next->next->prev = head->next->next;
	return head;
}
void printlist(struct node *head){
	while (head){
		printf("%d ", head->val);
		head = head->next;
	}
}
struct node *merge(struct node *head1, struct node *head2){
	struct node *head = NULL,*last=NULL;
	int sw;
	if (head1->val < head2->val){
		head = head1;
		last = head1;
		head1 = head1->next;
		sw = 1;
	}
	else {
		head = head2;
		last = head2;
		head2 = head2->next;
		sw = 2;
	}
	while (head1 && head2){
		if (sw == 1){
			if (head1->val < head2->val){
				last = last->next;
				head1 = head1->next;
			}
			else{

			}
		}
	}
}
struct node *mergesort(struct node *head){
	struct node *slow = head, *fast = head;
	while (fast && fast->next){
		fast = fast->next->next;
		slow = slow->next;
	}
	if (!slow->prev) return head;
	slow->prev->next = NULL;
	slow->prev = NULL;
	head=mergesort(head);
	slow = mergesort(slow);
	head=merge(head, slow);
	return head;
}
int main(){
	struct node *head = createtestcase();
	head=mergesort(head);
	printlist(head);
	return 0;
}
