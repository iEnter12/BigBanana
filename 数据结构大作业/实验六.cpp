#include<stdio.h>
#include<stdlib.h>

int arr[513];//�洢�����
int top = -1, second = -1;//���ʹδ������±�
int max1 = -1, max2 = -1;//���ʹδ�����ֵ
void sequentialSearch(int* a, int len) {//˳��O(n)
	top = second = max1 = max2 = -1;
	for (int i = 1; i <= len; i++) {
		if (a[i] > max1) {
			max2 = max1;
			second = top;
			max1 = a[i];
			top = i;
		}
		else if (a[i] <= max1 && a[i] > max2) {
			max2 = a[i];
			second = i;
		}
	}
		
}

void cpSearch(int* a, int len) {//����������O(n)=n-1+logn-1=n+logn-2
	top = second = max1 = max2 = -1;
	int i;
	int* b = (int*)malloc(sizeof(int) * len * 2 + 1);//һ������������С�����飬�����������ԭ���飬ǰ����������ÿ�αȽϵ�ʤ�߲��ٴαȽ�
	for (i = len * 2; i > len; i--) {
		b[i] = a[i - len];
	}
	for (i = len * 2 - 1; i >= 3; i -= 2) {//�Ӻ���ǰ��¼ÿ�ε�ʤ��
		b[i / 2 + 1] = b[i] > b[i + 1] ? b[i] : b[i + 1];
	}
	//�����ʱ�临�Ӷ�Ϊn-1
	//�����Ŀǰ�±�Ϊ2
	max1 = b[2];
	for (i = 2; i <= len;) {//������������ֵ�������Ҵδ�ֵ
		if (b[i] == b[i * 2]) {//��ʱ���Ӧ����2n-1
			if (b[i * 2 - 1] > max2) {
				max2 = b[i * 2 - 1];
				second = i * 2 - 1;
			}
			i *= 2;
		}
		else {//��ʱ���Ӧ����2n
			if (b[i * 2] > max2) {
				max2 = b[i * 2];
				second = i * 2;
			}			
			i = i * 2 - 1;
		}
	}
	//�ҵڶ�������ʱ�临�Ӷ�Ϊlogn-1������
	//��ʱi-lenΪ������±�
	top = i - len;
	//���δ����±��ʱ����ǰ��������ͨ�������ķ����ҵ����ں�������±�
	while (second * 2 <= 2 * len) {
		if (b[second] == b[second * 2])second *= 2;
		else second = second * 2 - 1;
	}
	second -= len;//�õ��δ����±�
}


int size;
typedef struct stu {
	int score;
	int no;
};
stu heap[513];//ѧ������

void swap(stu& a, stu& b) {//�Լ������һ����������
	stu temp = a;
	a = b;
	b = temp;
}

void up(int p) {//�������ϲ�ά������ѵ����ԣ�����ʱʹ�ã�
	while (p > 1) {
		if (heap[p].score > heap[p / 2].score) {
			swap(heap[p], heap[p / 2]);
			p /= 2;
		}
		else break;
	}
}

void down(int p) {//�Զ����²�ά������ѵ����ԣ�ɾ���Ѷ�ʱʹ�ã�
	while (p <= size) {
		int s = p * 2;
		if (s < size && heap[s].score < heap[size + 1].score)s++;
		if (heap[s].score > heap[p].score) {
			swap(heap[s], heap[p]);
			p = s;
		}
		else break;
	}
}

void build(int* a) {//���뷨���ѣ�ÿ�μ���һ���½ڵ㵽��׶ˣ�Ȼ����������ά��һ�ζ�
	for (size = 1; size <= 512; size++) {
		heap[size].no = size;
		heap[size].score = a[size];
		up(size);
	}
}
//���뷨��ʼ���ѵ����ʱ�临�Ӷ�ΪO(n)���ʱ�临�Ӷ�ΪO(nlogn)
//����ɸѡ��������ʱ�临�Ӷȶ�ΪO(n)

void delete1(stu* h) {//ɾ���Ѷ������Ѷ�Ԫ�������һ��Ԫ�ؽ�����Ȼ���Զ�����ά��һ�ζ�
	heap[1] = heap[size--];
	down(1);
}
//ɾ��һ��ʱ�临�Ӷ�ΪO(logn)

int getTopNo(stu* h) {
	return h[1].no;
}

int getTopScore(stu* h) {
	return h[1].score;
}

void heapSearch(int* a, int num) {
	build(arr);
	//�õ����ֵ
	top = getTopNo(heap);
	max1 = getTopScore(heap);
	//ɾ���Ѷ���ά���󣬶����д���ѵ����ԣ���ʱ�Ѷ���Ϊ�δ�ֵ
	delete1(heap);
	second = getTopNo(heap);
	max2 = getTopScore(heap);
}

int main() {
	for (int i = 1; i <= 512; i++) {
		arr[i] = rand() % 1000;//0��999�������
		printf("��%d�������� %d\n", i, arr[i]);
	}
	printf("\n");
	sequentialSearch(arr, 512);
	printf("˳����ҵĽ��Ϊ��\n��߷��߱�ţ�%d ��߷֣�%d\n�θ߷��߱�ţ�%d �θ߷֣�%d\n", top, max1, second, max2);
	cpSearch(arr, 512);
	printf("���������ҵĽ��Ϊ��\n��߷��߱�ţ�%d ��߷֣�%d\n�θ߷��߱�ţ�%d �θ߷֣�%d\n", top, max1, second, max2);
	heapSearch(arr, 512);
	printf("��������ҵĽ��Ϊ��\n��߷��߱�ţ�%d ��߷֣�%d\n�θ߷��߱�ţ�%d �θ߷֣�%d\n", top, max1, second, max2);
	return 0;
}
