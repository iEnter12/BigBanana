#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAXN 200
int cnt[MAXN];
int n = 0, m = 0;//不同字符的个数
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
typedef char** HufCode;//哈夫曼编码字符串数组
HufTree HT;

void Count() {//打开文件并计算其中字符出现的频率
	FILE* file;
	file = fopen("1.txt", "r+");
	if (file == NULL) {
		printf("文件打开错误！\n");
		exit(0);
	}

	fscanf(file, "%s", s);
	int i = 0;
	while (s[i] != '\0') {
		if (!cnt[s[i]])
			++n;  //n为字符种类的总数
		cnt[s[i]]++;  //对应的cnt数组的ASCII值位加一 ，统计每种字符的数量
		i++;
	}
	m = 2 * n;//总共需要两倍叶子节点个数的节点
	fclose(file);
}

int select(int n) {//找到权值最小的字符
	int minn = 0x3f3f3f3f, minnode = 0;//近似为无穷大使用
	for (int i = 1; i <= n; i++) {
		if (!HT[i].p && HT[i].weight < minn) {//如果没有父节点则进行对比
			minn = HT[i].weight;
			minnode = i;
		}
	}
	return minnode;
}

void CreateHT() {//建哈夫曼树
	HT = (HufTree)malloc(m * sizeof(HTnode));//节点数组
	for (int i = 1, j = 0; i <= n; i++) {//给每个节点赋值
		while (!cnt[j])j++;
		HT[i] = HTnode(cnt[j], 0, (char)j);//若cnt[j]不为0，则其为一个出现过的字符，为其初始化一个节点
		j++;
	}
	for (int i = n + 1; i < m; i++)
		HT[i] = HTnode(0, 0, '#');//构造哈夫曼树的其他节点
	for (int i = n + 1; i < m; i++) {//合并叶子节点
		int s1 = select(i - 1);
		HT[s1].p = i, HT[i].l = s1;
		int s2 = select(i - 1);
		HT[s2].p = i, HT[i].r = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHTCode() {//构造哈夫曼编码
	char* cd = (char*)malloc(n * sizeof(char));
	FILE* file = fopen("HufCode", "w+");
	if (file == NULL) {
		printf("文件打开错误！\n");
		exit(0);
	}
	string ss = "";//存储一个临时的哈夫曼编码
	for (int i = 1; i <= n; i++) {
		int start = n - 1;//从后往前构建
		for (int c = i, f = HT[c].p; f != 0; c = f, f = HT[c].p) {
			if (HT[f].l == c)//左孩子
				cd[start--] = '0';
			else//右孩子
				cd[start--] = '1';
		}
		for (int j = start + 1; j < n; j++) {
			ss += cd[j];
		}
		HC[(int)HT[i].c] = ss;
		fprintf(file, "%c %s\n", (char)HT[i].c, ss.c_str());//将这个字符的哈夫曼编码写入文件
		ss = "";
	}
	fclose(file);
}

void Compress() {//压缩
	FILE* file = fopen("compressed file", "w+");
	if (file == NULL) {
		printf("文件打开错误！\n");
		exit(0);
	}

	string lltt = "";//要写入文件的字符串
	int i = 0;
	while (s[i] != '\0') {
		lltt += HC[(int)s[i++]];
	}
	fprintf(file, "%s", lltt.c_str());
	printf("压缩完成！");
	fclose(file);
}

void unCompress() {//解压
	FILE* file = fopen("compressed file", "r+");
	if (file == NULL) {
		printf("文件打开错误！\n");
		exit(0);
	}

	string ll = "";//用于存储哈夫曼编码的临时字符串
	char llc[MAXN];//将文件中总的哈夫曼编码写入这个字符串数组
	fscanf(file, "%s", llc);
	int i = 0;
	while (llc[i] != '\0') {
		ll += llc[i];
		i++;
		for (int j = 1; j <= 128; j++) {//每加一个字符就与目前已经有的哈夫曼编码进行对比
			if (ll == HC[j]) {//如果相同则清空临时字符串，将对应的字符打印出来
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
	printf("请输入模式：\n");
	printf("1.压缩\n");
	printf("2.解压缩\n");
	int n;
	scanf("%d", &n);
	switch (n) {
	case 1:Compress(); break;
	case 2:unCompress(); break;
	default:printf("输入错误！"); break;
	}
	return 0;
}

