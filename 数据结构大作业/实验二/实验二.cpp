#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 50
#define OK 1
#define ERROR 0

typedef struct {
	char base[MAXSIZE];
	int top;
	int size;
}SqStack;

typedef struct {
	int base[MAXSIZE];
	int top;
	int size;
}NStack;

void InitStack(SqStack& S) {
	S.top = 0;
	S.size = 0;
}

bool isEmpty(SqStack& S) {
	return S.size == 0;
}

bool isFull(SqStack& S) {
	return S.size == MAXSIZE;
}

int Push(SqStack& S, char str) {
	if (isFull(S)) {
		printf("stack already full\n");
		return ERROR;
	}
	S.top++;
	S.size++;
	S.base[S.top] = str;
	return OK;
}

int Pop(SqStack& S, char& str) {
	if (isEmpty(S)) {
		printf("stack already empty\n");
		return ERROR;
	}
	str = S.base[S.top];
	S.top--;
	S.size--;
	return OK;
}

char GetTop(SqStack& S) {
	if (isEmpty(S)) {
		printf("stack already empty");
		return ERROR;
	}
	return S.base[S.top];
}

//int���͵�ջ
void InitStack_N(NStack& S) {
	S.top = 0;
	S.size = 0;
}

bool isEmpty_N(NStack& S) {
	return S.size == 0;
}

bool isFull_N(NStack& S) {
	return S.size == MAXSIZE;
}

int Push_N(NStack& S, int num) {
	if (isFull_N(S)) {
		printf("stack already full\n");
		return ERROR;
	}
	S.top++;
	S.size++;
	S.base[S.top] = num;
	return OK;
}

int Pop_N(NStack& S, int& num) {
	if (isEmpty_N(S)) {
		printf("stack already empty\n");
		return ERROR;
	}
	num = S.base[S.top];
	S.top--;
	S.size--;
	return OK;
}

int GetTop_N(NStack& S) {
	if (isEmpty_N(S)) {
		printf("stack already empty");
		return ERROR;
	}
	return S.base[S.top];
}

