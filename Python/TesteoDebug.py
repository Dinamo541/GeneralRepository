
def sumar(costo, impuesto):
    return costo + impuesto

def leer_datos() -> list[int]:
    with open("datos.txt", "r") as f:
        lineas = f.readlines()
    lista_sin_encabezado = lineas[1:]
    datos = []
    for num in lista_sin_encabezado:
        datos.append(num)
    return datos


costo = 100
impuesto = 16

print(sumar(costo, impuesto))

