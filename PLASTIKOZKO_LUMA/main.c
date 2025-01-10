/*#include "orokorrak.h"
#include "bukaera.h"
#include "errealitateFisikoa.h"
#include "jokoa.h"
#include "sarrera.h"*/

//---------------------------------------------------------------------------------
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "soinua.h"
#include "text.h"
//---------------------------------------------------------------------------------

#include <stdio.h>

#include "lib/jokoa.h"
#include "ourTypes.h"

int main(int argc, char *str[])
{
    EGOERA egoera;

    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
        return 1;
    }
    textuaGaitu();
    audioInit();

    egoera = jokatu();
    IrabaziedoGaldu(egoera);

    audioTerminate();
    sgItxi();
    return 0;
}