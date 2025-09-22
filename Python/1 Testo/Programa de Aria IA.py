import pygame
import math
import random

# Inicialización de Pygame
pygame.init()

# Configuración de la pantalla
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Pelota Rebotando en Hexágono Rotatorio")

# Colores
black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)

# Parámetros de la pelota
ball_radius = 15
ball_x = width // 2
ball_y = height // 2
ball_speed_x = 0
ball_speed_y = 0
gravity = 0.2
friction = 0.98

# Parámetros del hexágono
hex_radius = 150
hex_center_x = width // 2
hex_center_y = height // 2
hex_rotation_speed = 0.02
hex_angle = 0

# Función para dibujar el hexágono
def draw_hexagon(surface, color, radius, center_x, center_y, angle):
    points = []
    for i in range(6):
        x = center_x + radius * math.cos(angle + i * math.pi / 3)
        y = center_y + radius * math.sin(angle + i * math.pi / 3)
        points.append((x, y))
    pygame.draw.polygon(surface, color, points, 2) # Grosor de la línea = 2

# Función para detectar colisiones con las paredes del hexágono
def check_collision(ball_x, ball_y, hex_center_x, hex_center_y, hex_radius, hex_angle):
    global ball_speed_x, ball_speed_y  # Aseguramos que las velocidades sean modificables
    for i in range(6):
        angle1 = hex_angle + i * math.pi / 3
        angle2 = hex_angle + (i + 1) * math.pi / 3
        x1 = hex_center_x + hex_radius * math.cos(angle1)
        y1 = hex_center_y + hex_radius * math.sin(angle1)
        x2 = hex_center_x + hex_radius * math.cos(angle2)
        y2 = hex_center_y + hex_radius * math.sin(angle2)

        # Calcula la distancia del punto a la línea
        dx = x2 - x1
        dy = y2 - y1
        if dx == 0 and dy == 0:
            continue
        det = dx * dx + dy * dy
        if det == 0:
            continue
        a = ((ball_x - x1) * dx + (ball_y - y1) * dy) / det
        if a < 0:
            closest_x = x1
            closest_y = y1
        elif a > 1:
            closest_x = x2
            closest_y = y2
        else:
            closest_x = x1 + a * dx
            closest_y = y1 + a * dy

        distance = math.sqrt((ball_x - closest_x) ** 2 + (ball_y - closest_y) ** 2)

        if distance <= ball_radius:
            # Calcula el vector normal a la pared
            nx = -(y2 - y1)
            ny = x2 - x1
            norm = math.sqrt(nx * nx + ny * ny)
            if norm != 0:
                nx /= norm
                ny /= norm

                # Calcula la velocidad de la pelota en la dirección normal
                dot_product = ball_speed_x * nx + ball_speed_y * ny
                ball_speed_x -= 2 * dot_product * nx
                ball_speed_y -= 2 * dot_product * ny

                # Reposiciona la pelota fuera de la pared
                overlap = ball_radius - distance
                ball_x += nx * overlap
                ball_y += ny * overlap

                return True
    return False

# Bucle principal del juego
running = True
clock = pygame.time.Clock()
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Actualización de la física de la pelota
    ball_speed_y += gravity
    ball_speed_x *= friction
    ball_speed_y *= friction
    ball_x += ball_speed_x
    ball_y += ball_speed_y

    # Rotación del hexágono
    hex_angle += hex_rotation_speed

    # Detección de colisiones y rebotes
    if check_collision(ball_x, ball_y, hex_center_x, hex_center_y, hex_radius, hex_angle):
        pass # La velocidad de la pelota se modifica dentro de check_collision

    # Rebote en los bordes de la pantalla (opcional)
    if ball_x - ball_radius < 0 or ball_x + ball_radius > width:
        ball_speed_x *= -1
    if ball_y - ball_radius < 0 or ball_y + ball_radius > height:
        ball_speed_y *= -1

    # Dibujo
    screen.fill(black)
    draw_hexagon(screen, white, hex_radius, hex_center_x, hex_center_y, hex_angle)
    pygame.draw.circle(screen, red, (int(ball_x), int(ball_y)), ball_radius)

    pygame.display.flip()
    clock.tick(60)  # Limitamos el framerate a 60 FPS

pygame.quit()