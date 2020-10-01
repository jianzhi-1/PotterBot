import pygame
import os
import generator

pygame.init()
display_width = 800
display_height = 600

gameDisplay = pygame.display.set_mode((display_width,display_height))
pygame.display.set_caption('TrumpBot')
black = (0,0,0)
white = (255,255,255)
green = (0, 255, 0)
blue = (0, 0, 128)

trumpimg = pygame.image.load('trump2.png')

#font = pygame.font.Font('freesansbold.ttf', 10)
font = pygame.font.SysFont('Arial', 22)
text = generator.get_message(5, 300, "Thank")
#text = font.render(generator.get_message(5, 300, "Thank"), True, green, blue)
#textRect = text.get_rect()
#textRect.center = (400//2, 400//2)


clock = pygame.time.Clock()
crashed = False

def blit_text(surface, text, pos, font, color=pygame.Color('black')):
    words = [word.split(' ') for word in text.splitlines()]  # 2D array where each row is a list of words.
    space = font.size(' ')[0]  # The width of a space.
    max_width, max_height = surface.get_size()
    x, y = pos
    for line in words:
        for word in line:
            word_surface = font.render(word, 0, color)
            word_width, word_height = word_surface.get_size()
            if x + word_width >= max_width:
                x = pos[0]  # Reset the x.
                y += word_height  # Start on new row.
            surface.blit(word_surface, (x, y))
            x += word_width + space
        x = pos[0]  # Reset the x.
        y += word_height  # Start on new row.


def car(x,y):
    gameDisplay.blit(trumpimg, (x,y))

x =  (display_width * 0)
y = (display_height * 0)

while not crashed:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            crashed = True

        print(event)
    gameDisplay.fill(white)
    #gameDisplay.blit(text, textRect)
    blit_text(gameDisplay, text, (400, 200), font)
    car(x,y)


    pygame.display.update()
    clock.tick(60)

pygame.quit()
quit()
