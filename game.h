#ifndef FLORAFILL_H
#define FLORAFILL_H

#include <stdint.h>
#include <stdbool.h>
#include <imp.h>
#include "lewtils.h"

#define COL_BLACK (ImpColor){ 0, 0, 0, 255 }
#define COL_BLACK_TRANSPARENT (ImpColor){ 0, 0, 0, 128 }
#define COL_WHITE (ImpColor){ 255, 255, 255, 255 }
#define COL_BACKGROUND (ImpColor){ 24, 20, 37, 255 }
#define COL_GOLD (ImpColor){ 254, 174, 52, 255 }
#define COL_BLUE (ImpColor){ 0, 149, 233, 255 }
#define COL_GREEN (ImpColor){ 99, 199, 77, 255 }
#define COL_DARK_GREEN (ImpColor){ 62, 137, 72, 255 }
#define COL_RED (ImpColor){ 228, 59, 68, 255 }

#define BASE_WIDTH 640
#define BASE_HEIGHT 360

//*************************************************************************************
// SCREENS

typedef enum {
   SCREEN_NONE,
   #define X(upper, lower) SCREEN_##upper,
   #include "x_screens.h"
   #undef X
   SCREEN_COUNT
} ScreenType;

const char *screen_names[SCREEN_COUNT] = {
   #define X(upper, lower) #lower,
   #include "x_screens.h"
   #undef X
};

#define X(upper, lower) \
   void lower##_enter(void);\
   void lower##_tick(float dt);\
   void lower##_leave(void);
#include "x_screens.h"
#undef X

//*************************************************************************************
// UI

typedef struct {
   float x;
   float y;
   float w;
   float h;
   const char *text;
   uint8_t hovered;
   uint8_t pressed;
   uint8_t center_text;
} UiElement;

bool ui_button(UiElement *element);
void ui_currency_box(void);

//*************************************************************************************
// GAME DATA

typedef struct {

   bool show_debug;

   // Screen specific stuff.
   ScreenType screen;          // What screen are we on?
   void * screen_scratch;      // Scratch memory for per-screen state.

   // Asset & input handles.
   ImpHandle fnt_quaver;
   ImpHandle tex_sprites;
   #define X(name, ...) ImpHandle name;
   #include "x_inputs.h"
   #include "x_nine_patches.h"
   #include "x_sprites.h"
   #undef X

} GameData;

extern GameData *game;
extern ImpAPI imp;

void screen_swap(ScreenType new_screen);

#endif // FLORAFILL_H
