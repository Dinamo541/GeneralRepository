import pygame
import math

# Configuración inicial
WIDTH, HEIGHT = 800, 600
FPS = 60
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BALL_COLOR = (200, 0, 0)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pelota rebotando en un hexágono rotatorio")
clock = pygame.time.Clock()

# Parámetros de la pelota
ball_radius = 15
ball_pos = [WIDTH // 2, HEIGHT // 4]
ball_vel = [2, 1]
gravity = 0.5
friction = 0.99

# Parámetros del hexágono
hex_radius = 200
hex_center = [WIDTH // 2, HEIGHT // 2]
hex_angle = 0
rotation_speed = 0.02

def draw_hexagon(surface, center, radius, angle):
    points = []
    for i in range(6):
        theta = math.radians(i * 60) + angle
        x = center[0] + radius * math.cos(theta)
        y = center[1] + radius * math.sin(theta)
        points.append((x, y))
    pygame.draw.polygon(surface, WHITE, points, 2)
    return points

def reflect_ball(ball_pos, ball_vel, hex_points):
    for i in range(len(hex_points)):
        p1 = hex_points[i]
        p2 = hex_points[(i + 1) % len(hex_points)]
        dx, dy = p2[0] - p1[0], p2[1] - p1[1]
        length = math.sqrt(dx**2 + dy**2)  # Corregido - 4Pts
        normal = (-dy / length, dx / length)

        # Distancia desde la pelota al lado del hexágono
        point_to_line = (
            (ball_pos[0] - p1[0]) * normal[0] +
            (ball_pos[1] - p1[1]) * normal[1]
        )
        if abs(point_to_line) < ball_radius:
            # Refleja la velocidad de la pelota
            vel_dot_n = ball_vel[0] * normal[0] + ball_vel[1] * normal[1]
            ball_vel[0] -= 2 * vel_dot_n * normal[0]
            ball_vel[1] -= 2 * vel_dot_n * normal[1]
            return

# Bucle principal
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Física de la pelota
    ball_vel[1] += gravity
    ball_vel[0] *= friction
    ball_vel[1] *= friction
    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]

    # Dibuja el hexágono y refleja la pelota si colisiona
    screen.fill(BLACK)
    hex_points = draw_hexagon(screen, hex_center, hex_radius, hex_angle)
    reflect_ball(ball_pos, ball_vel, hex_points)
    hex_angle += rotation_speed

    # Dibuja la pelota
    pygame.draw.circle(screen, BALL_COLOR, (int(ball_pos[0]), int(ball_pos[1])), ball_radius)

    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()