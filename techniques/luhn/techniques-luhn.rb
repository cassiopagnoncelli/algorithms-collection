# Input account number.
account_number = "1954348249615"

# Calculate check digit.
numbers = 0.upto(account_number.length - 1).map { |i| account_number[i].to_i }
doubles = numbers.map { |x| 2*x }
sums_of_digits = doubles.map { |x| x < 10 ? x : x - 9 }
check_digit = sums_of_digits.inject(0, &:+) * 9 % 10

# Report.
puts "Account number: #{account_number}"
puts "Check digit: #{check_digit}"
