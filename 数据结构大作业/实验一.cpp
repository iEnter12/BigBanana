#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct node {
	int num;
	struct node* nxt;
}node, * Linklist;

Linklist Create(int n) {
	Linklist L = (Linklist)malloc(sizeof(node));
	if (!L)exit(1);//������ʧ���򷵻�
	L->nxt = L;    //����ѭ��
	L->num = 0;
	Linklist p, q = L;
	p = L;
	int i;
	// β�巨 
	for (i = 1; i <= n; i++) {
		p = (Linklist)malloc(sizeof(node));
		p->num = i;
		q->nxt = p;
		q = p;
	}
	q->nxt = L;//ѭ���������㻷�β��� 
	return L;//����ͷ��� 
}

void Delete(int n, int m, Linklist& L) {
	int i;
	Linklist p = L->nxt;
	while (1) {
		//�ҵ�Ӧ�ó�Ȧ��ǰһ���� 
		for (i = 1; i < m - 1; i++) {
			p = p->nxt;
			//��ѭ����ͷ���Ӧ���� 
			if (p == L) {
				p = p->nxt;
			}
		}
		Linklist q;
		if (p->nxt == L)p = p->nxt;//��һ��Ϊͷ��㣬��Pָ��ͷ��� 
		if (p->nxt == L)return;//��ʱֻ��һ��ͷ��㣬����ѭ�� 
		printf("the number is %d\n", p->nxt->num);
		q = p->nxt;
		p->nxt = q->nxt;
		p = q->nxt;//��ɾ������һ���ڵ����	
		if (p == L)p = p->nxt;//��ͷ�������� 
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