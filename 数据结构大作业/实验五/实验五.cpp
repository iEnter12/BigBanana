#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
int n, z;//�޵�ʿ��Ұ�������ʹ���״̬��,z=1��ʾ���ڳ�ʼ�Ӱ�
int w = 0;//�ܵĹ��ӷ�����
int idea = 0;//�ܵķ�����
int way[100][2];
vector<string>hist;//�ܵ��ı�

void myPrint() {//��Ŀǰ����������������
	for (int i = 0; i < hist.size(); i++) {
		cout << hist[i] << endl << endl;
	}
}

int is_legal(int frair_num, int bar_num, int boat){
	if (frair_num<0 || frair_num>n) return 0; //�޵�ʿ���ݷǷ�
	if (bar_num<0 || bar_num>n) return 0;     //Ұ�������ݷǷ�
	if ((frair_num < bar_num && frair_num) || (n - frair_num && (n - frair_num) < (n - bar_num))) return 0;   //�޵�ʿ��Ұ���˳Ե��������������Ϊ0���ÿ���
	if (boat != 0 && boat != 1) return 0;
	char text[40];
	sprintf(text, "frair_num=%d, bar_num=%d, boat=%d", frair_num, bar_num, boat);
	for (int i = 0; i < hist.size(); i++)          //�����֮ǰ���ֹ�
		if (text == hist[i])
			return 0;
	hist.push_back(text);
	return  1;
}

void dfs(int frair_num, int bar_num, int boat) {//ǰ���߶������ڳ�ʼ�Ӱ�������
	if (frair_num == 0 && bar_num == 0 && boat == 0) {
		idea++;
		cout << "��" << idea << "�ֽⷨ���£�" << endl;
		myPrint();
		return;
	}

	for (int i = 0; i < w; i++) {//�������й��ӷ���
		//���ӳ�ʼ��԰�
		if (boat == 1) {
			int f = frair_num - way[i][0];
			int b = bar_num - way[i][1];
			if (is_legal(f, b, 0)) {
				dfs(f, b, 0);
				hist.pop_back();//����ʱ����һ�����ɾ��
			}
		}

		//���Ӷ԰��س�ʼ
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
	cout << "�������޵�ʿ������Ұ���������Լ���ֻ������" << endl;
	cin >> n >> z;
	sprintf(text, "frair_num=%d, bar_num=%d, boat=%d", n, n, 1);
	hist.push_back(text);//��ʼ���
	//���ܵĹ��ӷ���
	for (int i = z; i > 0; i--) {//�޵�ʿ��������Ϊ0��
		for (int j = 0; j < i, j <= z - i; j++) {//Ұ������
			way[w][0] = i;
			way[w][1] = j;
			w++;
		}
	}
	for (int j = 1; j <= z; j++) {//�޵�ʿ����Ϊ0ʱ��Ұ�˵�����
		way[w][0] = 0;
		way[w][1] = j;
		w++;
	}
	cout << "���ܵĹ��ӷ�����" << endl;
	for (int j = 0; j < w; j++) {
		cout << "�޵�ʿ��" << way[j][0] << "�ˣ�Ұ�ˣ�" << way[j][1] << "��" << endl;
	}
	dfs(n, n, 1);
	if (idea == 0)
		cout << "�޽�" << endl;
	else 
		cout << "�ܷ�����Ϊ��" << idea << endl;
	return 0;
}
