#define _CRT_SECURE_NO_WARNINGS
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "jokoa.h"
#include "soinua.h"
#include "text.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void AldeaAukeratuPelota(double *x, double *y);
void PelotaMarraztu(ETSAILAK *pelota);
void PelotakMugitu(ETSAILAK *etsaila, double EtsailaPosX, double EtsailaPosY, double abiadura);
void PelotakIniziau(ETSAILAK *etsaila, double x, double y);
void EtsailarenTiro(void);

void AldeaAukeratuPelota(double *x, double *y)
{
    int aldea = rand() % 4; // 0tik 3ra

    switch (aldea)
    {
    case 0:
        *x = 0;
        *y = rand() % (SCREEN_HEIGHT - 32);
        break;
    case 1:
        *x = rand() % (SCREEN_WIDTH - 32);
        *y = 0;
        break;
    case 2:
        *x = rand() % (SCREEN_WIDTH - 32);
        *y = SCREEN_HEIGHT - 32;
        break;
    case 3:
        *x = SCREEN_WIDTH - 32;
        *y = rand() % (SCREEN_HEIGHT - 32);
        break;
    }
}

void PelotakIniziau(ETSAILAK *etsaila, double x, double y)
{
    etsaila->x = x;
    etsaila->y = y;
    etsaila->dx = 0.0;
    etsaila->dy = 0.0;
}

void PelotakMugitu(ETSAILAK *etsaila, double EtsailaPosX, double EtsailaPosY, double abiadura)
{
    double dx, dy, Luzeera;

    dx = EtsailaPosX - etsaila->x;
    dy = EtsailaPosY - etsaila->y;

    Luzeera = sqrt(dx * dx + dy * dy);

    dx /= Luzeera;
    dy /= Luzeera;

    etsaila->x += dx * abiadura;
    etsaila->y += dy * abiadura;
}

void PelotaMarraztu(ETSAILAK *pelota)
{
    arkatzKoloreaEzarri(0xFF, 0x00, 0x00);
    zirkuluaMarraztu(pelota->x, pelota->y, 10);
}

/*
typedef struct
{
    int x, y;
    int width, height;
    int dx, dy;
    SDL_Texture *texture;
} Enemy;

// Función para cargar una textura desde un archivo
SDL_Texture *loadTexture(const char *file, SDL_Renderer *renderer)
{
    SDL_Surface *loadedImage = SDL_LoadBMP(file);
    if (loadedImage == NULL)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
    return texture;
}

// Función para generar un enemigo
Enemy createEnemy(int x, int y, int width, int height, int dx, int dy, SDL_Renderer *renderer)
{
    Enemy enemy;
    enemy.x = x;
    enemy.y = y;
    enemy.width = width;
    enemy.height = height;
    enemy.dx = dx;
    enemy.dy = dy;
    enemy.texture = loadTexture("./img/invader.bmp", renderer);

    if (enemy.texture == NULL)
    {
        printf("Failed to load enemy texture.\n");
    }

    return enemy;
}

// Función para actualizar la posición del enemigo
void updateEnemy(Enemy *enemy)
{
    enemy->x += enemy->dx;
    enemy->y += enemy->dy;

    // Aquí puedes agregar lógica para rebotar, cambiar dirección, etc.
    // Ejemplo: Si el enemigo sale de la pantalla, invierte la dirección
    if (enemy->x < 0 || enemy->x > 800 - enemy->width)
    {
        enemy->dx = -enemy->dx;
    }
    if (enemy->y < 0 || enemy->y > 600 - enemy->height)
    {
        enemy->dy = -enemy->dy;
    }
}
*/