import pygame
import math
import sys

# Inicialización
pygame.init()
WIDTH, HEIGHT = 800, 800
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# Parámetros físicos
GRAVITY = 0.5
FRICTION = 0.99
BOUNCE = 0.9

# Pelota
ball_pos = [WIDTH // 2, HEIGHT // 2 - 100]
ball_vel = [3, 0]
ball_radius = 10

# Hexágono
hex_radius = 300
hex_center = (WIDTH // 2, HEIGHT // 2)
hex_rotation = 0
rotation_speed = 0.01

def get_hex_points(center, radius, angle_offset):
    points = []
    for i in range(6):
        angle = math.radians(i * 60) + angle_offset
        x = center[0] + math.cos(angle) * radius
        y = center[1] + math.sin(angle) * radius
        points.append((x, y))
    return points

def reflect(vel, normal):
    dot = vel[0] * normal[0] + vel[1] * normal[1]
    return [
        vel[0] - 2 * dot * normal[0],
        vel[1] - 2 * dot * normal[1]
    ]

def point_line_distance(p, a, b):
    # Proyección del punto p sobre la línea ab
    ap = (p[0] - a[0], p[1] - a[1])
    ab = (b[0] - a[0], b[1] - a[1])
    ab_len = ab[0]**2 + ab[1]**2  # Corregido: calcular la longitud al cuadrado del vector ab
    t = max(0, min(1, (ap[0]*ab[0] + ap[1]*ab[1]) / ab_len))  # Proyección escalar
    closest = (a[0] + ab[0]*t, a[1] + ab[1]*t)  # Punto más cercano en la línea
    dist = math.hypot(p[0] - closest[0], p[1] - closest[1])  # Distancia al punto más cercano
    return dist, closest

# Loop principal
running = True
while running:
    dt = clock.tick(60) / 1000
    screen.fill((30, 30, 30))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Actualizar rotación del hexágono
    hex_rotation += rotation_speed
    hex_points = get_hex_points(hex_center, hex_radius, hex_rotation)

    # Física de la pelota
    ball_vel[1] += GRAVITY
    ball_vel[0] *= FRICTION
    ball_vel[1] *= FRICTION
    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]

    # Colisión con las paredes del hexágono
    for i in range(6):
        a = hex_points[i]
        b = hex_points[(i + 1) % 6]
        dist, closest = point_line_distance(ball_pos, a, b)
        if dist < ball_radius:
            # Calcular normal
            edge = (b[0] - a[0], b[1] - a[1])
            normal = (-edge[1], edge[0])
            norm_len = math.hypot(*normal)
            normal = (normal[0]/norm_len, normal[1]/norm_len)

            # Rebote
            ball_vel = reflect(ball_vel, normal)
            ball_vel[0] *= BOUNCE
            ball_vel[1] *= BOUNCE

            # Reposicionar la pelota fuera de la pared
            overlap = ball_radius - dist
            ball_pos[0] += normal[0] * overlap
            ball_pos[1] += normal[1] * overlap

    # Dibujar hexágono
    pygame.draw.polygon(screen, (200, 200, 200), hex_points, 3)

    # Dibujar pelota
    pygame.draw.circle(screen, (255, 100, 100), (int(ball_pos[0]), int(ball_pos[1])), ball_radius)

    pygame.display.flip()

pygame.quit()
sys.exit()