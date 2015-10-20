# TODO: 
# - Use dynamic programming;
# - Add hygiene.
#

# Random variate, sampling from a gamma distribution.
# (See "The Art of Computer Programming", v. II.)
#
class Array
  def sum
    #self.inject { |sum,x| sum + x }
    self.inject(0, &:+)
  end
end

def round(x, decimals=2)
  x.round(decimals)
end

def rgamma(k, lambd)
  ((1..k).map { -Math.log(rand) / lambd }).sum
end

# Print table header.
#
def header
  "weight x value,   \tsharpe index (=value/volume, value per unit of weight)\n"
end

# Knapsack item with value and weight. There is a metric called `sharpe'
# resembling Sharpe Index, it stands for the value per unit of weight
# associated to this item, value / weight.
#
class Item
  attr_accessor :value, :weight

  def initialize(v, w)
    @value = v
    @weight = w
  end

  def sharpe
    @value / @weight
  end

  def to_s
    "#{@weight} x $#{@value},     \t#{'%.2f' % sharpe}"
  end
end

# Knapsack containing the items. 
# `capacity', `weight', and `value' are self-explanatory and run in O(1)-time.
#
class Knapsack
  attr_accessor :items, :capacity, :weight, :value

  def initialize(capacity)
    @items = []
    @capacity = capacity
    @weight = 0
    @value = 0
  end

  def fits?(item)
    item.weight + @weight <= @capacity
  end

  def <<(item)
    w = item.weight
    if w + @weight <= @capacity
      @items << item
      @weight += w
      @value += item.value
    end
  end

  def >>(item)
    @weight -= item.weight
    @value -= item.value
    @items.delete item
  end

  def to_s
    str = "value: $#{'%.02f' % value}, "
    str += "usage: #{'%.02f' % weight} / #{capacity}\n"
    if @items.count == 0
      str += "(empty)"
    else
      str += header
      str += (@items.each { |x| x.to_s }).join("\n") if @items.count > 0
    end
    str
  end

  # Create a snapshot of the instance and returns it.
  def duplicate
    k = self.dup
    k.items = self.items.dup
    k
  end
end

# Knapsap approximation algorithm.
# (The `$' prefix stands for global variable.)
$best_solution = Knapsack.new(0)
$max_iterations = 5040              # Try other values, say 200.

def knapsack_backtrack(bag, candidates)
  $max_iterations -= 1
  
  candidates.each do |candidate|
    if bag.fits? candidate
      # Add the item.
      bag << candidate

      # Evaluate knapsack. (Don't worry, GC does the dirty work.)
      $best_solution = bag.duplicate if bag.value > $best_solution.value

      # Backtrack.
      knapsack_backtrack(bag, candidates - [candidate]) if $max_iterations > 0

      # Remove the item. (todo: check if pop operation runs in constant time.)
      bag >> candidate
    end
  end
end

# Problem's instance:
# 50 randomly-generated items fill an application, but the knapsack's weight
# capacity is only 20.
# 
bag_capacity = 20

items = []
(1..50).each do
  items << Item.new(round(rgamma(15, 1)), round(0.1 + rgamma(1, 0.12)))
end

# Ace in the hole: sort descentantly by sharpe ratio ignoring ineligible items.
items = items.sort_by(&:sharpe).reverse.select { |x| x.weight <= bag_capacity }

# Solve.
knapsack_backtrack(Knapsack.new(bag_capacity), items)

# Report.
puts "List of candidate items:", header,
  (items.each { |item| item.to_s }).join("\n"), "\n"
puts "Bag capacity: ", bag_capacity, "\n"
puts "Aproximate solution:", $best_solution.to_s
