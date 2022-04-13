import matplotlib
import matplotlib.pyplot as plt
import numpy as np

#Cnfiguración de la distribución de la imagen
#(Nº de Filas, Nº de Columnas, Posición)
fig = plt.figure()
ax = plt.subplot()

#Datos a representar
data = np.loadtxt('sol-muchos.txt')
x=data[:,0]
y=data[:,1]
error=data[:,2]


plt.ylim(-0.05,1.20)

#Colocar etiquetas a los ejes y título a la gráfica
ax.set_ylabel('Solapamiento', fontname='Times New Roman', fontsize='14')
ax.set_xlabel('Número de Patrones', fontname='Times New Roman', fontsize='14')
#ax.set_title('Función seno')

#Creación de la gráfica, guardado y ejecución
ax.errorbar(x, y, error, linestyle='', capsize = 3, ecolor='g', marker='o', markersize=4, label='Data')


#plt.legend()
plt.savefig('sol-muchos.png')

plt.show()