#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define N 20
int a[N];

void rand_arr() {
	for (int i = 0; i < 20; i++) {
		a[i] = rand() % 100;
	}
}

void insert_sort(int* a, int len) {
	int key, j;
	for (int i = 1; i < len; i++) {
		key = a[i];
		j = i - 1;
		while (a[j] > key && j >= 0) {//找到插入位置
			a[j + 1] = a[j];//依次后移
			j--;
		}
		a[j + 1] = key;
	}
}

void quick_sort(int* a, int left, int right) {
	if (left > right)return;//结束条件
	int i = left, j = right, temp = a[left];//右哨兵和左哨兵
	while (i < j) {
		while (a[j] >= temp && i < j)//右哨兵从右向左找到第一个比基准大的
			j--;
		while (a[i] <= temp && i < j)//左哨兵从左向右找到第一个比基准小的
			i++;
		if (i < j) {//交换
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	a[left] = a[i];//交换基准与中心
	a[i] = temp;
	quick_sort(a, left, i - 1);//递归在左右半区继续排序
	quick_sort(a, i + 1, right);
}

void select_sort(int* a, int len) {
	int minn;
	for (int i = 0; i < len - 1; i++) {
		minn = i;
		for (int j = i + 1; j < len; j++) {
			if (a[j] < a[minn])//找到最小值
				minn = j;
		}
		//交换
		int temp = a[i];
		a[i] = a[minn];
		a[minn] = temp;
	}
}

int main() {
	rand_arr();
	printf("原始数组为：\n");
	for (int i = 0; i < N; i++)printf("%d ",a[i]);
	printf("\n请输入排序方法：\n1.插入排序  2.快速排序  3.选择排序\n");
	int n;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		insert_sort(a, N);
		printf("插入排序的结果为：\n");
		for (int i = 0; i < N; i++)printf("第%d个数：%d\n", i + 1, a[i]);
		break;
	case 2:
		quick_sort(a, 0, N - 1);
		printf("快速排序的结果为：\n");
		for (int i = 0; i < N; i++)printf("第%d个数：%d\n", i + 1, a[i]);
		break;
	case 3:
		select_sort(a, N);
		printf("选择排序的结果为：\n");
		for (int i = 0; i < N; i++)printf("第%d个数：%d\n", i + 1, a[i]);
		break;
	default:
		printf("输入错误！\n");
		break;
	}
	return 0;
}
