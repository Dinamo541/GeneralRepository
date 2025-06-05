arr = [9,2,3,6,5,8,7,4,1,0]
arr.sort()
first, *midlle, last = arr
print(arr)
print(first, midlle, last)

def contadorVocales(texto):
    vocales = 'aeiouáéíóúAEIOUÁÉÍÓÚ'
    contador = 0
    for letra in texto:
        if letra in vocales:
            contador += 1
    return contador 

testo = 'Hola, ¿cómo estás?'
resultado = contador_vocales(testo)
print(f'El texto "{testo}" tiene {resultado} vocales.')