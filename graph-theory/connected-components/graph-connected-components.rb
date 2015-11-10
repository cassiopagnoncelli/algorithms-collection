# Find and union.
#
class DisjointSet
  attr_accessor :universe

  def initialize
    @universe = []
  end

  def make_set(x)
    @universe.push([x])
  end

  def union(x, y)
    s_x = find_set(x)
    s_y = find_set(y)

    s_x.concat(s_y)

    @universe.delete(s_y)
  end

  def find_set(x)
    @universe.each do |s|
      return s if s.include?(x)
    end
    nil
  end

  # Application: connected components in a graph.
  #

  def connected_components(nodes, edges)
    nodes.each { |v| make_set(v) }
    edges.each { |e| union(e[0], e[1]) if find_set(e[0]) != find_set(e[1]) }
  end

  def same_component(u, v)
    find_set(u) == find_set(v)
  end

  def print_components
    @universe.each_with_index { |s, i| puts "#{i}: #{s.join(' | ')}" }
  end
end

# Node.
#
class Node
  attr_accessor :name
  attr_accessor :visited

  def initialize(name)
    @name = name
    @visited = false
    @gamma = Array.new(0)
  end

  def to_s
    @name
  end

  def connect(x)
    @gamma.push(x) unless @gamma.include?(x)
  end

  def connected?(x)
    @gamma.include?(x)
  end
end

def connect(a, b)
  a.connect(b)
  b.connect(a)
end

def connected?(a, b)
  a.connected?(b)
end

# Graph.
#
porto_alegre = Node.new("porto alegre")
florianopolis = Node.new("florianopolis")
curitiba = Node.new("curitiba")
sao_paulo = Node.new("sao paulo")
rio_de_janeiro = Node.new("rio de janeiro")
salvador = Node.new("salvador")
brasilia = Node.new("brasilia")
manaus = Node.new("manaus")
recife = Node.new("recife")
buenos_aires = Node.new("buenos aires")
amsterdam = Node.new("amsterdam")
paris = Node.new("paris")
london = Node.new("london")

connect(porto_alegre, florianopolis)
connect(porto_alegre, curitiba)
connect(florianopolis, buenos_aires)
connect(curitiba, sao_paulo)
connect(sao_paulo, rio_de_janeiro)
connect(salvador, recife)
connect(salvador, manaus)
connect(brasilia, salvador)
connect(amsterdam, paris)
connect(paris, london)

$nodes = [
  porto_alegre, florianopolis, curitiba, sao_paulo, rio_de_janeiro,
  salvador, brasilia, manaus, recife, buenos_aires, amsterdam, paris, london
]

$edges = [
  [porto_alegre, florianopolis],
  [porto_alegre, curitiba],
  [florianopolis, buenos_aires],
  [curitiba, sao_paulo],
  [sao_paulo, rio_de_janeiro],

  [salvador, recife],
  [salvador, manaus],
  [brasilia, salvador],

  [amsterdam, paris],
  [paris, london]
]

# Connected components.
dset = DisjointSet.new

dset.connected_components($nodes, $edges)
dset.print_components
puts

puts "sp ~> rj: #{dset.same_component(sao_paulo, rio_de_janeiro)}"
puts "curitiba ~> london: #{dset.same_component(curitiba, london)}"
