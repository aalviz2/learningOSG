#! /usr/bin/python3

from random import randint
import sys

if len(sys.argv) != 3:
    print("Must provide number of buildings to generate and ouput file name.")
    sys.exit(1)

numBuilds = int(sys.argv[1])
fileName = sys.argv[2]

fil = open(fileName, 'w')
fil.write("[\n")

for i in range(numBuilds):
    coord = (randint(0,100), randint(0,100), 0)
    sizes = (randint(0,10), randint(0,10), randint(0,10))

    fil.write("\t{\n")
    fil.write("\t\t\"location\": [" + str(coord[0]) + ", "  + str(coord[1]) + ", " + str(coord[2]) + "],\n")
    fil.write("\t\t\"x\": " + str(sizes[0]) + ",\n")
    fil.write("\t\t\"y\": " + str(sizes[1]) + ",\n")
    fil.write("\t\t\"z\": " + str(sizes[2]) + "\n")

    if i == numBuilds-1:
        fil.write("\t}\n")
    else:
        fil.write("\t},\n")

fil.write("]")
fil.close()
