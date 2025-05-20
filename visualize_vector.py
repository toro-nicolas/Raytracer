import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x1 = float(input("Entrez la coordonnée x du point A: "))
y1 = float(input("Entrez la coordonnée y du point A: "))
z1 = float(input("Entrez la coordonnée z du point A: "))
x2 = float(input("Entrez la coordonnée x du point B: "))
y2 = float(input("Entrez la coordonnée y du point B: "))
z2 = float(input("Entrez la coordonnée z du point B: "))

# Points A et B
A = np.array([x1, z1, y1])
B = np.array([x2, z2, y2])

# Vecteur direction
V = B - A

# Création de la figure 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Affichage des points
ax.scatter(*A, color='blue', label='Point A')
ax.scatter(*B, color='red', label='Point B')

# Affichage du vecteur (flèche)
ax.quiver(*A, *V, color='green', arrow_length_ratio=0.1, label='Vecteur AB')

# Légende et affichage
ax.legend()
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()
