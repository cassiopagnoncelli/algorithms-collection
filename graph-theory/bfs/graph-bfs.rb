#!/usr/bin/env ruby

class Node
  attr_accessor :name
  attr_accessor :marked

  def initialize(name)
    @name = name
    @marked = false
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

  def neighbors
    @gamma
  end

  def mark
    @marked = true
  end
end

def connect(a, b)
  a.connect(b)
  b.connect(a)
end

def connected?(a, b)
  a.connected?(b)
end

# Nodes.
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

# Connections.
connect(porto_alegre, florianopolis)
connect(porto_alegre, curitiba)
connect(porto_alegre, sao_paulo)
connect(porto_alegre, rio_de_janeiro)
connect(florianopolis, curitiba)
connect(florianopolis, sao_paulo)
connect(florianopolis, buenos_aires)
connect(curitiba, sao_paulo)
connect(curitiba, rio_de_janeiro)
connect(curitiba, brasilia)
connect(sao_paulo, rio_de_janeiro)
connect(sao_paulo, salvador)
connect(sao_paulo, brasilia)
connect(sao_paulo, manaus)
connect(sao_paulo, recife)
connect(sao_paulo, buenos_aires)
connect(sao_paulo, amsterdam)
connect(sao_paulo, paris)
connect(sao_paulo, london)
connect(rio_de_janeiro, salvador)
connect(rio_de_janeiro, brasilia)
connect(rio_de_janeiro, manaus)
connect(rio_de_janeiro, recife)
connect(rio_de_janeiro, buenos_aires)
connect(rio_de_janeiro, amsterdam)
connect(rio_de_janeiro, paris)
connect(rio_de_janeiro, london)
connect(salvador, recife)
connect(salvador, manaus)
connect(brasilia, buenos_aires)
connect(brasilia, paris)
connect(brasilia, london)
connect(buenos_aires, paris)
connect(buenos_aires, london)
connect(amsterdam, paris)
connect(amsterdam, london)
connect(paris, london)

# Search algorithm.
def bfs(src)
  queue, visited = [], []
  queue.push(src)
  visited.push(src)
  until queue.empty?
    x = queue.shift
    puts x.name
    x.neighbors.each do |neighbor|
      unless visited.include?(neighbor)
        visited.push(neighbor)
        queue.push(neighbor)
      end
    end
  end
end

bfs(porto_alegre)
