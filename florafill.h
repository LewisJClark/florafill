#ifndef FLORAFILL_H
#define FLORAFILL_H

#include <imp.h>
#include "lewtils.h"

#define COL_BLACK (ImpColor){ 0, 0, 0, 255 }
#define COL_WHITE (ImpColor){ 255, 255, 255, 255 }

#define BASE_WIDTH 640
#define BASE_HEIGHT 360

//*************************************************************************************
// SCREENS

typedef enum {
   SCREEN_NONE,
   #define X(upper, lower) SCREEN_##upper,
   #include "_screen_types.h"
   #undef X
} ScreenType;

#define X(upper, lower) \
   void lower##_enter(void);\
   void lower##_tick(float dt);\
   void lower##_leave(void);
#include "_screen_types.h"
#undef X


//*************************************************************************************
// GAME DATA

typedef struct {
   ScreenType screen;          // What screen are we on?
   void * screen_scratch;      // Scratch memory for per-screen state.
} GameData;

extern GameData *game;
extern ImpAPI imp;

void screen_swap(ScreenType new_screen);

#endif // FLORAFILL_H
