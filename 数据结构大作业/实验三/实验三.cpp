#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXN 100
int a[MAXN][MAXN] = { 0 };

void BuildSqaure(int m) {//每次将数放在上一个数的右上角（以左上角为最小），遇到边界则取余，遇到已赋值的则放在上一个数的下方
	printf("魔方阵为：\n");
	a[0][m / 2] = 1;//1在第一行中间
	int row = 0, col = m / 2;//把行和列初始化为1所在位置
	for (int i = 2; i <= m * m; i++) {
		row = (row + m - 1) % m;//row上移
		col = (col + 1) % m;//col右移
		if (a[row][col]) {
			row = (row + 2) % m;//row下移
			col = (col + m - 1) % m;//col左移
		}
		a[row][col] = i;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++)
			printf("%-4d", a[i][j]);
		printf("\n");
	}
}


void BuildSqaure2(int m) {//每次将数放在上一个数的右上角（以左上角为最小），遇到边界则取余，遇到已赋值的则往上两个
	printf("魔方阵为：\n");
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
	printf("请输入m：");
	scanf("%d", &m);
	if (m % 2 == 1) {
		BuildSqaure(m);
		//BuildSqaure2(m);
	}
	else {
		printf("输入不合法！");
	}
	return 0;
}