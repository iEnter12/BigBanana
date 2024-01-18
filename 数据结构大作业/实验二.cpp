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

//int类型的栈
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
//转换为后缀表达式
void TransPost(SqStack& S, char* p) {
	char a[MAXSIZE], c;
	int count = 0;//p的计数器
	scanf("%s", a);
	for (int i = 0; i < strlen(a); i++) {
		int temp = 0, j = 0, flag = 1;
		while (a[i] >= '0' && a[i] <= '9') {//获取一个多位数
			flag *= 10, i++, j++;
		}
		for (int k = i - j; k < i; k++) {
			flag /= 10;
			temp += (a[k] - '0') * flag;
			p[count++] = a[k];
		}
		if (j != 0) {//若j不为0，则说明读取了一个数，直接输出并将其存储
			printf("%d ", temp);
			p[count++] = ' ';//数后面用空格隔开，方便辨认
		}

		if (a[i] == '(') {//左括号直接入栈
			Push(S, a[i]);
		}

		if (a[i] == '+' || a[i] == '-') {
			while (!isEmpty(S) && GetTop(S) != '(') {//若栈顶为比自身优先级高的，则一直出栈，直到栈空或遇到比自己低级的
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Push(S, a[i]);
		}

		if (a[i] == ')') {
			while (GetTop(S) != '(') {//若没遇到左括号，则一直出栈
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Pop(S, c);
		}

		if (a[i] == '*' || a[i] == '/') {
			while (!isEmpty(S) && GetTop(S) != '(' && GetTop(S) != '+' && GetTop(S) != '-') {//同上加减
				Pop(S, c);
				printf("%c ", c);
				p[count++] = c;
			}
			Push(S, a[i]);
		}
	}
	while (!isEmpty(S)) {//把剩下的符号输出
		Pop(S, c);
		if (c != '(') {//左括号不输出
			printf("%c ", c);
			p[count++] = c;
		}
	}
	printf("\n");
	p[count] = '\0';
}

//后缀表达式求值
void CalPost(NStack& S, char* p) {
	int n1, n2;
	for (int i = 0; i < strlen(p); i++) {
		int temp = 0, j = 0, flag = 1;
		while (p[i] >= '0' && p[i] <= '9') {//获取一个多位数
			flag *= 10, i++, j++;
		}
		for (int k = i - j; k < i; k++) {
			flag /= 10;
			temp += (p[k] - '0') * flag;
		}
		if (j != 0)Push_N(S, temp);//若j不等于0，则证明读入了一个数，temp入栈
		
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
	printf("后缀表达式结果为：%d ", GetTop_N(S));
}

NStack TransPre(SqStack& S1, NStack& S2, char* p) {
	char a[MAXSIZE], c;
	int count = 0;//p的计数器
	scanf("%s", a);
	for (int i = strlen(a) - 1; i >= 0; i--) {
		int temp = 0, j = 0, flag = 1;
		while (a[i] >= '0' && a[i] <= '9') {//获取一个多位数
			flag *= 10, i--, j++;
		}
		for (int k = i + 1; k <= i + j; k++) {
			flag /= 10;
			temp += (a[k] - '0') * flag;
		}
		if (j != 0) {//若j不为0，则说明读取了一个数，将其存储
			Push_N(S2, temp);
		}

		if (a[i] == ')') {//右括号直接入栈
			Push(S1, a[i]);
		}

		if (a[i] == '+' || a[i] == '-') {
			while (!isEmpty(S1) && GetTop(S1) != ')') {//若栈顶为比自身优先级高的，则一直出栈，直到栈空或遇到比自己低级的
				Pop(S1, c);
				if (c == '+')Push_N(S2, -1);
				else if (c == '-')Push_N(S2, -2);
				else if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Push(S1, a[i]);
		}

		if (a[i] == '(') {
			while (GetTop(S1) != ')') {//若没遇到右括号，则一直出栈
				Pop(S1, c);
				if (c == '+')Push_N(S2, -1);
				else if (c == '-')Push_N(S2, -2);
				else if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Pop(S1, c);
		}

		if (a[i] == '*' || a[i] == '/') {
			while (!isEmpty(S1) && GetTop(S1) != ')' && GetTop(S1) != '+' && GetTop(S1) != '-') {//同上加减
				Pop(S1, c);
				if (c == '*')Push_N(S2, -3);
				else if (c == '/')Push_N(S2, -4);
			}
			Push(S1, a[i]);
		}
	}
	while (!isEmpty(S1)) {//把剩下的符号输出
		Pop(S1, c);
		if (c != ')') {//右括号不输出
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
	printf("前缀表达式结果为：%d ", GetTop_N(S1));
}

int main() {
	SqStack S;
	NStack NS;
	InitStack(S);
	InitStack_N(NS);
	char p[MAXSIZE];
	printf("请输入中缀表达式：\n");
	TransPost(S, p);
	CalPost(NS, p);
	printf("请输入中缀表达式：\n");
	InitStack(S);
	InitStack_N(NS);
	NStack S_CAL = TransPre(S, NS, p);
	CalPre(S_CAL);
}