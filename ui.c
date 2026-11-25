#include "game.h"
#include <imp.h>
#include <math.h>

//*************************************************************************************
static bool ui_element_contains(UiElement *e, int x, int y) {
   return x >= e->x && x < (e->x + e->w) && y >= e->y && y < (e->y + e->h);
}

//*************************************************************************************
bool ui_button(UiElement *e) {
   bool result = false;
   ImpPoint mouse = imp.input_get_mouse_pos();
   if (ui_element_contains(e, mouse.x, mouse.y)) {
      e->hovered = 1;
      if (imp.input_down(game->inp_confirm))
         e->pressed = 1;
      else
         e->pressed = 0;
      if (imp.input_released(game->inp_confirm))
         result = true;
   }
   else {
      e->hovered = 0;
      e->pressed = 0;
   }

   if (e->pressed)
      imp.draw_npatch(game->npatch_button_pressed, e->x, e->y, e->w, e->h);
   else if (e->hovered)
      imp.draw_npatch(game->npatch_button_hovered, e->x, e->y, e->w, e->h);
   else
      imp.draw_npatch(game->npatch_button_normal, e->x, e->y, e->w, e->h);

   if (e->center_text) {
      ImpPoint text_size = imp.font_measure_text(game->fnt_quaver, e->text);
      imp.draw_text(
         e->text,
         roundf((e->x + (e->w / 2)) - (text_size.x / 2)),
         roundf((e->y + (e->h / 2)) - (text_size.y / 2))
      );
   }
   else
      imp.draw_text(e->text, e->x + 3, e->y + 4);

   return result;
}

//*************************************************************************************
void ui_currency_box(void) {
   static int x = 528;
   static int y = 16;
   static int w = 97;
   static int h = 48;
   imp.draw_npatch(game->npatch_textbox, x, y, w, h);
   imp.draw_set_color(COL_GOLD);
   imp.draw_text("Coins", x + 6, y + 6);
   imp.draw_set_color(COL_GREEN);
   imp.draw_text("Cuttings", x + 6, y + 24);
   imp.draw_set_color(COL_WHITE);
}
