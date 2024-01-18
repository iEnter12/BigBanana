#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXN 100
int a[MAXN][MAXN] = { 0 };

void BuildSqaure(int m) {//ÿ�ν���������һ���������Ͻǣ������Ͻ�Ϊ��С���������߽���ȡ�࣬�����Ѹ�ֵ���������һ�������·�
	printf("ħ����Ϊ��\n");
	a[0][m / 2] = 1;//1�ڵ�һ���м�
	int row = 0, col = m / 2;//���к��г�ʼ��Ϊ1����λ��
	for (int i = 2; i <= m * m; i++) {
		row = (row + m - 1) % m;//row����
		col = (col + 1) % m;//col����
		if (a[row][col]) {
			row = (row + 2) % m;//row����
			col = (col + m - 1) % m;//col����
		}
		a[row][col] = i;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			printf("%-4d", a[i][j]);
		printf("\n");
	}
}


void BuildSqaure2(int m) {//ÿ�ν���������һ���������Ͻǣ������Ͻ�Ϊ��С���������߽���ȡ�࣬�����Ѹ�ֵ������������
	printf("ħ����Ϊ��\n");
	a[m / 2 - 1][m / 2] = 1;
	int row = m / 2 - 1, col = m / 2;
	for (int i = 2; i <= m * m; i++) {
		row = (row + m - 1) % m;
		col = (col + 1) % m;
		if (a[row][col]) {
			row = (row - 1 + m) % m;
			col = (col + m - 1) % m;
		}
		a[row][col] = i;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			printf("%-4d", a[i][j]);
		printf("\n");
	}
}


int main() {
	int m;
	printf("������m��");
	scanf("%d", &m);
	if (m % 2 == 1) {
		BuildSqaure(m);
		//BuildSqaure2(m);
	}
	else {
		printf("���벻�Ϸ���");
	}
	return 0;
}