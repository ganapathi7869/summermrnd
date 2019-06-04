#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *next;
};
struct node *createnode(int val){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->val = val;
	temp->next = NULL;
	return temp;
}
struct node *createtestcase(){
	struct node *head = createnode(1);
	head->next = createnode(2);
	head->next->next = createnode(3);
	head->next->next->next = createnode(4);
	head->next->next->next->next = createnode(5);
	head->next->next->next->next->next = head->next;
	return head;
}
struct node *detectloopnode(struct node *head){
	struct node *slow = head, *fast = head;
	if (!head->next)  return NULL;
	if (!head->next->next)  return NULL;
	slow = head->next;
	fast = head->next->next;
	while (slow != fast){
		if (!fast->next || !fast->next->next)  return NULL;
		slow = slow->next;
		fast = fast->next->next;
	}
	while (head != slow){
		head = head->next;
		slow = slow->next;
	}
	return head;
}
int main(){
	struct node *head = createtestcase();
	struct node *temp = detectloopnode(head);
	printf("loop starting node is:\n%d", temp->val);
	return 0;
}
