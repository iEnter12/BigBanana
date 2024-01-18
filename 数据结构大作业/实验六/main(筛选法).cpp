#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
int n = 512;
int size;
typedef struct stu {
    int score;
    int no;
};
stu heap[513];//学生数组
void heapAdjust(stu* h, int s, int m)//一次筛选的过程
{
    stu rc;
    rc.no = h[s].no;
    rc.score = h[s].score;
    for (int j = 2 * s; j <= m; j = j * 2)//通过循环沿较小的孩子结点向下筛选
    {
        if (j < m&& h[j].score < h[j + 1].score) j++;//j为较大的记录的下标
        if (rc.score > h[j].score) break;
        h[s] = h[j]; s = j;
    }
    h[s] = rc;//插入
}
void heapSort(stu* h, int n)
{
    int i, j;
    for (i = n / 2; i > 0; i--)//通过循环初始化顶堆
    {
        heapAdjust(h, i, n);
    }
}

void delete1(stu* h) {
    heap[1] = heap[n--];
    heapAdjust(h, 1, n);
}

int getTopNo(stu* h) {
    return h[1].no;
}

int getTopScore(stu* h) {
    return h[1].score;
}
int main()
{
    for (int i = 1; i <= n; i++)
    {
        heap[i].no = i;
        heap[i].score = rand() % 1000;
        printf("第%d个参与者 %d\n", i, heap[i]);
    }
    heapSort(heap, n);
    int max1 = getTopScore(heap), top = getTopNo(heap);
    delete1(heap);
    heapSort(heap, n);
    int max2 = getTopScore(heap), second = getTopNo(heap);
    printf("堆排序查找的结果为：\n最高分者编号：%d 最高分：%d\n次高分者编号：%d 次高分：%d\n", top, max1, second, max2);
    return 0;
}