void Copy(NStack& S1, NStack& S2) {
	S2.size = S1.size;
	S2.top = S1.top;
	for (int i = 1; i <= S1.top; i++)
		S2.base[i] = S1.base[i];
}
//ת��Ϊ��׺���ʽ
void TransPost(SqStack& S, char* p) {
	char a[MAXSIZE], c;
	int count = 0;//p�ļ�����
	scanf("%s", a);
	for (int i = 0; i < strlen(a); i++) {
		int temp = 0, j = 0, flag = 1;
		while (a[i] >= '0' && a[i] <= '9') {//��ȡһ����λ��
			flag *= 10, i++, j++;
		}
		for (int k = i - j; k < i; k++) {
			flag /= 10;
			temp += (a[k] - '0') * flag;
			p[count++] = a[k];
		}
		if (j != 0) {//��j��Ϊ0����˵����ȡ��һ������ֱ�����������洢
			printf("%d ", temp);
			p[count++] = ' ';//�������ÿո�������������
		}

		if (a[i] == '(') {//������ֱ����ջ
			Push(S, a[i]);
		}

		if (a[i] == '+' || a[i] == '-') {
			while (!isEmpty(S) && GetTop(S) != '(') {//��ջ��Ϊ���������ȼ��ߵģ���һֱ��ջ��ֱ��ջ�ջ��������Լ��ͼ���
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Push(S, a[i]);
		}

		if (a[i] == ')') {
			while (GetTop(S) != '(') {//��û���������ţ���һֱ��ջ
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Pop(S, c);
		}

		if (a[i] == '*' || a[i] == '/') {
			while (!isEmpty(S) && GetTop(S) != '(' && GetTop(S) != '+' && GetTop(S) != '-') {//ͬ�ϼӼ�
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Push(S, a[i]);
		}
	}
	while (!isEmpty(S)) {//��ʣ�µķ������
		Pop(S, c);
		if (c != '(') {//�����Ų����
			printf("%c ", c);
			p[count++] = c;
		}
	}
	printf("\n");
	p[count] = '\0';
}

//��׺���ʽ��ֵ
void CalPost(NStack& S, char* p) {
	int n1, n2;
	for (int i = 0; i < strlen(p); i++) {
		int temp = 0, j = 0, flag = 1;
		while (p[i] >= '0' && p[i] <= '9') {//��ȡһ����λ��
			flag *= 10, i++, j++;
		}
		for (int k = i - j; k < i; k++) {
			flag /= 10;
			temp += (p[k] - '0') * flag;
		}
		if (j != 0)Push_N(S, temp);//��j������0����֤��������һ������temp��ջ
		
		switch (p[i]) {
		    case '+': 
			    Pop_N(S, n2);
			    Pop_N(S, n1);
				Push_N(S, n1 + n2);
				break;
			case '-':
				Pop_N(S, n2);
				Pop_N(S, n1);
				Push_N(S, n1 - n2);
				break;
			case '*':
				Pop_N(S, n2);
				Pop_N(S, n1);
				Push_N(S, n1 * n2);
				break;
			case '/':
				Pop_N(S, n2);
				Pop_N(S, n1);
				Push_N(S, n1 / n2);
				break;
			case ' ':
				continue;
		}
	}
	printf("��׺���ʽ���Ϊ��%d ", GetTop_N(S));
}

NStack TransPre(SqStack& S1, NStack& S2, char* p) {
	char a[MAXSIZE], c;
	int count = 0;//p�ļ�����
	scanf("%s", a);
	for (int i = strlen(a) - 1; i >= 0; i--) {
		int temp = 0, j = 0, flag = 1;
		while (a[i] >= '0' && a[i] <= '9') {//��ȡһ����λ��
			flag *= 10, i--, j++;
		}
		for (int k = i + 1; k <= i + j; k++) {
			flag /= 10;
			temp += (a[k] - '0') * flag;
		}
		if (j != 0) {//��j��Ϊ0����˵����ȡ��һ����������洢
			Push_N(S2, temp);
		}

		if (a[i] == ')') {//������ֱ����ջ
			Push(S1, a[i]);
		}

		if (a[i] == '+' || a[i] == '-') {
			while (!isEmpty(S1) && GetTop(S1) != ')') {//��ջ��Ϊ���������ȼ��ߵģ���һֱ��ջ��ֱ��ջ�ջ��������Լ��ͼ���
				Pop(S1, c);
				if (c == '+')Push_N(S2, -1);
				else if (c == '-')Push_N(S2, -2);
				else if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Push(S1, a[i]);
		}

		if (a[i] == '(') {
			while (GetTop(S1) != ')') {//��û���������ţ���һֱ��ջ
				Pop(S1, c);
				if (c == '+')Push_N(S2, -1);
				else if (c == '-')Push_N(S2, -2);
				else if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Pop(S1, c);
		}

		if (a[i] == '*' || a[i] == '/') {
			while (!isEmpty(S1) && GetTop(S1) != ')' && GetTop(S1) != '+' && GetTop(S1) != '-') {//ͬ�ϼӼ�
				Pop(S1, c);
				if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Push(S1, a[i]);
		}
	}
	while (!isEmpty(S1)) {//��ʣ�µķ������
		Pop(S1, c);
		if (c != ')') {//�����Ų����
			if (c == '+')Push_N(S2, -1);
			else if (c == '-')Push_N(S2, -2);
			else if (c == '*')Push_N(S2, -3);
			else if (c == '/')Push_N(S2, -4);
		}
	}
	NStack S_Cal;
	InitStack_N(S_Cal);
	while (!isEmpty_N(S2)) {
		int n;
		Pop_N(S2, n);
		Push_N(S_Cal, n);
		if (n == -1)printf("+ ");
		else if (n == -2)printf("- ");
		else if (n == -3)printf("* ");
		else if (n == -4)printf("/ ");
		else printf("%d ", n);
	}
	printf("\n");
	return S_Cal;	
}

void CalPre(NStack& NS) {
	NStack S1;
	InitStack_N(S1);
	int n1, n2;
	while (!isEmpty_N(NS)) {
		int n;
		Pop_N(NS, n);
		if (n == -1) {
			Pop_N(S1, n2);
			Pop_N(S1, n1);
			Push_N(S1, n1 + n2);
		}
		else if (n == -2) {
			Pop_N(S1, n1);
			Pop_N(S1, n2);
			Push_N(S1, n1 - n2);
		}
		else if (n == -3) {
			Pop_N(S1, n2);
			Pop_N(S1, n1);
			Push_N(S1, n1 * n2);
		}
		else if (n == -4) {
			Pop_N(S1, n1);
			Pop_N(S1, n2);
			Push_N(S1, n1 / n2);
		}
		else
			Push_N(S1, n);
	}
	printf("ǰ׺���ʽ���Ϊ��%d ", GetTop_N(S1));
}

int main() {
	SqStack S;
	NStack NS;
	InitStack(S);
	InitStack_N(NS);
	char p[MAXSIZE];
	printf("��������׺���ʽ��\n");
	TransPost(S, p);
	CalPost(NS, p);
	printf("��������׺���ʽ��\n");
	InitStack(S);
	InitStack_N(NS);
	NStack S_CAL = TransPre(S, NS, p);
	CalPre(S_CAL);
}