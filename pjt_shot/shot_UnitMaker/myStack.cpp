#include "myStack.h"
#include <malloc.h>

using namespace my;

stack::stack() : stack(1) {}
stack::stack(unsigned int capacity) {
	if (capacity == 0) {
		capacity = 1;
	}

	topIndex = 0;
	this->capacity = capacity;
	value = (unsigned int*)malloc(sizeof(unsigned int) * capacity);
}

stack::~stack() {
	free(value);
}

bool stack::push(unsigned int in) {
	if (topIndex == capacity) {
		return false;
	}

	value[topIndex] = in;
	topIndex += 1;

	return true;
}

bool stack::pop(unsigned int* const out) {
	if (topIndex == 0) {
		return false;
	}

	topIndex -= 1;
	*out = value[topIndex];

	return true;
}

int stack::getSize() {
	return topIndex;
}

int stack::getCapacity() {
	return capacity;
}
