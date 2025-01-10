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

GURE_GAUZAK gureGauzak;
ETSAILAK etsailak;

EGOERA LehenengoMisioa(void)
{
    int ebentu = 0, irten = 0, bai = 0, kont = 0, i;
    EGOERA egoera = JOLASTEN;
    char contadorTexto[50];

    ETSAILAK etsailak[4];

    // Inicializar pelotas con posiciones y colores diferentes
    PelotakIniziau(&etsailak[0], 0, 200);   // Pelota 1
    PelotakIniziau(&etsailak[1], 400, 0);   // Pelota 2
    PelotakIniziau(&etsailak[2], 600, 200); // Pelota 3
    PelotakIniziau(&etsailak[3], 50, 400);  // Pelota 4

    double jokalariaPosx = 300, jokalariaPosy = 200; // jokalariaren esaugarriak
    double abiadura = 0.2;

    double disparoVelocidad = 0.5, luzeera, luzeeraSariaJokaliria;
    double disparoPosX, disparoPosY;         // disparuan posisioa
    double disparoDx = 0.0, disparoDy = 0.0; // disparuan direxioa
    int disparoBai = 0;                      // disparua aktibauta edo ez

    // hasierako imagenak kargatzeko
    gureGauzak.jokalaria = irudiaKargatu("./img/invader.bmp");
    irudiaMugitu(gureGauzak.jokalaria, disparoPosX, disparoPosY);

    while (kont < 25 && !irten)
    {
        ebentu = ebentuaJasoGertatuBada();
        const Uint8 *keystate = SDL_GetKeyboardState(NULL); // teklak detektatzeko

        // imagenak (while baten barruan dazenez bein eta berriz kargatzen die)
        pantailaGarbitu();
        irudiaMugitu(gureGauzak.idIrudi, jokalariaPosx, jokalariaPosy);
        textuaIdatzi(10, 20, "Sakatu irudia");
        textuaIdatzi(10, 60, "Lortu 25 puntu");

        // etsailak marraztu eta mogitu
        for (i = 0; i < 6; i++)
        {
            PelotaMarraztu(&etsailak[i]);
            PelotakMugitu(&etsailak[i], jokalariaPosx, jokalariaPosy, 0.05);
        }
        JokalariMugimendu(&jokalariaPosy, &jokalariaPosx);
        // imagena berriz kargau
        irudiaMugitu(gureGauzak.jokalaria, jokalariaPosx, jokalariaPosy);

        // disparua eta etsailen arteko kolisioak detektatu + etsailen eta jokalarien arteko kolisioa
        for (i = 0; i < 6; i++)
        {
            luzeera = (etsailak[i].x - disparoPosX) * (etsailak[i].x - disparoPosX) +
                      (etsailak[i].y - disparoPosY) * (etsailak[i].y - disparoPosY);

            if (luzeera < 30)
            {
                AldeaAukeratuPelota(&etsailak[i].x, &etsailak[i].y);
                kont++;
            }

            luzeera = (etsailak[i].x - jokalariaPosx) * (etsailak[i].x - jokalariaPosx) +
                      (etsailak[i].y - jokalariaPosy) * (etsailak[i].y - jokalariaPosy);

            if (luzeera < 20)
            {
                irten = 1;
            }
        }

        // disparuan mogimendua
        Disparoa(ebentu, &disparoPosX, &disparoPosY, &disparoDx, &disparoDy, &disparoBai, jokalariaPosx, jokalariaPosy,
                 disparoVelocidad);
        // kontadoria
        sprintf(contadorTexto, "Puntuazioa: %d", kont);
        textuaIdatzi(10, 40, contadorTexto);

        irudiakMarraztu();  // Redibujar las imágenes
        pantailaBerriztu(); // Refrescar la pantalla
    }

    if (!irten)
    {
        egoera = IRABAZI;
    }
    else
    {
        egoera = GALDU;
    }

    pantailaGarbitu();
    pantailaBerriztu();

    return egoera;
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