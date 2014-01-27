#!/usr/bin/env ruby

require 'csv'
mydata = CSV.new(ARGF.read)
data = mydata.each do |pair|
  puts pair[0].to_f().to_s().ljust(6,'0') + "#"*(pair[1].to_i*(10.0/74.0)+37)
end
puts data
