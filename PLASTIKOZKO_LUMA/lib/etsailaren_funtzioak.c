#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "jokoa.h"
#include "soinua.h"
#include "text.h"
#include <math.h>
#include <stdio.h>

#define JOKOA_SOUND "./sound/132TRANCE_02.wav"
#define JOKOA_PLAYER_IMAGE "./img/invader.bmp"
#define JOKOA_SOUND_WIN "./sound/BugleCall.wav"
#define JOKOA_SOUND_LOOSE "./sound/terminator.wav"
#define BUKAERA_SOUND_1 "./sound/128NIGHT_01.wav"

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
    enemy.texture = loadTexture("enemy.bmp", renderer);

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
