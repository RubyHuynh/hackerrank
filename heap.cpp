#include<iostream>
#include<climits>

template<typename T>
void swap(T *a, T *b) {
	std::cout << "\nSwapping " << *a << " " << *b;
	T c = *a;
	*a = *b;
	*b = c;
}

template<typename T>
struct MinHeap {
	T *arr;
	int cap;
	int sz;

	MinHeap(int c) {
		sz = 0;
		cap = c;
		arr = new T[cap];
	}

	int parent(int i) {
		return (i-1)/2;
	}

	int min() {
		std::cout<< "\n" << __func__;
		std::cout<< "\n\t rs=" << arr[0];
		return arr[0];
	}

	bool insert(T k) {
		std::cout << "\n" << __func__ << " " << k;
		if (sz == cap) {
			std::cout << "\n\t Reached max capacity";
			return false;
		}

		sz++;
		cap--;
		int i = sz - 1;
		arr[i] = k;

		// fix property
		while (i != 0 && arr[parent(i)] > arr[i]) {
			std::cout << "\n\t" << i;
			swap(&arr[parent(i)], &arr[i]);
			i = parent(i);
		}
		return true;
	}
	
	bool update(T i, T val) {
		std::cout << "\n" << __func__;
		arr[i] = val;
		while (i != 0 && arr[parent(i)] > arr[i]) {
			std::cout << "\n\t" << i;
			swap(&arr[parent(i)], &arr[i]);
			i = parent(i);
		}
		return true;
	}
	void dump() {
		std::cout<< "\n" << __func__;
		for(int i = 0; i < sz; i++) {
			std::cout << " " << arr[i];
		}
	}	
};

int main() {
	MinHeap<int> h(11);
	h.insert(3);
	h.insert(2);
	h.insert(1);
	h.insert(15);
	h.insert(5);
	h.insert(4);
	h.insert(45);
	h.dump();

	h.min();
	h.update(2, -121);
	h.dump();
	h.min();
	std::cout << "\n";
}
