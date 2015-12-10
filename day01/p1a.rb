def run
  file = File.open("input", "rb").read
  floor = 0

  file.split(//).each { |c|
    floor+=1 if c == '('
    floor-=1 if c == ')'
  }

  puts "The instructions take you to floor #{floor}"
end

run
