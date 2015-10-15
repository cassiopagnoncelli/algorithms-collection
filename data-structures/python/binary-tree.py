class Node(object):
	def __init__(self, element):
		self.x = element
		self.left = None
		self.right = None
	def insert(self, x):
		if self.x == x:
			return False
		elif x < self.x:
			if self.left:
				return self.left.insert(x)
			else:
				self.left = Node(x)
				return True
		else:
			if self.right:
				return self.right.insert(x)
			else:
				self.right = Node(x)
				return True
	def find(self, x):
		if self.x == x:
			return True
		elif x < self.x:
			return self.left.find(x) if self.left else False
		else:
			return self.right.find(x) if self.right else False
	def __repr__(self):
		l = self.left.__repr__() if self.left else ''
		r = self.right.__repr__() if self.right else ''
		return '({root},{left},{right})'.format(root=self.x, left=l, right=r)

elems = [8, 1, 6, 4, 9, 2, 4, 3, 7]
bt = Node(5)
for x in elems:
	bt.insert(x)

print bt
