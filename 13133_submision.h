#include <stdlib.h>

typedef struct node {
	struct node* next;
	int val;
} Node;

void createLinkedList(Node **head, int N, int *arr){
	Node *tmp = (Node *)malloc(sizeof(Node)*(N+1));
	*head = &tmp[1];
	
	for (int i = 1; i <= N; i++){
		tmp[i].val = arr[i];
		tmp[i].next = NULL;
		if (i != N)
			tmp[i].next = &tmp[i+1];
		else if (i==N)
			tmp[i].next = &tmp[1];
	}
	return;
}

void swapTwoSegment(Node **head, int a, int b, int len){
	
	a -= 1; //the nuber of intervals to move
	b -= 1;

	if (a == 0)
		a += 6;
	else if (b==0)
		b += 6;

	Node *p = NULL, *q=NULL, *r=NULL, *s=NULL;
	//p, q are our targets to switch. r, s are the previous node for p and q respectively
	p = q = r = s = *head;
	
		for (int i = 1; i < a; i++)
		{
			r = r->next;
		}
		p = r->next;
	
		for (int i = 1; i < b; i++) 
			s = s->next;
		q = s->next;

	for (int j = 0; j < len; j++)
	{
		if (j>0){
			r = r->next;
			p = r->next;
			s = s->next;
			q = s->next;
		}
		

		if (*head ==p )
			*head = q;
		else if (*head ==q)
			*head = p;


		//update link
		Node *tmp;
		tmp = p->next;
		p->next = q->next;
		q->next = tmp;

		tmp = r->next;
		r->next = s->next;
		s->next = tmp;

	}
	return;
}
