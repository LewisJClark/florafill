#include "game.h"

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
