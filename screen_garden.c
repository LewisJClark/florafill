#include <imp.h>
#include "game.h"
#include "lewtils.h"

static Timer visitor_timer = {0};

//*************************************************************************************
void garden_enter(void) {
   visitor_timer = timer_create(.5f, true);
}

//*************************************************************************************
void garden_tick(float dt) {
   GardenScreenState *state = &game->garden_state;
   ImpPoint mouse_pos = imp.input_get_mouse_pos();

   if (timer_tick(&visitor_timer, dt)) {
      int entity_handle = entity_create_visitor(
         imp.random_frange(0, BASE_WIDTH),
         imp.random_frange(0, BASE_HEIGHT)
      );
   }

   for (int i = 0; i < ENTITY_MAX; i++) {
      if (!game->entities[i].active)
         continue;
      entity_update(&game->entities[i], dt);
   }

   imp.draw_begin();
   imp.draw_clear_color(COL_BACKGROUND);

   imp.draw_apply_camera(game->camera);
   for (int i = 0; i < ENTITY_MAX; i++) {
      if (!game->entities[i].active)
         continue;
      entity_draw(&game->entities[i]);
   }
   imp.draw_remove_camera();

   imp.draw_npatch(game->npatch_textbox, 528, 326, 96, 16, false);
   imp.draw_npatch(game->npatch_leaf_border, 0, 0, BASE_WIDTH, BASE_HEIGHT, true);
   ui_currency_box();

   if (game->ui_hover_text != NULL)
      ui_hover_text(mouse_pos.x, mouse_pos.y, game->ui_hover_text);

   imp.draw_end();
}

//*************************************************************************************
void garden_leave(void) {

}
