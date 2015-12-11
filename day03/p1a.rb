def run
  file = File.open("input1", "rb").read
  total = 1
  data = []
  a = b = 0

  file.split(//).each { |c|
    can_add = true

    case c
    when '^'
      a += 1
    when '<'
      b += 1
    when 'v'
      a -= 1
    when '>'
      b -= 1
    else
      break
    end

    data.each { |x|
      if a == x["a"] && b == x["b"]
        can_add = false
      end
    }

    if can_add
      total += 1
      data << {"a" => a, "b" => b}
    end
  }

  puts "#{total} houses received more than 1 present"
end

run
