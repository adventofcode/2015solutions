def get_surface_area l, w, h
  a = 2 * l * w
  b = 2 * w * h
  c = 2 * h * l
  return a + b + c
end

def run
  file = File.open("input1", "rb").read
  file.gsub!(/\r\n?/, "\n")

  total = 0

  file.each_line { |line|
    smallest = nil

    parts  = line.split('x').map(&:to_i)
    length = parts[0]
    width  = parts[1]
    height = parts[2]

    next if parts.count < 3

    sa = get_surface_area length, width, height

    parts.sort.first(2).each { |x|
      if smallest.nil?
        smallest = x
      else
        smallest *= x
      end
    }

    total += sa += smallest
  }

  puts "Total square feet is #{total}"
end

run
