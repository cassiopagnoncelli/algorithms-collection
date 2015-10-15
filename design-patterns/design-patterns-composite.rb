# Superclass.
#
class CoffeeRoutine
  attr_reader :task

  def initialize(task)
    @task = task
  end

  def time
    0.0
  end
end

# Simple routines: GrindCoffe, BoilWater, and AddCoffee.
#
class GrindCoffee < CoffeeRoutine
  def initialize
    super 'Grinding some coffee!'
  end

  def time
    0.5
  end
end

class BoilWater < CoffeeRoutine
  def initialize
    super 'Boiling some water!'
  end

  def time
    4.0
  end
end

class AddCoffee < CoffeeRoutine
  def initialize
    super 'Adding in the coffee!'
  end

  def time
    1.0
  end
end

class PressPlunger < CoffeeRoutine
  def initialize
    super 'Pressing the plunger.'
  end

  def time
    0.4
  end
end

class PressStartButton < CoffeeRoutine
  def initialize
    super 'Pressing Start button.'
  end

  def time
    0.3
  end
end

# Composite: FrenchPress.
# Components: BoilWater, GrindCoffee, AddCoffee.
#
# (Simple version.)
#
#class FrenchPress < CoffeeRoutine
#  attr_reader :task, :steps
#
#  def initialize(task)
#    super 'Using the French press to make coffee'
#    @steps = []
#    add_step BoilWater.new
#    add_step GrindCoffee.new
#    add_step AddCoffee.new
#  end
#
#  def add_step(step)
#    steps << step
#  end
#
#  def remove_step(step)
#    steps.delete step
#  end
#
#  def time_required
#    total_time = 0.0
#    steps.each { |step| total_time += step.time }
#    total_time
#  end
#end

# Abstract composite: CompositeTasks.
# Components are dynamic and can be put by derived classes.
# 
class CompositeTasks < CoffeeRoutine
  attr_reader :task, :steps

  def initialize(task)
    @steps = []
  end

  def add_step(step)
    steps << step
  end

  def remove_step(step)
    steps.delete step
  end

  def time_required
    total_time = 0.0
    steps.each { |step| total_time += step.time }
    total_time
  end
end

# Composite: FrenchPress.
# This is a newer version of the old one using the CompositeTasks abstract.
# 
class FrenchPress < CompositeTasks
  def initialize
    super 'Using the FrenchPress to make coffee!!!'
    add_step GrindCoffee.new
    add_step BoilWater.new
    add_step AddCoffee.new
    # ... Omitted actual steps to make coffee from a French press ...
    # ... Imagine PressPlunger class has been defined already ...
    add_step PressPlunger.new
  end
end

# Composite: DripMaker
# Components: GrindCoffee, BoilWater, AddCoffee, and PressStartButton.
#
class DripMaker < CompositeTasks
  def initialize
    super 'Using the DripMaker to make coffee!!!'
    add_step GrindCoffee.new
    add_step BoilWater.new
    add_step AddCoffee.new
    # ... Imagine PressStartButton class has been defined already ...
    add_step PressStartButton.new
  end
end

# Instance.
frenchpress = FrenchPress.new
dripmaker = DripMaker.new

puts frenchpress.inspect
puts dripmaker.inspect

puts "French press time: ", frenchpress.time_required
puts "Drip maker time: ", dripmaker.time_required

