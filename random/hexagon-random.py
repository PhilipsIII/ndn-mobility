# Python Code to generate random positions within areas in a hexagon.
# Slightly modified version implemented by Greg Kuperberg.
#
# http://stackoverflow.com/users/225554/greg-kuperberg
#
# 2014/08/28
# Jairo Eduardo Lopez

import argparse
from math import sqrt
from random import randrange, random
from matplotlib import pyplot

# Vectors that define a hexagon
vectors = [(0,-1),(-sqrt(3.)/2.,.5),(sqrt(3.)/2.,.5)]

# Puts a point within the hexagon.
# center gives the center of the hexagon
# size tells us the length of the side of the hexagon
# side tells us in which rhombus to put the wireless station
# limit [0,1,2] 0 - rhombus 1 will return points on both sides of the X axis
#               1 - rhombus 1 will return points on the negative side
#               2 - rhombus 1 will return points on the positive side
def randinunithex(center, size, side, limit=0):
    #if not randrange(3*size*size+1): return (0,0)
    t = side

    (v1,v2) = (vectors[t], vectors[(t+1)%3])
    (x,y) = (randrange(0,size),randrange(1,size))
    resX = x*v1[0]+y*v2[0]
    resY = x*v1[1]+y*v2[1] + center[1]

    if t == 1:
        if limit == 1:
            if resX > 0:
                    resX = -1 * resX
            elif limit == 2:
                resX = abs(resX) 

    resX += center[0]
    return (resX,resY)

def addT(xs,ys):
    return (xs[0] + ys[0], xs[1] + ys[1])

def frange(start, end=None, inc=None):
    if end == None:
        end = start + 0.0
        start = 0.0

    if inc == None:
        inc = 1.0

    L = []
    while 1:
        next = start + len(L) * inc
        if inc > 0 and next >= end:
            break
        elif inc < 0 and next <= end:
            break
        L.append(next)
        
    return L

# Configure the parser
parser = argparse.ArgumentParser(
    description="Random Hexagon Wireless Network constructor")
parser.add_argument("-r", "--radius",
    help="Radius of the range of the Wireless station (meters)",
    dest="radius", type=float, default=100.0)
parser.add_argument("-x", "--xaxis",
    help="Size of the X axis for the area to use (meters)",
    dest="xaxis", type=float, default=1000.0)
parser.add_argument("-y", "--yaxis",
    help="Size of the Y axis for the area to use (meters)",
    dest="yaxis", type=float, default=1000.0)
parser.add_argument("-w", "--wireless",
    help="Number of wireless stations to put in one hexagon area",
    dest="wireless", type=int, default=6)

# Parse things
args = parser.parse_args()

# Create new variables for easier use
r = args.radius
x = args.xaxis
y = args.yaxis
w = args.wireless

spoints = [ (r*sqrt(3) , 2*r), (0, 5*r) ]
sides = []
resGW = []
resN = []

# Always divided in 3 zones which correspond to 3 rhombus of regular hexagon
# 0 is left rhombus
# 1 is top rhombus - divided by X axis into negative and positive part
# 2 is right rhombus 
perzone = w / 3
remainder = w % 3

for i in xrange(perzone):
    for j in xrange(3):
        sides.append(j)

for i in xrange(remainder):
    sides.append(i)
    
for (x1,y1) in spoints:
    for i in frange(y1, y, 6*r):
        for j in frange(x1, x, 2*r*sqrt(3)):
            center = (j,i) 
            print center
            resGW.append(center)

            for s in sides:
                resN.append(randinunithex(center, r, s))

for i in resGW:
    pyplot.plot([i[0]], [i[1]], 'ro') 

for i in resN:
    pyplot.plot([i[0]], [i[1]], 'ro') 

for center in resGW:
    size = 2*r
    # Show the trimmed rhombuses
    for t in xrange(3):
        (v1,v2) = (vectors[t], vectors[(t+1)%3])
        corners = [(0,1),(0,size-1),(size-1,size-1),(size-1,1),(0,1)]
        corners = [(x*v1[0]+y*v2[0],x*v1[1]+y*v2[1]) for (x,y) in corners]
        corners = [addT(x,center) for x in corners]
        pyplot.plot([x for (x,y) in corners],[y for (x,y) in corners],'b')

pyplot.show()
