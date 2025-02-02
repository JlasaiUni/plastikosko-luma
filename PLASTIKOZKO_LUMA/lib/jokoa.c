#define _CRT_SECURE_NO_WARNINGS
#include "ebentoak.h"
#include "etsailaren_funtzioak.h"
#include "graphics.h"
#include "gurefuntzioak.h"
#include "imagen.h"
#include "jokalariaren_funtzioak.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

EGOERA jokatu(void)
{
    EGOERA egoera = JOLASTEN;

    jokoaAurkeztu();
    egoera = LehenengoMisioa();

    return egoera;
}

int IrabaziedoGaldu(EGOERA egoera)
{
    int ebentu, BUKAERA = 0;

    if (egoera == GALDU)
    {
        while (!BUKAERA)
        {
            ebentu = ebentuaJasoGertatuBada();

            if (ebentu == TECLA_RETURN)
            {
                BUKAERA = 1;
            }

            BUKAERA_GALDU();
        }
    }

    if (egoera == IRABAZI)

    {
        while (!BUKAERA)
        {
            ebentu = ebentuaJasoGertatuBada();

            if (ebentu == TECLA_RETURN)
            {
                BUKAERA = 1;
            }

            BUKAERA_IRABAZI();
        }
    }
}

/* #include "jokoa.h"
#include "ebentoak.h"
#include "etsailaren_funtzioak.h"
#include "graphics.h"
#include "gurefuntzioak.h"
#include "imagen.h"
#include "jokalariaren_funtzioak.h"
#include "soinua.h"
#include "text.h"
#include <math.h>
#include <stdio.h>

#define ONGI_ETORRI_MEZUA "Sakatu return hasteko..."
#define JOKOA_SOUND "./sound/132TRANCE_02.wav"
#define JOKOA_PLAYER_IMAGE "./img/invader.bmp"
#define JOKOA_SOUND_WIN "./sound/BugleCall.wav"
#define JOKOA_SOUND_LOOSE "./sound/terminator.wav"
#define BUKAERA_SOUND_1 "./sound/128NIGHT_01.wav"
#define BUKAERA_IMAGE "./img/gameOver.bmp"
#define BACKGROUND_IMAGE "./img/background.bmp"
#define ZIRKULUAREN_TAMAINA 40

EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa);
int BUKAERA_irudiaBistaratu();

void jokoaAurkeztu(void)
{
    int ebentu = 0;

    pantailaGarbitu();
    textuaIdatzi((SCREEN_WIDTH / 2) - 100, (SCREEN_HEIGHT / 2) - 20, ONGI_ETORRI_MEZUA);
    pantailaBerriztu();
    do
    {
        ebentu = ebentuaJasoGertatuBada();
    } while (ebentu != TECLA_RETURN);
}

EGOERA jokatu(void)
{
    int mugitu = 0, kont = 0;
    EGOERA egoera = JOLASTEN;
    int ebentu = 0;
    JOKO_ELEMENTUA jokalaria;
    int backgroundId;

    POSIZIOA pos;

    int randomX = 200, randomY = 200, randomX2 = 400, randomY2 = 400, randomX3 = 234, randomY3 = 200, randomX4 = 50,
        randomY4 = 150;

    loadTheMusic(JOKOA_SOUND);
    toggleMusic();
    backgroundId = irudiaKargatu(BACKGROUND_IMAGE);
    jokalaria.id = irudiaKargatu(JOKOA_PLAYER_IMAGE);
    arkatzKoloreaEzarri(0, 0, 0xFF);
    do
    {
        SDL_Delay(10);
        pantailaGarbitu();
        irudiaMugitu(jokalaria.id, jokalaria.pos.x, jokalaria.pos.y);
        irudiakMarraztu();
        pantailaBerriztu();
        zirkuluaMarraztu(randomX, randomY, 10);
        arkatzKoloreaEzarri(0xAF, 0xAF, 0xAA);
        zirkuluaMarraztu(randomX2, randomY2, 10);
        arkatzKoloreaEzarri(0xBE, 0xBE, 0xAB);
        zirkuluaMarraztu(randomX3, randomY3, 10);
        arkatzKoloreaEzarri(0xFF, 0xFF, 0xFF);
        zirkuluaMarraztu(randomX4, randomY4, 10);
        arkatzKoloreaEzarri(0xDE, 0xAA, 0xAA);

    } while (egoera == JOLASTEN);
    irudiaKendu(jokalaria.id);
    irudiaKendu(backgroundId);
    toggleMusic();
    return egoera;
}

EGOERA JOKOA_egoera(JOKO_ELEMENTUA jokalaria, JOKO_ELEMENTUA oztopoa)
{
    EGOERA ret = JOLASTEN;
    if (jokalaria.pos.x > oztopoa.pos.x - ZIRKULUAREN_TAMAINA &&
        jokalaria.pos.x < oztopoa.pos.x + ZIRKULUAREN_TAMAINA &&
        jokalaria.pos.y > oztopoa.pos.y - ZIRKULUAREN_TAMAINA && jokalaria.pos.y < oztopoa.pos.y + ZIRKULUAREN_TAMAINA)
    {
        ret = GALDU;
    }
    else if (jokalaria.pos.x > SCREEN_WIDTH)
    {
        ret = IRABAZI;
    }
    return ret;
}

int jokoAmaierakoa(EGOERA egoera)
{
    int ebentu = 0, id;
    int idAudioGame;

    loadTheMusic(BUKAERA_SOUND_1);
    toggleMusic();
    if (egoera == IRABAZI)
    {
        idAudioGame = loadSound(JOKOA_SOUND_WIN);
        playSound(idAudioGame);
    }
    else
    {
        idAudioGame = loadSound(JOKOA_SOUND_LOOSE);
        playSound(idAudioGame);
    }
    id = BUKAERA_irudiaBistaratu();
    do
    {
        ebentu = ebentuaJasoGertatuBada();
    } while ((ebentu != TECLA_RETURN) && (ebentu != SAGU_BOTOIA_ESKUMA));
    toggleMusic();
    irudiaKendu(id);
    return (ebentu != TECLA_RETURN) ? 1 : 0;
}

int BUKAERA_irudiaBistaratu()
{
    int id = -1;
    id = irudiaKargatu(BUKAERA_IMAGE);
    pantailaGarbitu();
    irudiaMugitu(id, (SCREEN_WIDTH / 2) - 125, (SCREEN_HEIGHT / 2) - 20);
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}
*/