#include <imp.h>
#include "game.h"
#include "lewtils.h"

//*************************************************************************************
void garden_enter(void) {

}

//*************************************************************************************
void garden_tick(float dt) {
   GardenScreenState *state = &game->garden_state;
   ImpPoint mouse_pos = imp.input_get_mouse_pos();

   imp.draw_begin();
   imp.draw_clear_color(COL_BACKGROUND);
   ui_currency_box();
   imp.draw_npatch(game->npatch_textbox, 528, 326, 96, 16);
   imp.draw_sprite(game->spr_ui_border, 0, 0, 0, 1, 1, 0);

   if (game->ui_hover_text != NULL)
      ui_hover_text(mouse_pos.x, mouse_pos.y, game->ui_hover_text);

   imp.draw_end();
}

//*************************************************************************************
void garden_leave(void) {

}
