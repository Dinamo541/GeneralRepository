rows = 7
for i in range(rows):
    for j in range(i):
        print(i, end=' ')
    print('')

rows = 5
b = 0
for i in range(rows, 0, -1):
    b += 1
    for j in range(1, i +1):
        print(b, end=' ')
    print('\r')

print(end=' ')
rows = 5
k= 2 * rows - 2
for i in range(rows, -1, -1):
    for j in range(k, 0, -1):
        print(end=" ")
    k = k + 1
    for j in range(0, i + 1):
        print("*", end=" ")
    print("")