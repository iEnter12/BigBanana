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
		while (a[j] > key && j >= 0) {//�ҵ�����λ��
			a[j + 1] = a[j];//���κ���
			j--;
		}
		a[j + 1] = key;
	}
}

void quick_sort(int* a, int left, int right) {
	if (left > right)return;//��������
	int i = left, j = right, temp = a[left];//���ڱ������ڱ�
	while (i < j) {
		while (a[j] >= temp && i < j)//���ڱ����������ҵ���һ���Ȼ�׼���
			j--;
		while (a[i] <= temp && i < j)//���ڱ����������ҵ���һ���Ȼ�׼С��
			i++;
		if (i < j) {//����
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	a[left] = a[i];//������׼������
	a[i] = temp;
	quick_sort(a, left, i - 1);//�ݹ������Ұ�����������
	quick_sort(a, i + 1, right);
}

void select_sort(int* a, int len) {
	int minn;
	for (int i = 0; i < len - 1; i++) {
		minn = i;
		for (int j = i + 1; j < len; j++) {
			if (a[j] < a[minn])//�ҵ���Сֵ
				minn = j;
		}
		//����
		int temp = a[i];
		a[i] = a[minn];
		a[minn] = temp;
	}
}

int main() {
	rand_arr();
	printf("ԭʼ����Ϊ��\n");
	for (int i = 0; i < N; i++)printf("%d ",a[i]);
	printf("\n���������򷽷���\n1.��������  2.��������  3.ѡ������\n");
	int n;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		insert_sort(a, N);
		printf("��������Ľ��Ϊ��\n");
		for (int i = 0; i < N; i++)printf("��%d������%d\n", i + 1, a[i]);
		break;
	case 2:
		quick_sort(a, 0, N - 1);
		printf("��������Ľ��Ϊ��\n");
		for (int i = 0; i < N; i++)printf("��%d������%d\n", i + 1, a[i]);
		break;
	case 3:
		select_sort(a, N);
		printf("ѡ������Ľ��Ϊ��\n");
		for (int i = 0; i < N; i++)printf("��%d������%d\n", i + 1, a[i]);
		break;
	default:
		printf("�������\n");
		break;
	}
	return 0;
}
