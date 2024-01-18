#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node {
	int num;
	struct node* nxt;
}node, * Linklist;

Linklist Create(int n) {
	Linklist L = (Linklist)malloc(sizeof(node));
	if (!L)exit(1);//若创建失败则返回
	L->nxt = L;    //自身循环
	L->num = 0;
	Linklist p, q = L;
	p = L;
	int i;
	// 尾插法 
	for (i = 1; i <= n; i++) {
		p = (Linklist)malloc(sizeof(node));
		p->num = i;
		q->nxt = p;
		q = p;
	}
	q->nxt = L;//循环链表，方便环形查找 
	return L;//返回头结点 
}

void Delete(int n, int m, Linklist& L) {
	int i;
	Linklist p = L->nxt;
	while (1) {
		//找到应该出圈的前一个人 
		for (i = 1; i < m - 1; i++) {
			p = p->nxt;
			//若循环到头结点应跳过 
			if (p == L) {
				p = p->nxt;
			}
		}
		Linklist q;
		if (p->nxt == L)p = p->nxt;//下一个为头结点，则P指向头结点 
		if (p->nxt == L)return;//此时只有一个头结点，结束循环 
		printf("the number is %d\n", p->nxt->num);
		q = p->nxt;
		p->nxt = q->nxt;
		p = q->nxt;//从删除的下一个节点出发	
		if (p == L)p = p->nxt;//到头结点就跳过 
		free(q);
	}
}

int main() {
	printf("please input num and password:");
	int n, m;
	scanf_s("%d%d", &n, &m);
	if (m <= 0 || n <= 0) {
		printf("invalid input\n");
		return 0;
	}
	Linklist L1 = Create(n);
	int i;
	for (i = 1; i <= n; i++)Delete(n, m, L1);
	return 0;
}