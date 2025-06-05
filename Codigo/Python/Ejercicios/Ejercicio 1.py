# Ejercicio 1
# Escribir un programa que pida al usuario tres notas y calcule el promedio.
oneScore = float(input('Porfavor ingrese la primera nota:'))
twoScore = float(input('Porfavor ingrese la segunda nota:'))
threeScore = float(input('Porfavor ingrese la tercera nota:'))
if (((oneScore + twoScore + threeScore) / 3) >= 7): 
    print ('Aprobado con un promedio de: ' + str(((oneScore + twoScore + threeScore) / 3)) + ' puntos')
else:
    if (((oneScore + twoScore + threeScore) / 3) >= 6):
        print ('Aplazado con un promedio de: ' + str(((oneScore + twoScore + threeScore) / 3)) + ' puntos')
    else:
        print ('Reprobado con un promedio de: ' + str(((oneScore + twoScore + threeScore) / 3)) + ' puntos')
