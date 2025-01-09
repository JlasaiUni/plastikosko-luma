#include "jokoa.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
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
    int mugitu = 0, kont = 0; // boolean
    EGOERA egoera = JOLASTEN;
    int ebentu = 0;
    JOKO_ELEMENTUA jokalaria;
    int backgroundId;

    POSIZIOA pos;

    int randomX = 200, randomY = 200, randomX2 = 400, randomY2 = 400, randomX3 = 234, randomY3 = 200, randomX4 = 50,
        randomY4 = 150;

    float disparoVelocidad = 2.0, luzeera;
    float disparoPosX, disparoPosY;
    float disparoDx = 0.0, disparoDy = 0.0;
    int disparoBai = 0;

    jokalaria.pos.x = 0;
    jokalaria.pos.y = SCREEN_HEIGHT / 2;

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
        ebentu = ebentuaJasoGertatuBada();
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_A])
        {
            jokalaria.pos.x = jokalaria.pos.x - 2;
        }
        if (keystate[SDL_SCANCODE_D])
        {
            jokalaria.pos.x = jokalaria.pos.x + 2;
        }
        if (keystate[SDL_SCANCODE_W])
        {
            jokalaria.pos.y = jokalaria.pos.y - 2;
        }
        if (keystate[SDL_SCANCODE_S])
        {
            jokalaria.pos.y = jokalaria.pos.y + 2;
        }

        if (jokalaria.pos.x < 0)
        {
            jokalaria.pos.x = 0;
        }
        if (jokalaria.pos.x > SCREEN_WIDTH - 32)
        {
            jokalaria.pos.x = SCREEN_WIDTH - 32;
        }
        if (jokalaria.pos.y < 0)
        {
            jokalaria.pos.y = 0;
        }
        if (jokalaria.pos.y > SCREEN_HEIGHT - 32)
        {
            jokalaria.pos.y = SCREEN_HEIGHT - 32;
        }

        if (ebentu == SAGU_BOTOIA_EZKERRA)
        {
            pos = saguarenPosizioa();

            disparoPosX = jokalaria.pos.x; // jokalariaren posisioan hasi
            disparoPosY = jokalaria.pos.y;

            // clik egiten duzun diztantzirarte dagoen distantzia detektatu
            disparoDx = pos.x - disparoPosX;
            disparoDy = pos.y - disparoPosY;

            // Normalizamos la dirección para que el disparo tenga una velocidad constante
            // sqrt funtzioak bi magnituden arteko erro karratua kalkulatzen dau
            // bektoria kalkulatzeko x eta y distantziak ber 2 egindako batura da
            luzeera = sqrt(disparoDx * disparoDx + disparoDy * disparoDy);
            // La división de disparoDx y disparoDy entre luzeera tiene como objetivo
            // normalizar el vector. Al dividir las componentes del vector por su magnitud,
            // obtenemos un vector unitario, es decir, un vector con una longitud de 1,
            // pero que sigue apuntando en la misma dirección.
            disparoDx /= luzeera;
            disparoDy /= luzeera;

            disparoBai = 1;
        }

        if (disparoBai == 1)
        {
            // disparuaren posisioa mugitzeko
            disparoPosX += disparoDx * disparoVelocidad;
            disparoPosY += disparoDy * disparoVelocidad;

            // clik egindako puntutik tirurarte dagoen distantzia 5 baino txikiagoa bada tirua desagertzen da
            luzeera = (disparoPosX - pos.x) * (disparoPosX - pos.x) + (disparoPosY - pos.y) * (disparoPosY - pos.y);

            if (luzeera < 5)
            {
                disparoBai = 0; // tirua klik egin duzun tokura heltzen danian desagertu egiten da
            }

            zirkuluaMarraztu(disparoPosX, disparoPosY, 5); // bakarrik marrazten da disparatzen baduzu bestela ez
        }
        if ((disparoPosX > randomX - 30) && (disparoPosX < randomX + 30) && (disparoPosY > randomY - 30) &&
            (disparoPosY < randomY + 30))
        {

            randomX = rand() % (SCREEN_WIDTH - 32); // posicion ramd
            randomY = rand() % (SCREEN_HEIGHT - 32);
            kont++;
        }
        if ((disparoPosX > randomX2 - 30) && (disparoPosX < randomX2 + 30) && (disparoPosY > randomY2 - 30) &&
            (disparoPosY < randomY2 + 30))
        {

            randomX2 = rand() % (SCREEN_WIDTH - 32); // posicion ramd
            randomY2 = rand() % (SCREEN_HEIGHT - 32);
            kont++;
        }
        if ((disparoPosX > randomX3 - 30) && (disparoPosX < randomX3 + 30) && (disparoPosY > randomY3 - 30) &&
            (disparoPosY < randomY3 + 30))
        {

            randomX3 = rand() % (SCREEN_WIDTH - 32); // posicion ramd
            randomY3 = rand() % (SCREEN_HEIGHT - 32);
            kont++;
        }
        if ((disparoPosX > randomX4 - 30) && (disparoPosX < randomX4 + 30) && (disparoPosY > randomY4 - 30) &&
            (disparoPosY < randomY4 + 30))
        {

            randomX4 = rand() % (SCREEN_WIDTH - 32); // posicion ramd
            randomY4 = rand() % (SCREEN_HEIGHT - 32);
            kont++;
        }

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
