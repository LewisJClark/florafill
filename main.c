#include "florafill.h"
#include <imp.h>

#define LEWTILS_IMPL
#include "lewtils.h"

#include "florafill.c"
#include "screens.c"

GameData *game;
ImpAPI imp = {0};

//*************************************************************************************
__declspec(dllexport) void game_load(ImpAPI *api) {
   imp = *api;

   imp.window_set_title("Florafill");
   imp.window_set_fps(144);
   imp.window_set_size(BASE_WIDTH, BASE_HEIGHT);
   imp.window_canvas_set_size(BASE_WIDTH, BASE_HEIGHT);

   game = imp.alloc_game_data(sizeof(GameData));
   game->screen_scratch = imp.alloc(10240000);

   screen_swap(SCREEN_MAIN_MENU);
}


//*************************************************************************************
__declspec(dllexport) void game_reload(ImpAPI *api, void *game_data) {
   imp = *api;
   game = (GameData *)game_data;
}


//*************************************************************************************
__declspec(dllexport) void game_tick(float dt) {

   switch (game->screen) {
      default: break;

      #define X(upper, lower) case SCREEN_##upper: lower##_tick(dt); break;
      #include "_screen_types.h"
      #undef X
   }

}


//*************************************************************************************
__declspec(dllexport) void game_quit(void) {
   imp.free(game->screen_scratch);
   imp.free(game);
}
