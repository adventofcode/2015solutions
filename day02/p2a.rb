def run
  file = File.open("input1", "rb").read
  file.gsub!(/\r\n?/, "\n")

  total = 0

  file.each_line { |line|
    perimeter = nil

    parts  = line.split('x').map(&:to_i)
    length = parts[0]
    width  = parts[1]
    height = parts[2]

    next if parts.count < 3

    vl = length * width * height

    parts.sort.first(2).each { |x|
      if perimeter.nil?
        perimeter = x
      else
        perimeter += x
      end
    }

    perimeter*=2

    total += vl += perimeter
  }

  puts "Total feet is #{total}"
end

run
