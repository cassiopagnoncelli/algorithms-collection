require 'minitest/autorun'

# Simple wall.
class SimpleWall
  def initialize
  end

  def dimensions
    'I am 30 ft long and 20 ft wide.'
  end

  def made_from
    'I am made from brick.'
  end
end

# Blueprints for a simple wall.
describe SimpleWall do
  let(:wall) { SimpleWall.new }

  it 'should state its dimensions' do
    wall.dimensions.must_equal 'I am 30 ft long and 20 ft wide.'
  end

  it 'should be made of brick' do
    wall.made_from.must_equal 'I am made from brick.'
  end
end

#-----------------------------------------------------------------------------
# Template pattern.
#-----------------------------------------------------------------------------

class Wall
  def dimensions
    "I am #{length}ft. long and #{width}ft. wide!"
  end

  def made_from
    "I am made from #{material}!"
  end

  private

  def length
    raise NotImplementedError, 'Sorry, you have to override length'
  end
  
  def length
    30
  end
end

class BrickWall < Wall
  private

  def width
    20
  end

  def material
    'brick'
  end
end

class ConcreteWall < Wall
  private

  def width
    20
  end

  def material
    'concrete'
  end
end

class WoodWall < Wall
  private 

  def length
    10
  end

  def width
    20
  end

  def material
    'wood'
  end
end

# Blueprints for a BrickWall
describe BrickWall do
  let(:brick_wall) { BrickWall.new }

  it 'should state its dimensions' do
    brick_wall.dimensions.must_equal 'I am 30ft. long and 20ft. wide!'
  end

  it 'should be made from brick' do
    brick_wall.made_from.must_equal 'I am made from brick!'
  end
end

# Blueprints for a ConcreteWall
describe ConcreteWall do
  let(:concrete_wall) { ConcreteWall.new }

  it 'should state its dimensions' do
    concrete_wall.dimensions.must_equal 'I am 30ft. long and 20ft. wide!'
  end

  it 'should be made from concrete' do
    concrete_wall.made_from.must_equal 'I am made from concrete!'
  end
end

# Blueprints for a WoodWall
describe WoodWall do
  let(:wood_wall) { WoodWall.new }

  it 'should state its dimensions' do
    wood_wall.dimensions.must_equal 'I am 10ft. long and 20ft. wide!'
  end

  it 'should be made from wood' do
    wood_wall.made_from.must_equal 'I am made from wood!'
  end
end
