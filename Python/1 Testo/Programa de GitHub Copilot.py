import pygame
import math
import sys

# Inicializar pygame
pygame.init()

# Configuración de la pantalla
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pelota rebotando en un hexágono rotatorio")

# Colores
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Configuración de la pelota
ball_radius = 15
ball_pos = [WIDTH // 2, HEIGHT // 4]
ball_vel = [2, 0]  # Velocidad inicial
gravity = 0.5
friction = 0.98

# Configuración del hexágono
hexagon_radius = 200
hexagon_center = (WIDTH // 2, HEIGHT // 2)
hexagon_angle = 0
hexagon_rotation_speed = 1  # Grados por frame

# Reloj para controlar FPS
clock = pygame.time.Clock()
FPS = 60

def get_hexagon_points(center, radius, angle):
    """Calcula los puntos del hexágono rotado."""
    points = []
    for i in range(6):
        theta = math.radians(angle + i * 60)
        x = center[0] + radius * math.cos(theta)
        y = center[1] + radius * math.sin(theta)
        points.append((x, y))
    return points

def reflect_ball(ball_pos, ball_vel, p1, p2):
    """Refleja la pelota al chocar con una pared."""
    wall_dx = p2[0] - p1[0]
    wall_dy = p2[1] - p1[1]
    wall_length = math.sqrt(wall_dx**2 + wall_dy**2)
    wall_normal = (-wall_dy / wall_length, wall_dx / wall_length)

    # Producto punto para reflejar la velocidad
    dot_product = ball_vel[0] * wall_normal[0] + ball_vel[1] * wall_normal[1]
    ball_vel[0] -= 2 * dot_product * wall_normal[0]
    ball_vel[1] -= 2 * dot_product * wall_normal[1]

    # Ajustar posición para evitar que la pelota quede atrapada
    overlap = ball_radius - math.sqrt((ball_pos[0] - p1[0])**2 + (ball_pos[1] - p1[1])**2)
    ball_pos[0] += overlap * wall_normal[0]
    ball_pos[1] += overlap * wall_normal[1]

# Bucle principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Aplicar gravedad
    ball_vel[1] += gravity

    # Actualizar posición de la pelota
    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]

    # Aplicar fricción
    ball_vel[0] *= friction
    ball_vel[1] *= friction

    # Rotar el hexágono
    hexagon_angle += hexagon_rotation_speed
    hexagon_points = get_hexagon_points(hexagon_center, hexagon_radius, hexagon_angle)

    # Detectar colisiones con las paredes del hexágono
    for i in range(6):
        p1 = hexagon_points[i]
        p2 = hexagon_points[(i + 1) % 6]

        # Vector de la pared
        wall_dx = p2[0] - p1[0]
        wall_dy = p2[1] - p1[1]
        wall_length = math.sqrt(wall_dx**2 + wall_dy**2)

        # Proyección de la pelota sobre la pared
        t = ((ball_pos[0] - p1[0]) * wall_dx + (ball_pos[1] - p1[1]) * wall_dy) / wall_length**2
        t = max(0, min(1, t))
        closest_point = (p1[0] + t * wall_dx, p1[1] + t * wall_dy)

        # Distancia entre la pelota y la pared
        dist = math.sqrt((ball_pos[0] - closest_point[0])**2 + (ball_pos[1] - closest_point[1])**2)

        if dist <= ball_radius:
            reflect_ball(ball_pos, ball_vel, p1, p2)

    # Dibujar todo
    screen.fill(BLACK)
    pygame.draw.polygon(screen, WHITE, hexagon_points, 2)
    pygame.draw.circle(screen, RED, (int(ball_pos[0]), int(ball_pos[1])), ball_radius)

    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
sys.exit()