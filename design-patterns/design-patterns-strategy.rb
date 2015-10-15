class Food
  def type
    raise NotImplementedError, 'Ask the subclass'
  end
end

class HotDog < Food
  def type
    'hot dogs'
  end
end

class Hamburger < Food
  def type
    'hamburgers'
  end
end

class VeggiePatty < Food
  def type
    'veggie patties'
  end
end

class Grill
  attr_accessor :food

  def initialize food
    @food = food
  end

  def grilling
    "Grilling the #{food.type}!"
  end
end

grill = Grill.new(HotDog.new)
puts grill.grilling

grill.food = Hamburger.new
puts grill.grilling

grill.food = VeggiePatty.new
puts grill.grilling
