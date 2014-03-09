#!/usr/bin/env ruby

require 'csv'
require 'curses'
include Curses

width = 73
height = 32

mydata = CSV.new(ARGF.read)
coords = Array.new
$xmax,$xmin,$ymax,$ymin = 0,0,0,0
mydata.each do |pair|
  #puts pair[1], pair[2]
  $xmax = (pair[1].to_f)+1 if ($xmax < pair[1].to_f)
  $xmin = (pair[1].to_f)-1 if ($xmin > pair[1].to_f)
  $ymax = (pair[2].to_f)+1 if ($ymax < pair[2].to_f)
  $ymin = (pair[2].to_f)-1 if ($ymin > pair[2].to_f)
  coords.push pair
end
puts $xmax,$xmin,$ymax,$ymin
$xscale,$yscale = 1,1
  $xscale = 1.0/(($xmax.abs+$xmin.abs)/width.to_f) if ((($xmax.abs+$xmin.abs)/width.to_f) != 0)
  $yscale = 1.0/(($ymax.abs+$ymin.abs)/height.to_f) if ((($ymax.abs+$ymin.abs)/height.to_f) != 0)
puts $xscale, $yscale
def plot(x,y)
  clear
  xx = (x-$xmin)*$xscale
  yy = (y-$ymin)*$yscale
  #puts xx,yy
  setpos(yy.to_i,xx.to_i)
  addstr("X (#{x.to_i},#{y.to_i})")
  refresh
end
puts mydata
init_screen
begin
  crmode
  nl
  coords.each do |pair|
    #puts pair[0].to_f().to_s().ljust(6,'0') + "#"*(pair[1].to_i*(10.0/74.0)+37)
    plot(pair[1].to_f,pair[2].to_f)
    refresh
    sleep 0.5
  end
  puts 'hi'
ensure
  close_screen
end
