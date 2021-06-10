#pragma once

#include "LinkedList.h"

template<typename T>
class CQueue: public CLinkedList<T>{

	using valueType = T;
	using ptrType = valueType*;

public:

	CQueue() : CLinkedList<T>(){}
	~CQueue() {}

	inline void push(valueType data) {
		this->push_back(data);
	}
	inline void pop(ptrType out) {
		*out = this->begin()->value;
		this->pop_front();
	}

	inline bool isEmpty() {
		return this->head.child == &(this->tail);
	}

private:

};