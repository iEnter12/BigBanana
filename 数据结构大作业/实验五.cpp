#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
int n, z;//修道士、野人数量和船的状态量,z=1表示船在初始河岸
int w = 0;//总的过河方案数
int idea = 0;//总的方法数
int way[100][2];
vector<string>hist;//总的文本

void myPrint() {//将目前所有情况都输出出来
	for (int i = 0; i < hist.size(); i++) {
		cout << hist[i] << endl << endl;
	}
}

int is_legal(int frair_num, int bar_num, int boat){
	if (frair_num<0 || frair_num>n) return 0; //修道士数据非法
	if (bar_num<0 || bar_num>n) return 0;     //野蛮人数据非法
	if ((frair_num < bar_num && frair_num) || (n - frair_num && (n - frair_num) < (n - bar_num))) return 0;   //修道士被野蛮人吃掉的情况，若人数为0则不用考虑
	if (boat != 0 && boat != 1) return 0;
	char text[40];
	sprintf(text, "frair_num=%d, bar_num=%d, boat=%d", frair_num, bar_num, boat);
	for (int i = 0; i < hist.size(); i++)          //此情况之前出现过
		if (text == hist[i])
			return 0;
	hist.push_back(text);
	return  1;
}

void dfs(int frair_num, int bar_num, int boat) {//前两者都代表在初始河岸的数量
	if (frair_num == 0 && bar_num == 0 && boat == 0) {
		idea++;
		cout << "第" << idea << "种解法如下：" << endl;
		myPrint();
		return;
	}

	for (int i = 0; i < w; i++) {//遍历所有过河方案
		//船从初始向对岸
		if (boat == 1) {
			int f = frair_num - way[i][0];
			int b = bar_num - way[i][1];
			if (is_legal(f, b, 0)) {
				dfs(f, b, 0);
				hist.pop_back();//回溯时把上一次情况删除
			}
		}

		//船从对岸回初始
		if (boat == 0) {
			int f = frair_num + way[i][0];
			int b = bar_num + way[i][1];
			if (is_legal(f, b, 1)) {
				dfs(f, b, 1);
				hist.pop_back();
			}
		}
	}
}

int main() {
	char text[40];
	cout << "请输入修道士数量和野人数量，以及船只容量：" << endl;
	cin >> n >> z;
	sprintf(text, "frair_num=%d, bar_num=%d, boat=%d", n, n, 1);
	hist.push_back(text);//初始情况
	//可能的过河方案
	for (int i = z; i > 0; i--) {//修道士数量（不为0）
		for (int j = 0; j < i, j <= z - i; j++) {//野人数量
			way[w][0] = i;
			way[w][1] = j;
			w++;
		}
	}
	for (int j = 1; j <= z; j++) {//修道士数量为0时，野人的数量
		way[w][0] = 0;
		way[w][1] = j;
		w++;
	}
	cout << "可能的过河方案：" << endl;
	for (int j = 0; j < w; j++) {
		cout << "修道士：" << way[j][0] << "人，野人：" << way[j][1] << "人" << endl;
	}
	dfs(n, n, 1);
	if (idea == 0)
		cout << "无解" << endl;
	else 
		cout << "总方案数为：" << idea << endl;
	return 0;
}
