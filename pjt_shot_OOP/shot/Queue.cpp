#include <malloc.h>
#include "Queue.h"

CQueue::CQueue(int size) {

	arr = (CQueue::ptrType)malloc(size * sizeof(CQueue::valueType));

	cap = size;
	this->size = 0;
	front = 0;
	rear = 0;

}

CQueue::~CQueue() {

	free(arr);

}

bool CQueue::push(CQueue::valueType data) {

	if (cap == size) {
		return false;
	}

	arr[rear] = data;
	rear = (rear + 1) % cap;
	size += 1;

	return true;

}

bool CQueue::pop(CQueue::ptrType out) {

	if (size == 0) {
		return false;
	}

	*out = arr[front];
	front = (front + 1) % cap;
	size -= 1;

	return true;

}