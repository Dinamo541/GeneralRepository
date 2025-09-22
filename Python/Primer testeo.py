def contadorVocales(texto):
    vocales = 'aeiouáéíóúAEIOUÁÉÍÓÚ'
    contador = 0
    for letra in texto:
        if letra in vocales:
            contador += 1
    return contador 

print("Hola Mundo")
print("Hola Mundo")
print("Hola Mundo")