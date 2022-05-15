#include <list>
#include "binomial_heap.hpp"

int main()
{
	// BinHeap test

	int ch, key;
	list<Node *> _heap;

	// Insert data in the heap
	_heap = insert(_heap, 10);
	_heap = insert(_heap, 20);
	_heap = insert(_heap, 30);

	cout << "Heap elements after insertion:\n";
	printHeap(_heap);

	Node *temp = getMin(_heap);
	cout << "\nMinimum element of heap "
		 << temp->data << "\n";

	// Delete minimum element of heap
	_heap = extractMin(_heap);
	cout << "Heap after deletion of minimum element\n";
	printHeap(_heap);

	return 0;
}