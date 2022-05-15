
#ifndef _BHEAP_
#define _BHEAP_

#include <iostream>
#include <list>
using namespace std;

// A Binomial Tree node.
template <typename T>
struct Node
{
	T data;
	int degree;
	Node *child, *sibling, *parent;
};

template <typename T>
Node<T> *newNode(T key)
{
	auto *temp = new Node<T>;
	temp->data = key;
	temp->degree = 0;
	temp->child = temp->parent = temp->sibling = NULL;
	return temp;
}

// This function merge two Binomial Trees.
template <typename T>
Node<T> *mergeBinomialTrees(Node<T> *b1, Node<T> *b2)
{
	// Make sure b1 is smaller
	if (b1->data > b2->data)
		swap(b1, b2);

	// We basically make larger valued tree
	// a child of smaller valued tree
	b2->parent = b1;
	b2->sibling = b1->child;
	b1->child = b2;
	b1->degree++;

	return b1;
}

// This function perform union operation on two
// binomial heap i.e. l1 & l2
template <typename T>
list<Node<T> *> unionBionomialHeap(list<Node<T> *> l1, list<Node<T> *> l2)
{
	// _new to another binomial heap which contain
	// new heap after merging l1 & l2
	list<Node<T> *> _new;
	auto it = l1.begin();
	auto ot = l2.begin();
	while (it != l1.end() && ot != l2.end())
	{
		// if D(l1) <= D(l2)
		if ((*it)->degree <= (*ot)->degree)
		{
			_new.push_back(*it);
			it++;
		}
		// if D(l1) > D(l2)
		else
		{
			_new.push_back(*ot);
			ot++;
		}
	}

	// if there remains some elements in l1
	// binomial heap
	while (it != l1.end())
	{
		_new.push_back(*it);
		it++;
	}

	// if there remains some elements in l2
	// binomial heap
	while (ot != l2.end())
	{
		_new.push_back(*ot);
		ot++;
	}
	return _new;
}

// adjust function rearranges the heap so that
// heap is in increasing order of degree and
// no two binomial trees have same degree in this heap
template <typename T>
list<Node<T> *> adjust(list<Node<T> *> _heap)
{
	if (_heap.size() <= 1)
		return _heap;
	list<Node<T> *> new_heap;
	auto it1 = _heap.begin();
	auto it2 = _heap.begin();
	auto it3 = _heap.begin();

	if (_heap.size() == 2)
	{
		it2 = it1;
		it2++;
		it3 = _heap.end();
	}
	else
	{
		it2++;
		it3 = it2;
		it3++;
	}
	while (it1 != _heap.end())
	{
		// if only one element remains to be processed
		if (it2 == _heap.end())
			it1++;

		// If D(it1) < D(it2) i.e. merging of Binomial
		// Tree pointed by it1 & it2 is not possible
		// then move next in heap
		else if ((*it1)->degree < (*it2)->degree)
		{
			it1++;
			it2++;
			if (it3 != _heap.end())
				it3++;
		}

		// if D(it1),D(it2) & D(it3) are same i.e.
		// degree of three consecutive Binomial Tree are same
		// in heap
		else if (it3 != _heap.end() &&
				 (*it1)->degree == (*it2)->degree &&
				 (*it1)->degree == (*it3)->degree)
		{
			it1++;
			it2++;
			it3++;
		}

		// if degree of two Binomial Tree are same in heap
		else if ((*it1)->degree == (*it2)->degree)
		{
			Node<T> *temp;
			*it1 = mergeBinomialTrees(*it1, *it2);
			it2 = _heap.erase(it2);
			if (it3 != _heap.end())
				it3++;
		}
	}
	return _heap;
}

// inserting a Binomial Tree into binomial heap
template <typename T>
list<Node<T> *> insertATreeInHeap(list<Node<T> *> _heap, Node<T> *tree)
{
	// creating a new heap i.e temp
	list<Node<T> *> temp;

	// inserting Binomial Tree into heap
	temp.push_back(tree);

	// perform union operation to finally insert
	// Binomial Tree in original heap
	temp = unionBionomialHeap(_heap, temp);

	return adjust(temp);
}

// removing minimum key element from binomial heap
// this function take Binomial Tree as input and return
// binomial heap after
// removing head of that tree i.e. minimum element
template <typename T>
list<Node<T> *> removeMinFromTreeReturnBHeap(Node<T> *tree)
{
	list<Node<T> *> heap;
	Node<T> *temp = tree->child;
	Node<T> *lo;

	// making a binomial heap from Binomial Tree
	while (temp)
	{
		lo = temp;
		temp = temp->sibling;
		lo->sibling = NULL;
		heap.push_front(lo);
	}
	return heap;
}

// inserting a key into the binomial heap
template <typename T>
list<Node<T> *> insert(list<Node<T> *> _head, T key)
{
	Node<T> *temp = newNode(key);
	return insertATreeInHeap(_head, temp);
}

// return pointer of minimum value Node
// present in the binomial heap
template <typename T>
Node<T> *getMin(list<Node<T> *> _heap)
{
	auto it = _heap.begin();
	Node<T> *temp = *it;
	while (it != _heap.end())
	{
		if ((*it)->data < temp->data)
			temp = *it;
		it++;
	}
	return temp;
}

template <typename T>
list<Node<T> *> extractMin(list<Node<T> *> _heap)
{
	list<Node<T> *> new_heap, lo;
	Node<T> *temp;

	// temp contains the pointer of minimum value
	// element in heap
	temp = getMin(_heap);
	auto it = _heap.begin();
	while (it != _heap.end())
	{
		if (*it != temp)
		{
			// inserting all Binomial Tree into new
			// binomial heap except the Binomial Tree
			// contains minimum element
			new_heap.push_back(*it);
		}
		it++;
	}
	lo = removeMinFromTreeReturnBHeap(temp);
	new_heap = unionBionomialHeap(new_heap, lo);
	new_heap = adjust(new_heap);
	return new_heap;
}

// print function for Binomial Tree
template <typename T>
void printTree(Node<T> *h)
{
	while (h)
	{
		cout << h->data << " ";
		printTree(h->child);
		h = h->sibling;
	}
}

// print function for binomial heap
template <typename T>
void printHeap(list<Node<T> *> _heap)
{
	auto it = _heap.begin();
	while (it != _heap.end())
	{
		printTree(*it);
		it++;
	}
}

#endif