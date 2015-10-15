require 'matrix'

class Array
  def sum
    self.inject(0, &:+)
  end
end

def rbernoulli(p)
  rand < p ? 1 : 0
end

def rbinomial(n, p)
  ((1..n).map { rbernoulli(p) }).sum
end

# Node represents its id and its neighborhood (gamma) only.
#
class Node
  attr_accessor :id, :gamma

  def initialize(id)
    @id = id
    @gamma = []
  end

  def degree
    @gamma.length
  end

  def duplicate
    new_node = this.dup
    new_node.gamma = @gamma.dup
    new_node
  end
end

# Graph.
#
class Graph
  attr_accessor :nodes, :max_degree

  def initialize(list_of_nodes = [])
    @nodes = list_of_nodes
  end

  # Generate a random graph.
  def random(num_nodes = 100, degree_seed = 10)
    # Generate nodes.
    0.upto(num_nodes - 1).each do |i|
      @nodes << Node.new(i)
    end

    # Generate edges.
    0.upto(num_nodes - 1).each do |node_1|
      num_edges = rbinomial(2 * degree_seed, 0.5)
      0.upto(num_edges - 1).each do |i|
        node_2 = rand(num_nodes)
        @nodes[node_1].gamma << node_2 unless @nodes[node_1].gamma.include? node_2
        @nodes[node_2].gamma << node_1 unless @nodes[node_2].gamma.include? node_1
      end
    end

    # Sort nodes
    @nodes.each do |v|
      v.gamma = v.gamma.sort
    end

    # Calculates maximum degree
    @max_degree = 0
    @nodes.each do |v|
      @max_degree = v.gamma.length if v.gamma.length > @max_degree
    end
  end

  def ostergard_input
    s = 0
    @nodes.each { |n| s += n.gamma.length }

    puts "#{@nodes.length} #{s}"
    @nodes.each do |v|
      puts "1 #{v.gamma.length} " + v.gamma.join(" ")
    end
  end

  def to_s
    str = ""
    0.upto(@nodes.length - 1).each do |i|
      str += "node #{i} has #{@nodes[i].gamma.length} neighbors: "
      str += @nodes[i].gamma.join(" ") + "\n"
    end
    str
  end
end

# Instance.
g = Graph.new
g.random(250, 145)

# Find maximum clique.
max_clique = g.maximum_clique

# Report.
puts "-- Graph --", g.to_s, "\n"
#g.ostergard_input
