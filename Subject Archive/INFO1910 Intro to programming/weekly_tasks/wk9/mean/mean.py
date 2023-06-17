def calcmean(x, y, z):
	return(float((x+y+z)/3))

def calcdistance(mean, num):
	return(abs(mean - num))

x = input()
y = input()
z = input()

mean = calcmean(x,y,z)
distance = calcdistance(mean, x)
if distance < calcdistance(mean, y):
	distance = calcdistance(mean, y)
elif distance < calcdistance(mean, z):
	distance = calcdistance(mean, z)

print(distance)

#print(max(calcdistance(mean, x), calcdistance(mean, y), calcdistance(mean, z)))