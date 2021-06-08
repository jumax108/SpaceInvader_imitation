#include <malloc.h>
#include "Queue.h"

CQueue::CQueue(int size) {

	_arr = (CQueue::ptrType)malloc(size * sizeof(CQueue::valueType));

	_cap = size;
	_size = 0;
	_front = 0;
	_rear = 0;

}

CQueue::~CQueue() {

	free(_arr);

}

bool CQueue::push(CQueue::valueType data) {

	if (_cap == _size) {
		return false;
	}

	_arr[_rear] = data;
	_rear = (_rear + 1) % _cap;
	_size += 1;

	return true;

}

bool CQueue::pop(CQueue::ptrType out) {

	if (_size == 0) {
		return false;
	}

	*out = _arr[_front];
	_front = (_front + 1) % _cap;
	_size -= 1;

	return true;

}