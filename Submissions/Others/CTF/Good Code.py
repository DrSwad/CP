import matplotlib.pyplot as plt

xpoints = []
ypoints = []

f = open("Code Jam Coordinates.txt", "r")
for line in f:
  [x, y] = line.split()
  xpoints.append(x)
  ypoints.append(y)
f.close()

plt.plot(xpoints, ypoints, 'o')
plt.show()