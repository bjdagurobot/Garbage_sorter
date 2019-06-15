#include "ColQueue.h"
ColQueue::ColQueue(int N)
{
	data = new int[N];
	num = N; length = 0;
	front = 0; rear = 0;
}

void ColQueue::Enter(int a)
{
	if (a == 0)return;
	data[rear] = a;
	rear = (rear + 1) % num;
	++length;
}

int ColQueue::Get()
{
	if (front == rear)return 0;
	int a = data[front];
	front = (front + 1) % num; --length;
	return a;
}
int ColQueue::Length()
{
	return length;
}
