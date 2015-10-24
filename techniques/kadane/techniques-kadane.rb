#
# Kadane's algorithm solves the problem of finding the maximum contiguous
# subsequence in a one-dimensional sequence.
#

def kadane(x)
  max_sum = -1000000000      # -Infinite
  max_start_index = 0
  max_end_index = 0
  current_max_sum = 0
  current_start_index = 1

  (0..(x.length-1)).each do |current_end_index|
    current_max_sum += x[current_end_index]
    if current_max_sum > max_sum
      max_sum = current_max_sum
      max_start_index = current_start_index
      max_end_index = current_end_index
    end

    if current_max_sum < 0
      current_max_sum = 0
      current_start_index = current_end_index + 1
    end
  end

  return [max_sum, max_start_index, max_end_index]
end

sample = [-1, -4, 3, 4, 0, -1, -15, 3, -8, -4, 1]
result = kadane(sample)

puts sample.inspect
puts "sum=#{result[0]}, start=#{result[1]}, end=#{result[2]}"
