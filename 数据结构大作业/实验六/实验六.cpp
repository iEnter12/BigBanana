#include<stdio.h>
#include<stdlib.h>

int arr[513];//存储随机数
int top = -1, second = -1;//最大和次大数的下标
int max1 = -1, max2 = -1;//最大和次大数的值
void sequentialSearch(int* a, int len) {//顺序，O(n)
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

void cpSearch(int* a, int len) {//锦标赛法，O(n)=n-1+logn-1=n+logn-2
	top = second = max1 = max2 = -1;
	int i;
	int* b = (int*)malloc(sizeof(int) * len * 2 + 1);//一个两倍总数大小的数组，后半区用来存原数组，前半区用来存每次比较的胜者并再次比较
	for (i = len * 2; i > len; i--) {
		b[i] = a[i - len];
	}
	for (i = len * 2 - 1; i >= 3; i -= 2) {//从后往前记录每次的胜者
		b[i / 2 + 1] = b[i] > b[i + 1] ? b[i] : b[i + 1];
	}
	//找最大，时间复杂度为n-1
	//最大数目前下标为2
	max1 = b[2];
	for (i = 2; i <= len;) {//从所有输给最大值的数中找次大值
		if (b[i] == b[i * 2]) {//此时输的应该在2n-1
			if (b[i * 2 - 1] > max2) {
				max2 = b[i * 2 - 1];
				second = i * 2 - 1;
			}
			i *= 2;
		}
		else {//此时输的应该在2n
			if (b[i * 2] > max2) {
				max2 = b[i * 2];
				second = i * 2;
			}			
			i = i * 2 - 1;
		}
	}
	//找第二大数，时间复杂度为logn-1（树）
	//此时i-len为最大数下标
	top = i - len;
	//若次大数下标此时还在前半区，则通过倍增的方法找到其在后半区的下标
	while (second * 2 <= 2 * len) {
		if (b[second] == b[second * 2])second *= 2;
		else second = second * 2 - 1;
	}
	second -= len;//得到次大数下标
}


int size;
typedef struct stu {
	int score;
	int no;
};
stu heap[513];//学生数组

void swap(stu& a, stu& b) {//自己定义的一个交换函数
	stu temp = a;
	a = b;
	b = temp;
}

void up(int p) {//自下向上并维护大根堆的特性（建堆时使用）
	while (p > 1) {
		if (heap[p].score > heap[p / 2].score) {
			swap(heap[p], heap[p / 2]);
			p /= 2;
		}
		else break;
	}
}

void down(int p) {//自顶向下并维护大根堆的特性（删除堆顶时使用）
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

void build(int* a) {//插入法建堆，每次加入一个新节点到最底端，然后自下向上维护一次堆
	for (size = 1; size <= 512; size++) {
		heap[size].no = size;
		heap[size].score = a[size];
		up(size);
	}
}
//插入法初始化堆的最好时间复杂度为O(n)，最坏时间复杂度为O(nlogn)
//若是筛选法则最好最坏时间复杂度都为O(n)

void delete1(stu* h) {//删除堆顶，将堆顶元素与最后一个元素交换，然后自顶向下维护一次堆
	heap[1] = heap[size--];
	down(1);
}
//删除一次时间复杂度为O(logn)

int getTopNo(stu* h) {
	return h[1].no;
}

int getTopScore(stu* h) {
	return h[1].score;
}

void heapSearch(int* a, int num) {
	build(arr);
	//得到最大值
	top = getTopNo(heap);
	max1 = getTopScore(heap);
	//删除堆顶并维护后，堆仍有大根堆的特性，此时堆顶即为次大值
	delete1(heap);
	second = getTopNo(heap);
	max2 = getTopScore(heap);
}

int main() {
	for (int i = 1; i <= 512; i++) {
		arr[i] = rand() % 1000;//0到999的随机数
		printf("第%d个参与者 %d\n", i, arr[i]);
	}
	printf("\n");
	sequentialSearch(arr, 512);
	printf("顺序查找的结果为：\n最高分者编号：%d 最高分：%d\n次高分者编号：%d 次高分：%d\n", top, max1, second, max2);
	cpSearch(arr, 512);
	printf("锦标赛查找的结果为：\n最高分者编号：%d 最高分：%d\n次高分者编号：%d 次高分：%d\n", top, max1, second, max2);
	heapSearch(arr, 512);
	printf("堆排序查找的结果为：\n最高分者编号：%d 最高分：%d\n次高分者编号：%d 次高分：%d\n", top, max1, second, max2);
	return 0;
}
