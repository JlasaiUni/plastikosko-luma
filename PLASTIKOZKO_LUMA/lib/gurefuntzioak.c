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

int BUKAERA_IRABAZI(void);
int BUKAERA_GALDU(void);
int hasieratu(void);
void jokoaAurkeztu(void);

int hasieratu(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Directorio actual de trabajo: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
    }

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        return 0;
    }

    audioInit();
    textuaGaitu();
    pantailaGarbitu();

    return 0;
}

void jokoaAurkeztu(void)
{
    int ebentu = 0, kont = 0;

    textuaIdatzi(200, 200, "JOKOAREN HASIERA, sakatu SPACE 5 aldiz");
    pantailaBerriztu(); // irudi bat zartzen dan bakoitzian pantaila berriztu behar da

    do
    {
        ebentu = ebentuaJasoGertatuBada();
        if (ebentu == TECLA_SPACE)
        {
            kont++;
        }

    } while (kont < 5); // bost aldiz espasio presionauta beste pantailara doia

    pantailaGarbitu();
}

int BUKAERA_GALDU()
{
    int id = -1;
    irudiaKargatu("./img/background.bmp");
    id = irudiaKargatu("./img/gameOver.bmp");
    textuaIdatzi(200, 200, "sakatu RETURN jokoa amaitzeko");
    arkatzKoloreaEzarri(0xFF, 0xFF, 0xFF);

    irudiaMugitu(id, (SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 20);
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}

int BUKAERA_IRABAZI()
{
    int id = -1;
    id = irudiaKargatu("./img/IRABAZI.bmp");
    textuaIdatzi(200, 200, "sakatu RETURN jokoa amaitzeko");
    arkatzKoloreaEzarri(0xFF, 0xFF, 0xFF);

    irudiaMugitu(id, 125, 20);
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}