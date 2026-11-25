#include "game.h"
#include <imp.h>

#include "game.c"
#include "ui.c"
#include "screen_main_menu.c"
#include "screen_garden.c"

GameData *game;
ImpAPI imp = {0};

//*************************************************************************************
__declspec(dllexport) void game_load(ImpAPI *api) {
   imp = *api;

   game = imp.alloc_game_data(sizeof(GameData));
   game->screen_scratch = imp.alloc(10240000);

   imp.window_set_title("Florafill");
   imp.window_set_fps(144);
   imp.window_set_size(BASE_WIDTH, BASE_HEIGHT);
   imp.window_canvas_set_size(BASE_WIDTH, BASE_HEIGHT);

   // Load all of the assets.
   game->fnt_quaver = imp.font_create("assets/quaver.ttf", 8);
   game->tex_sprites = imp.texture_create("assets/sprites.png");
   #define X(name, ...) game->name = imp.sprite_create(__VA_ARGS__);
   #include "x_sprites.h"
   #undef X
   #define X(name, ...) game->name = imp.npatch_create(__VA_ARGS__);
   #include "x_nine_patches.h"
   #undef X

   // Create all of the input actions.
   #define X(name, count, ...) game->name = imp.input_create((ImpInput [count]){ __VA_ARGS__ }, count);
   #include "x_inputs.h"
   #undef X

   imp.draw_set_font(game->fnt_quaver);
   imp.input_hide_mouse();
   screen_swap(SCREEN_MAIN_MENU);
}


//*************************************************************************************
__declspec(dllexport) void game_reload(ImpAPI *api, void *game_data) {
   imp = *api;
   game = (GameData *)game_data;
}


//*************************************************************************************
__declspec(dllexport) void game_tick(float dt) {
   ImpPoint mouse_pos = imp.input_get_mouse_pos();

   switch (game->screen) {
      default: break;

      #define X(upper, lower) case SCREEN_##upper: lower##_tick(dt); break;
      #include "x_screens.h"
      #undef X
   }

   if (imp.input_pressed(game->inp_toggle_debug))
      game->show_debug = !game->show_debug;

   if (game->show_debug) {
      imp.draw_begin();
      imp.draw_set_color(COL_BLACK_TRANSPARENT);
      imp.draw_rect(0, 0, BASE_WIDTH, 16, true);
      imp.draw_set_color(COL_WHITE);
      imp.draw_text("FPS:", 3, 3);
      imp.draw_end();
   }

   // Draw the cursor after everything else.
   imp.draw_begin();
   if (imp.input_down(game->inp_confirm)) {
      imp.draw_set_color(COL_BLACK_TRANSPARENT);
      imp.draw_sprite(game->spr_cursor_click, 0, mouse_pos.x + 3, mouse_pos.y + 3, 1, 1, 0);
      imp.draw_set_color(COL_WHITE);
      imp.draw_sprite(game->spr_cursor_click, 0, mouse_pos.x, mouse_pos.y, 1, 1, 0);
   }
   else {
      imp.draw_set_color(COL_BLACK_TRANSPARENT);
      imp.draw_sprite(game->spr_cursor_normal, 0, mouse_pos.x + 3, mouse_pos.y + 3, 1, 1, 0);
      imp.draw_set_color(COL_WHITE);
      imp.draw_sprite(game->spr_cursor_normal, 0, mouse_pos.x, mouse_pos.y, 1, 1, 0);
   }
   imp.draw_end();

}


//*************************************************************************************
__declspec(dllexport) void game_quit(void) {
   imp.free(game->screen_scratch);
   imp.free(game);
}
