#include <list>
#include "binomial_heap.hpp"
#include "complex_number.hpp"

int main()
{
	// BinHeap test

	int ch, key;
	list<Node<ComplexNumber> *> _heap;

	// Insert data in the heap
	_heap = insert<ComplexNumber>(_heap, {1, 2});
	_heap = insert<ComplexNumber>(_heap, {3, 5});
	_heap = insert<ComplexNumber>(_heap, {-7, 10});

	cout << "Heap elements after insertion:\n";
	printHeap(_heap);

	Node<ComplexNumber> *temp = getMin(_heap);
	cout << "\nMinimum element of heap "
		 << temp->data << "\n";

	// Delete minimum element of heap
	_heap = extractMin(_heap);
	cout << "Heap after deletion of minimum element\n";
	printHeap(_heap);

	return 0;
}