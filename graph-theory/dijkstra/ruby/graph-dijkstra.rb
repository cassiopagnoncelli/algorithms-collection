$Infinite = 1 << 30

class Graph
  def initialize(path)
    file = File.new(path, 'r')

    @m = []
    while (line = file.gets)
      row = line.split(' ')
      row.map! { |x| x.to_i == 0 ? $Infinite : x.to_i }
      @m.push(row)
    end
    file.close

    rows = @m.length
    raise IncorrectDimensions unless rows > 0
    @m.each { |row| raise IncorrectDimensions unless row.length == rows }
  end

  def find_min_index(q, dist)
    m = 0
    q.each_index { |i| m = i if dist[q[i]] < dist[q[m]] }
    m
  end

  def dijkstra(src)
    dist = Array.new(@m.length) { $Infinite }
    previous = Array.new(@m.length) { nil }
    q = 0.upto(@m.length - 1).to_a

    dist[src] = 0

    until q.empty?
      u_idx = find_min_index(q, dist)
      u = q[u_idx]
      q.delete_at(u_idx)

      @m[u].each_index do |v|
        alt = dist[u] + @m[u][v]
        if alt < dist[v]
          dist[v] = alt
          previous[v] = u
        end
      end
    end

    [dist, previous]
  end

  def neighbors(node)
    @m[node]
  end

  def [](row, col)
    @m[row][col]
  end
  
  def print
    @m.each do |row|
      newrow = row.map { |e| e == $Infinite ? '-' : e }
      puts newrow.join(' ')
    end
  end
end

graph = Graph.new("graph-dijkstra.txt")
source = 0
dijkstra = graph.dijkstra(source)

puts "Graph g"
graph.print

puts "\nDijkstra(g, #{source}) = " + dijkstra.inspect

puts "\nInterpretation"
puts "Shortest paths:"
dijkstra[0].each_index do |cost_idx|
  puts "from #{source} to #{cost_idx} costs #{dijkstra[0][cost_idx]}"
end

puts "\nStructure:"
dijkstra[1].each_index do |i|
  if dijkstra[1][i] != nil
    puts "Antecessor node of #{i} is #{dijkstra[1][i]}"
  else
    puts "Node #{i} has no antecessor"
  end
end
