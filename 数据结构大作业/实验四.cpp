#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAXN 200
int cnt[MAXN];
int n = 0, m = 0;//��ͬ�ַ��ĸ���
char s[MAXN];
char sa[MAXN][MAXN];
string HC[256];

typedef struct node {
	int weight;
	char c;
	int p, l, r;
	node(int n, int m, char ch) {
		weight = n;
		p = l = r = m, c = ch;
	}
}HTnode, *HufTree;
typedef char** HufCode;//�����������ַ�������
HufTree HT;

void Count() {//���ļ������������ַ����ֵ�Ƶ��
	FILE* file;
	file = fopen("1.txt", "r+");
	if (file == NULL) {
		printf("�ļ��򿪴���\n");
		exit(0);
	}

	fscanf(file, "%s", s);
	int i = 0;
	while (s[i] != '\0') {
		if (!cnt[s[i]])
			++n;  //nΪ�ַ����������
		cnt[s[i]]++;  //��Ӧ��cnt�����ASCIIֵλ��һ ��ͳ��ÿ���ַ�������
		i++;
	}
	m = 2 * n;//�ܹ���Ҫ����Ҷ�ӽڵ�����Ľڵ�
	fclose(file);
}

int select(int n) {//�ҵ�Ȩֵ��С���ַ�
	int minn = 0x3f3f3f3f, minnode = 0;//����Ϊ�����ʹ��
	for (int i = 1; i <= n; i++) {
		if (!HT[i].p && HT[i].weight < minn) {//���û�и��ڵ�����жԱ�
			minn = HT[i].weight;
			minnode = i;
		}
	}
	return minnode;
}

void CreateHT() {//����������
	HT = (HufTree)malloc(m * sizeof(HTnode));//�ڵ�����
	for (int i = 1, j = 0; i <= n; i++) {//��ÿ���ڵ㸳ֵ
		while (!cnt[j])j++;
		HT[i] = HTnode(cnt[j], 0, (char)j);//��cnt[j]��Ϊ0������Ϊһ�����ֹ����ַ���Ϊ���ʼ��һ���ڵ�
		j++;
	}
	for (int i = n + 1; i < m; i++)
		HT[i] = HTnode(0, 0, '#');//������������������ڵ�
	for (int i = n + 1; i < m; i++) {//�ϲ�Ҷ�ӽڵ�
		int s1 = select(i - 1);
		HT[s1].p = i, HT[i].l = s1;
		int s2 = select(i - 1);
		HT[s2].p = i, HT[i].r = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHTCode() {//�������������
	char* cd = (char*)malloc(n * sizeof(char));
	FILE* file = fopen("HufCode", "w+");
	if (file == NULL) {
		printf("�ļ��򿪴���\n");
		exit(0);
	}
	string ss = "";//�洢һ����ʱ�Ĺ���������
	for (int i = 1; i <= n; i++) {
		int start = n - 1;//�Ӻ���ǰ����
		for (int c = i, f = HT[c].p; f != 0; c = f, f = HT[c].p) {
			if (HT[f].l == c)//����
				cd[start--] = '0';
			else//�Һ���
				cd[start--] = '1';
		}
		for (int j = start + 1; j < n; j++) {
			ss += cd[j];
		}
		HC[(int)HT[i].c] = ss;
		fprintf(file, "%c %s\n", (char)HT[i].c, ss.c_str());//������ַ��Ĺ���������д���ļ�
		ss = "";
	}
	fclose(file);
}

void Compress() {//ѹ��
	FILE* file = fopen("compressed file", "w+");
	if (file == NULL) {
		printf("�ļ��򿪴���\n");
		exit(0);
	}

	string lltt = "";//Ҫд���ļ����ַ���
	int i = 0;
	while (s[i] != '\0') {
		lltt += HC[(int)s[i++]];
	}
	fprintf(file, "%s", lltt.c_str());
	printf("ѹ����ɣ�");
	fclose(file);
}

void unCompress() {//��ѹ
	FILE* file = fopen("compressed file", "r+");
	if (file == NULL) {
		printf("�ļ��򿪴���\n");
		exit(0);
	}

	string ll = "";//���ڴ洢�������������ʱ�ַ���
	char llc[MAXN];//���ļ����ܵĹ���������д������ַ�������
	fscanf(file, "%s", llc);
	int i = 0;
	while (llc[i] != '\0') {
		ll += llc[i];
		i++;
		for (int j = 1; j <= 128; j++) {//ÿ��һ���ַ�����Ŀǰ�Ѿ��еĹ�����������жԱ�
			if (ll == HC[j]) {//�����ͬ�������ʱ�ַ���������Ӧ���ַ���ӡ����
				printf("%c", j);
				ll = "";
				break;
			}
		}
	}
	fclose(file);
}


int main() {
	Count();
	CreateHT();
	CreateHTCode();
	printf("������ģʽ��\n");
	printf("1.ѹ��\n");
	printf("2.��ѹ��\n");
	int n;
	scanf("%d", &n);
	switch (n) {
	case 1:Compress(); break;
	case 2:unCompress(); break;
	default:printf("�������"); break;
	}
	return 0;
}

