#pragma once

namespace my {
	class stack {

		using valueType = unsigned int;
		using ptrType = unsigned int*;

	private:
		unsigned int capacity;
		ptrType value;
		unsigned int topIndex;

	public:
		bool push(
			const valueType in // push data
		);

		bool push(
			const ptrType const in // push data
		);

		bool pop(
			ptrType const out // for return
		);

		// get used stack size
		inline int getSize() {
			return topIndex;
		}

		// get maximum stack size
		inline int getCapacity() {
			return capacity;
		}

		stack();
		stack(
			unsigned int capacity // minimum capacity is 1
		);

		~stack();
	};

}