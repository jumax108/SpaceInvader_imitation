#pragma once

namespace my {
	class stack {

	protected:
		unsigned int capacity;
		unsigned int* value;
		unsigned int topIndex;

	public:
		bool push(
			unsigned int in // push data
		);

		bool pop(
			unsigned int* const out // for return
		);

		// get used stack size
		int getSize();

		// get maximum stack size
		int getCapacity();

		stack();
		stack(
			unsigned int capacity // minimum capacity is 1
		);

		~stack();
	};

}