#
# Minimum Priority Queue.
#
# For a max priority queue, just set priority to -priority at the tuple.
#
from heapq import *

# Heap sort.
def hsort(l):
	h = []
	map(lambda i: heappush(h, i), l)
	return map(lambda x: heappop(h), range(len(h)))

heap = []

# Push. (Populate.)
# Push changes the array pointed by `heap'.
def populate(heap):
	heappush(heap, (6, 'six'))
	heappush(heap, (3, 'three'))
	heappush(heap, (8, 'eight'))
	heappush(heap, (1, 'one'))
	heappush(heap, (5, 'five'))
	heappush(heap, (7, 'seven'))
	heappush(heap, (2, 'two'))
	heappush(heap, (4, 'four'))
	heappush(heap, (9, 'nine'))

print "Pushing 1-9"
populate(heap)
print "--"

# Pop.
print "Popping 1-9"
for i in range(len(heap)):
	print heappop(heap)
print "--"

# Random access.
populate(heap)
print "Head without popping:", heap[0]
print "Head again:", heap[0]
print "--"

# Heap sort.
print "Sorted version:\n", hsort(heap)
print "--"

# Pushpop inserts the given elements and pops its minimum.
# Popped element can be the newly inserted element.
print "Pushpopping 'zero' (first pushes, then pops)"
print heappushpop(heap, (0, 'zero'))
print "remaining:", heappop(heap), heappop(heap), heappop(heap), "..."
print "--"

# Heapreplace.
# Popped element can NOT be the newly inserted element as heap first pops then pushes.
heap = []
populate(heap)
print "Heapreplace 'zero' (first pops, then pushes)"
print heapreplace(heap, (0, 'zero'))
print "remaining:", heappop(heap), heappop(heap), heappop(heap), "..."
print "--"

# N largest and N smallest
heap = []
populate(heap)

print "Largest 3:", nlargest(3, heap)
print "Smallest 3:", nsmallest(3, heap)
print "--"

# Heapify
v = [5, 8, 1, 3, 7, 6, 9, 2, 4]
print "Heapify makes a heap out of a vector in time, in-place."
print "Vector:", v, "-> Pops before heapify:", map(lambda x: heappop(v), range(len(v)))

v = [5, 8, 1, 3, 7, 6, 9, 2, 4]
heapify(v)
print "Vector:", v, "-> Pops after heapify: ", map(lambda x: heappop(v), range(len(v)))
print "--"

# Merge
print "Merge sorted sequences"
A = sorted([5, 1, 9, 7, 6])
B = sorted([2, 4, 3, 8])
AB = merge(A, B)
print "A:", A
print "B:", B
print "A+B:", list(AB)
print "A+B again:", list(AB)
