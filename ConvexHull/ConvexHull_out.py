import numpy as np
import matplotlib.pyplot as plt
import math

with open('in.txt', 'r') as f:
	lines = f.read().split("\n")
	points = [line.split(" ") for line in lines[1:] if line]

points = [[float(c[0]), float(c[1])] for c in points]


with open('out.txt', 'r') as f:
	lines = f.read().split("\n")
	n = int(lines[0])
	hull = [line.split(" ") for line in lines[1:] if line]

hull = [[float(c[0]), float(c[1])] for c in hull]

x, y = zip(*hull)
centroid = (sum(x) / n, sum(y) / n)
hull.sort(key = lambda l: math.atan2(l[1] - centroid[1], l[0] - centroid[0]))

hull.append(hull[0])

# print(hull)
# print(points)

plt.figure()
plt.plot(*zip(*hull))
plt.scatter(*zip(*points), marker='o', color='black')
plt.scatter(*zip(*hull), marker='o', color='red')
plt.savefig('hull_out.png', bbox_inches='tight')