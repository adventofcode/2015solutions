def run
  file = File.open("input", "rb").read
  floor = 0

  file.split(//).each_with_index { |c, index|
    floor+=1 if c == '('
    floor-=1 if c == ')'

    if floor == -1
      puts "Santa enters the basement at position #{index+1}"
      break
    end
  }
end

run
