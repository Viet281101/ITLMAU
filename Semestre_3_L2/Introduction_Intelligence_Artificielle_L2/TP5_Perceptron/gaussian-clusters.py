import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


centre1=np.array([3,3])
centre2=np.array([-3,-3])
sigma1=np.array([[1.5,0],[0,1.5]])
sigma2=np.array([[1.5,0],[0,1.5]])
taille1=200
taille2=200
cluster1=np.random.multivariate_normal(centre1,sigma1,taille1)
cluster2=np.random.multivariate_normal(centre2,sigma2,taille2)


class Perceptron:
	def __init__(self):
		self.w0 = -1.0
		self.wgts = np.array([2.0, 1.0])
		self.stepsize = 3e-2

	def decide(self, x : np.array, y: int) -> float:
		# decision function:
		res = -1
		if (self.w0 + self.wgts @ x)*y > 0:
			res = 1

		return(res)

	def calculate_x2(self, x1):
		return((-self.w0 - self.wgts[0]*x1)/self.wgts[1])

	def calculate_x1(self, x2):
		return((-self.w0 - self.wgts[1]*x2)/self.wgts[0])	


p = Perceptron()
print(p.wgts)

data = [(cluster1, -1) , 
			(cluster2, 1)]


# for point in cluster1:
# 	print(p.decide(point, -1))

# -1
plt.scatter([point[0] for point in cluster1], [point[1] for point in cluster1], color="pink")
# 1
plt.scatter([point[0] for point in cluster2], [point[1] for point in cluster2], color="blue")
plt.scatter(centre1[0], centre1[1], color="red")
plt.scatter(centre2[0], centre2[1], color="red")


# before
plt.plot(np.array([6.0, -6.0]), 
			np.array([p.calculate_x2(6.0), p.calculate_x2(-6.0)]))

not_convert = True

while not_convert:
	check = True
	for clust, y in data:
		for point in clust:
			if p.decide(point, y) < 0:
				p.w0  += p.stepsize * y
				p.wgts[0] += p.stepsize*y*point[0] 
				p.wgts[1] += p.stepsize*y*point[1]
				check = False
	if check: not_convert = False


# after
plt.plot(np.array([6.0, -6.0]), 
			np.array([p.calculate_x2(6.0), p.calculate_x2(-6.0)]))



plt.show()







