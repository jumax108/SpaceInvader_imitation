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
		return _size == 0;
	}

	inline int size() {
		return _size;
	}

private:

	ptrType _arr;

	int _cap; // capacity
	int _size;
	int _front;
	int _rear;

};

