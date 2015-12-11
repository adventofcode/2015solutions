def run
  file = File.open("input1", "rb").read
  total = 0
  santa = []
  robosanta = []
  sa = sb = ra = rb = 0

  issanta = true

  file.split(//).each { |c|
    case c
    when '^'
      sa += 1 if issanta
      ra += 1 if !issanta
    when '<'
      sb += 1 if issanta
      rb += 1 if !issanta
    when 'v'
      sa -= 1 if issanta
      ra -= 1 if !issanta
    when '>'
      sb -= 1 if issanta
      rb -= 1 if !issanta
    else
      break
    end

    if issanta
      hash = {"sa" => sa, "sb" => sb}
      if !santa.include? hash and !robosanta.include? hash
        total += 1
        santa << hash
      end
    else
      hash = {"sa" => ra, "sb" => rb}
      if !santa.include? hash and !robosanta.include? hash
        total += 1
        robosanta << hash
      end
    end

    issanta = !issanta
  }

  puts "#{total} houses received more than 1 present"
end

run
