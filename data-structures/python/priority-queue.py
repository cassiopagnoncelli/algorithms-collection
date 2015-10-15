##
## Min priority queue.
## To switch to a max heap just negate priorities: priority becomes -priority.
##

import Queue

q = Queue.PriorityQueue()

## Key.
q.put(10)
q.put(24)
q.put(12)
q.put(11)
q.put(16)

while not q.empty():
	print q.get()

## Tuple.
q.put((10, 'ten'))
q.put((5, 'five'))
q.put((7, 'seven'))
q.put((6, 'six'))

while not q.empty():
	print q.get()

## OO
class Skill(object):
	def __init__(self, priority, description):
		self.priority = priority
		self.description = description
		print 'New Level:', description
		return
	def __cmp__(self, other):
		return cmp(self.priority, other.priority)

q.put(Skill(5, 'Proficient'))
q.put(Skill(10, 'Expert'))
q.put(Skill(1, 'Novice'))

while not q.empty():
	next_level = q.get()
	print 'Processing level:', next_level.description

##
## heapq
##
import heapq

heap = []
heapq.heappush(heap, (1, 'one'))
heapq.heappush(heap, (10, 'ten'))
heapq.heappush(heap, (5,'five'))

for x in heap:
	print x,
print

heapq.heappop(heap)

for x in heap:
	print x,
print 

# the smallest
print heap[0]
