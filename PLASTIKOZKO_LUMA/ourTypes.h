#ifndef OURTYPES_H
#define OURTYPES_H

#include "ebentoak.h"

typedef enum
{
    JOLASTEN,
    GALDU,
    IRABAZI
} EGOERA;
typedef enum
{
    IRUDIA,
    MARGOA,
    TESTUA
} MOTA;

typedef struct
{
    POSIZIOA pos;
    int id;
    MOTA mota;
} JOKO_ELEMENTUA;

typedef struct S_GURE_GAUZAK
{
    int idIrudi;
    int text;
    int jokalaria;

} GURE_GAUZAK;

typedef struct S_ETSAILAK
{
    double x, y;
    double dx, dy;

} ETSAILAK;

typedef struct S_SARIAK
{
    double x, y;

} SARIAK;

#endif