# Array
x = [1,2,3,4]

# Generate powerset
powerset = (0.upto(x.length).collect { |k| x.combination(k).to_a }).flatten(1)

puts powerset.inspect
