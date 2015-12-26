def run
  file = File.open("input", "rb").read
  locs = []
  x = y = 0

  # Already at 0,0 so push into locs
  locs.push([0,0])

  file.split(//).each { |d|
    case d
    when '^'
      x += 1
    when 'v'
      x -= 1
    when '<'
      y -= 1
    when '>'
      y += 1
    else
      break
    end

    locs.push([x,y])
  }

  total = locs.uniq.count
  puts "#{total} houses visited"
end

run
