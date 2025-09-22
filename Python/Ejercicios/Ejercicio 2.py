# Ejercicio 2
# Escribir un programa que pida al usuario un número y calcule su factorial.
number = int (input('Porfavor ingrese un numero: '))
factorial = 1
for i in range (1, number + 1):
    factorial *= i
print (f'El factorial de {number} es: {factorial}')