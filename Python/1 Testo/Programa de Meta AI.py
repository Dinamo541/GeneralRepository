import pygame
import math

#Constantes
ANCHO, ALTO = 800, 600
GRAVEDAD = 0.1
FRICCION = 0.995
VELOCIDAD_INICIAL = 5

class Pelota:
    def __init__(self):
        self.x = ANCHO // 2
        self.y = ALTO // 2
        self.vx = VELOCIDAD_INICIAL
        self.vy = -VELOCIDAD_INICIAL
        self.radio = 10

    def actualizar(self):
        self.vy += GRAVEDAD
        self.vx *= FRICCION
        self.vy *= FRICCION
        self.x += self.vx
        self.y += self.vy

    def dibujar(self, pantalla):
        pygame.draw.circle(pantalla, (255, 255, 255), (int(self.x), int(self.y)), self.radio)

class Hexagono:
    def __init__(self, x, y, lado):
        self.x = x
        self.y = y
        self.lado = lado
        self.angulo = 0
        self.vertices = []
        for i in range(6):
            angulo = math.radians(60 * i)
            self.vertices.append((x + lado * math.cos(angulo), y + lado * math.sin(angulo)))

    def rotar(self):
        self.angulo += 1
        if self.angulo >= 360:
            self.angulo = 0
        self.vertices = []
        for i in range(6):
            angulo = math.radians(60 * i + self.angulo)
            self.vertices.append((self.x + self.lado * math.cos(angulo), self.y + self.lado * math.sin(angulo)))

    def dibujar(self, pantalla):
        pygame.draw.polygon(pantalla, (255, 0, 0), self.vertices, 2)

def colision(pelota, hexagono):
    for i in range(len(hexagono.vertices)):
        x1, y1 = hexagono.vertices[i]
        x2, y2 = hexagono.vertices[(i + 1) % len(hexagono.vertices)]
        dx = x2 - x1
        dy = y2 - y1
        longitud = math.hypot(dx, dy)
        ux = dx / longitud
        uy = dy / longitud
        vx = pelota.x - x1
        vy = pelota.y - y1
        t = (vx * ux + vy * uy) / longitud
        if 0 <= t <= 1:
            distancia = abs((x2 - x1) * (y1 - pelota.y) - (x1 - pelota.x) * (y2 - y1)) / math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
            if distancia <= pelota.radio:
                normal_x = -(y2 - y1)
                normal_y = x2 - x1
                longitud_normal = math.hypot(normal_x, normal_y)
                normal_x /= longitud_normal
                normal_y /= longitud_normal
                dot_product = pelota.vx * normal_x + pelota.vy * normal_y
                pelota.vx -= 2 * dot_product * normal_x
                pelota.vy -= 2 * dot_product * normal_y

def main():
    pygame.init()
    pantalla = pygame.display.set_mode((ANCHO, ALTO))
    reloj = pygame.time.Clock()
    pelota = Pelota()
    hexagono = Hexagono(ANCHO // 2, ALTO // 2, 200)

    ejecutando = True
    while ejecutando:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                ejecutando = False

        pelota.actualizar()
        hexagono.rotar()
        colision(pelota, hexagono)

        pantalla.fill((0, 0, 0))
        pelota.dibujar(pantalla)
        hexagono.dibujar(pantalla)

        if pelota.x - pelota.radio < 0 or pelota.x + pelota.radio > ANCHO:
            pelota.vx *= -1
        if pelota.y - pelota.radio < 0 or pelota.y + pelota.radio > ALTO:
            pelota.vy *= -1

        pygame.display.flip()
        reloj.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()