import numpy as np
import matplotlib.pyplot as plt
import sys

a, b = -100, 100
n = 10
if len(sys.argv) > 1:
	n = int(sys.argv[1])

points = np.random.randint(a, b, size = (n, 2))

# import math
# import random
# points = []
# r = 500
# for x in range(n):
# 	theta = 2*math.pi*random.random()
# 	points.append([r + r * math.cos(theta), r + r * math.sin(theta)])

with open('in.txt', 'w') as f:
	f.write("%d\n" % n)
	for coords in points:
		f.write("%d %d\n" % (coords[0], coords[1]))


plt.scatter(*zip(*points), marker='o', color='black')
plt.savefig('hull_in.png', bbox_inches='tight')