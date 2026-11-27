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

#define GARDEN_SIZE 1024

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

typedef struct {
   uint64_t coins;
   uint64_t cuttings;
   uint64_t next_flower_cost;
} GardenScreenState;

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
   float hovered_time;
   const char *hover_text;
} UiElement;

bool ui_button(UiElement *element);
void ui_currency_box(void);
void ui_hover_text(float x, float y, const char *text);
float ui_get_area_hovered_time(float current_time, float x, float y, float w, float h);

//*************************************************************************************
// ENTITIES

#define ENTITY_MAX 4096

typedef enum {
   ENT_NONE,
   #define X(lower, upper, ...) ENT_##upper,
   #include "x_entities.h"
   #undef X
   ENT_COUNT
} EntityType;

typedef struct {
   bool active;
   EntityType type;
   float x;
   float y;
   ImpHandle sprite;
   float sprite_frame;
   float sprite_xscale;
   float sprite_yscale;
   float sprite_angle;
   float xspeed;
   float yspeed;
} Entity;

void entity_update(Entity *e, float dt);
void entity_draw(Entity *e);

#define X(lower, upper, ...) int entity_create_##lower(__VA_ARGS__);
#include "x_entities.h"
#undef X
#define X(lower, upper, ...) void entity_update_##lower(Entity *e, float dt);
#include "x_entities.h"
#undef X
#define X(lower, upper, ...) void entity_draw_##lower(Entity *e);
#include "x_entities.h"
#undef X
#define X(lower, upper, ...) void entity_destroy_##lower(Entity *e);
#include "x_entities.h"
#undef X

//*************************************************************************************
// GAME DATA

typedef struct {

   float delta_time;
   bool show_debug;
   char text_scratch[2048];
   const char *ui_hover_text;
   ImpHandle camera;

   Entity entities[ENTITY_MAX];

   // Screen specific stuff.
   ScreenType screen;          // What screen are we on?
   void * screen_scratch;      // Scratch memory for per-screen state.
   GardenScreenState garden_state;

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
int entity_get_free_handle(void);
Entity *entity_ptr_from_handle(int handle);

#endif // FLORAFILL_H
