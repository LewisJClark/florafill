#include "game.h"

//*************************************************************************************
int entity_get_free_handle(void) {
   for (int i = 0; i < ENTITY_MAX; i++) {
      if (game->entities[i].active)
         continue;
      return i;
   }
   return -1;
}

//*************************************************************************************
Entity *entity_ptr_from_handle(int handle) {
   if (handle == -1)
      return NULL;

   if (!game->entities[handle].active)
      return NULL;

   return &game->entities[handle];
}


//*************************************************************************************
// Swaps to the new screen, calling *_leave for the old screen
// and then *_enter for the new one.
void screen_swap(ScreenType new_screen) {
   if (game->screen != SCREEN_NONE) {
      switch (game->screen) {
         default: break;

         #define X(upper, lower) case SCREEN_##upper: lower##_leave(); break;
         #include "x_screens.h"
         #undef X
      }
   }

   game->screen = new_screen;

   switch (game->screen) {
      default: break;

      #define X(upper, lower) case SCREEN_##upper: lower##_enter(); break;
      #include "x_screens.h"
      #undef X
   }
}
