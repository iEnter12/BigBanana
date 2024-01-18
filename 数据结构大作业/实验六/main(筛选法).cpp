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
stu heap[513];//ѧ������
void heapAdjust(stu* h, int s, int m)//һ��ɸѡ�Ĺ���
{
    stu rc;
    rc.no = h[s].no;
    rc.score = h[s].score;
    for (int j = 2 * s; j <= m; j = j * 2)//ͨ��ѭ���ؽ�С�ĺ��ӽ������ɸѡ
    {
        if (j < m&& h[j].score < h[j + 1].score) j++;//jΪ�ϴ�ļ�¼���±�
        if (rc.score > h[j].score) break;
        h[s] = h[j]; s = j;
    }
    h[s] = rc;//����
}
void heapSort(stu* h, int n)
{
    int i, j;
    for (i = n / 2; i > 0; i--)//ͨ��ѭ����ʼ������
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
        printf("��%d�������� %d\n", i, heap[i]);
    }
    heapSort(heap, n);
    int max1 = getTopScore(heap), top = getTopNo(heap);
    delete1(heap);
    heapSort(heap, n);
    int max2 = getTopScore(heap), second = getTopNo(heap);
    printf("��������ҵĽ��Ϊ��\n��߷��߱�ţ�%d ��߷֣�%d\n�θ߷��߱�ţ�%d �θ߷֣�%d\n", top, max1, second, max2);
    return 0;
}