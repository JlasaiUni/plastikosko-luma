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

void JokalariMugimendu(double *JokalariaPosy, double *jokalariaPosx)
{
    double abiadura = 0.2;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL); // teklak detektatzeko

    // jokalaria fletzekin mugitu
    if (keystate[SDL_SCANCODE_W])
    {
        *JokalariaPosy -= abiadura;
    }
    if (keystate[SDL_SCANCODE_S])
    {
        *JokalariaPosy += abiadura;
    }
    if (keystate[SDL_SCANCODE_A])
    {
        *jokalariaPosx -= abiadura;
    }
    if (keystate[SDL_SCANCODE_D])
    {
        *jokalariaPosx += abiadura;
    }
    // ez ateratzeko pantailatik
    if (*jokalariaPosx < 0)
    {
        *jokalariaPosx = 0;
    }
    if (*jokalariaPosx > 1280)
    {
        *jokalariaPosx = 1280;
    }
    if (*jokalariaPosx < 0)
    {
        *jokalariaPosx = 0;
    }
    if (*jokalariaPosx > 720)
    {
        *jokalariaPosx = 720;
    }
}

void Disparoa(int ebentu, double *disparoPosX, double *disparoPosY, double *disparoDx, double *disparoDy,
              int *disparoBai, double posx, double posy, double disparoVelocidad)
{
    double luzeera;
    POSIZIOA pos;

    // Disparo al hacer clic
    if (ebentu == SAGU_BOTOIA_EZKERRA)
    {
        pos = saguarenPosizioa();

        *disparoPosX = posx; // Inicializamos la posición del disparo en la del jugador
        *disparoPosY = posy;

        // Calculamos la dirección del disparo
        *disparoDx = pos.x - *disparoPosX;
        *disparoDy = pos.y - *disparoPosY;

        // Normalizamos la dirección para que el disparo tenga velocidad constante
        luzeera = sqrt(*disparoDx * *disparoDx + *disparoDy * *disparoDy);
        *disparoDx /= luzeera;
        *disparoDy /= luzeera;

        *disparoBai = 1; // Activamos el disparo
    }

    // Movimiento del disparo
    if (*disparoBai == 1)
    {
        *disparoPosX += *disparoDx * disparoVelocidad;
        *disparoPosY += *disparoDy * disparoVelocidad;

        // Si el disparo llega cerca del mouse, desaparece
        luzeera = (*disparoPosX - pos.x) * (*disparoPosX - pos.x) + (*disparoPosY - pos.y) * (*disparoPosY - pos.y);
        if (luzeera < 5)
        {
            *disparoBai = 0; // Desactivamos el disparo

            // Reseteamos la posición del disparo para evitar que quede "invisible"
            *disparoPosX = 0;
            *disparoPosY = 0;
        }

        // Dibujamos el disparo
        if (*disparoBai == 1)
        {
            arkatzKoloreaEzarri(0x00, 0x00, 0xFF);           // Color azul
            zirkuluaMarraztu(*disparoPosX, *disparoPosY, 5); // Dibujamos el disparo
        }
    }
}