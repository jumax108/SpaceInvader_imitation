#pragma once
class CQueue{

	using valueType = int;
	using ptrType = valueType*;

public:

	CQueue(int size);
	~CQueue();

	bool push(valueType data);
	bool pop(ptrType out);

	inline bool isEmpty() {
		return size == 0;
	}

private:

	ptrType arr;

	int cap; // capacity
	int size;
	int front;
	int rear;

};

