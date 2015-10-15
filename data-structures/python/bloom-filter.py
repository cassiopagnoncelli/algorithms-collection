from bitarray import bitarray
import mmh3

# Bloom filter.
#
# m: size of bit array
# n: expected number of items
# p: probability percentage represented as a decimal
#
# Formula for the size of the bit array:
#
#   m = - n ln p / (ln 2)^2
#
# Number of hashes to use:
#
#   k = - (m/n) ln 2
#
# False positive probability:
#
#   fp = (1 - (1 - 1/m)^{k n})^k.
# 
class BloomFilter:
	def __init__(self, size, hash_count):
		self.size = size
		self.hash_count = hash_count
		self.bit_array = bitarray(size)
		self.bit_array.setall(0)
	
	def add(self, string):
		for seed in xrange(self.hash_count):
			result = mmh3.hash(string, seed) % self.size
			self.bit_array[result] = 1
	
	def lookup(self, string):
		for seed in xrange(self.hash_count):
			result = mmh3.hash(string, seed) % self.size
			if self.bit_array[result] == 0:
				return "Nope"
		return "Probably"

# Create a bloom filter and add American English dictionary.
bf = BloomFilter(500000, 7)
 
lines = open("/usr/share/dict/american-english").read().splitlines()
for line in lines:
	bf.add(line)

print bf.lookup("google")
print bf.lookup("Max")
print bf.lookup("mice")
print bf.lookup("3")
