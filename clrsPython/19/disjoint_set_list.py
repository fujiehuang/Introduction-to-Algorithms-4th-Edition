#!/usr/bin/env python3
"""Disjoint-set data structure maintains a collection of disjoint dynamic sets.
We identify each set by a representative.
"""


class DisjointSetListNode:

	def __init__(self, data):
		""" Initialize a node in disjoint set linked list implementation. """
		self.data = data
		self.next = None  # linked list next pointer
		self.list = None  # pointer to the DisjointSetList object

	def __str__(self):
		"""Return string representation of data in node."""
		return str(self.data)


class DisjointSetList:

	def __init__(self, node):
		"""Initialize the list implementation of 
		a disjoint set with one node."""
		self.head = node  # linked list head
		self.tail = node  # linked list tail
		self.size = 1

	def __str__(self):
		"""Return the string representation of the list."""
		result = ""
		x = self.head
		while x is not None:
			result += str(x) + " "
			x = x.next
		return result


def make_set(x):
	"""Create a new set whose only member is x."""
	node = DisjointSetListNode(x)
	node.list = DisjointSetList(node)
	return node


def find_set(x):
	"""Return the pointer to the representative of unique set containing x."""
	return x.list.head


def union(x, y):
	"""Unite sets x and y by appending the smaller set to the larger set.

	Arguments:
	x -- a node in one set
	y -- a node in other set
	"""
	x_set = x.list
	y_set = y.list
	if x_set.size <= y_set.size:
		append(x_set, y_set)  # append x's list to the end of y's list
	else:
		append(y_set, x_set)  # append y's list to the end of x's list


def append(first, second):
	"""Append the first DisjointSetList to the second."""
	# Check that neither set is empty. 
	if first.size == 0 or second.size == 0:
		raise RuntimeError("Cannot append empty sets.")

	# Set the DisjointSetList of each node in first set to be second set.
	x = first.head
	while x is not None:
		x.list = second
		x = x.next

	# Insert first set onto the end of the second.
	second.tail.next = first.head
	second.tail = first.tail
	second.size += first.size  # increase the size

	# Invalidate the first set.
	first.head = None
	first.tail = None
	first.size = None


# Testing
if __name__ == "__main__":

	node1 = make_set(1)
	print(find_set(node1))
	print(node1.list)
	node2 = make_set(2)
	union(node1, node2)
	print(find_set(node2))
	print(node2.list)
	node3 = make_set(3)
	union(node3, node1)
	print(find_set(node3))
	print(node3.list)
	for i in range(4, 20):
		union(make_set(i), node1)
	print(find_set(node1))
	print(node1.list)
