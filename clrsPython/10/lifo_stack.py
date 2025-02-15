#!/usr/bin/env python3
import numpy as np

class Stack:
	def __init__(self, n=4):
		"""Initialize a stack with an array of length n."""
		self.stack = [None] * n
		self.size = n
		self.top = -1 	# index of the top element

	def is_empty(self):
		"""Return a boolean indicating whether the stack is empty."""
		return self.top == -1

	def push(self, x):
		"""Add an element to the top of the stack."""
		if self.top == self.size - 1:
			raise RuntimeError("Stack overflow")
		else:
			self.top += 1
			self.stack[self.top] = x

	def pop(self):
		"""Remove the top element from the stack and return it."""
		if self.is_empty():
			raise RuntimeError("Stack underflow.")
		else:
			self.top -= 1
			return self.stack[self.top + 1]

	def __str__(self):
		"""Print the stack up to top element."""
		return str(self.stack[:self.top + 1])


# Testing
if __name__ == "__main__":

	stack1 = Stack(5)
	print(stack1)
	stack1.push(1)
	print(stack1)  # one element: 1
	stack1.push(2)
	stack1.push(100)
	print(stack1)  # three elements: 1, 2, 100
	print(stack1.pop()) 	# pop 100 out
	print(stack1)
	print(stack1.pop()) 	# pop 2 out
	print(stack1.pop()) 	# pop 1 out
	print(stack1.is_empty())  # should be true
	try:
		stack1.pop() 	# error when popping empty stack
	except RuntimeError as e:
		print(e)

	# Check for overflow.
	stack2 = Stack(10)
	for i in range(11):
		try:
			stack2.push(i)
		except RuntimeError as e:
			print(e)
	print(stack2)