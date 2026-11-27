#include "game.h"
#include <imp.h>
#include <math.h>
#include <stdio.h>

//*************************************************************************************
static bool element_contains(UiElement *e, int x, int y) {
   return x >= e->x && x < (e->x + e->w) && y >= e->y && y < (e->y + e->h);
}

//*************************************************************************************
static bool rect_contains(float x, float y, float w, float h, float px, float py) {
   return px >= x && px < (x + w) && py >= y && py < (y + h);
}

//*************************************************************************************
float ui_get_area_hovered_time(float current_time, float x, float y, float w, float h) {
   ImpPoint mouse = imp.input_get_mouse_pos();

   if (rect_contains(x, y, w, h, mouse.x, mouse.y))
      return current_time + game->delta_time;

   return 0;
}

//*************************************************************************************
bool ui_button(UiElement *e) {
   bool result = false;
   ImpPoint mouse = imp.input_get_mouse_pos();
   if (element_contains(e, mouse.x, mouse.y)) {
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
      ImpPoint text_size = imp.font_measure_text(game->fnt_quaver, e->text, 0);
      imp.draw_text(
         e->text,
         roundf((e->x + (e->w / 2)) - (text_size.x / 2)),
         roundf((e->y + (e->h / 2)) - (text_size.y / 2)),
         0
      );
   }
   else
      imp.draw_text(e->text, e->x + 3, e->y + 4, 0);

   return result;
}

//*************************************************************************************
void ui_currency_box(void) {
   static int x = 528;
   static int y = 16;
   static int w = 97;
   static int h = 48;

   static float coin_hover_time = 0;
   static float cuttings_hover_time = 0;
   static float cost_hover_time = 0;

   coin_hover_time = ui_get_area_hovered_time(coin_hover_time, x, y + 4, w, 10);
   cuttings_hover_time = ui_get_area_hovered_time(cuttings_hover_time, x, y + 16, w, 10);
   cost_hover_time = ui_get_area_hovered_time(cost_hover_time, x, y + 28, w, 10);

   if (coin_hover_time > 0.5f)
      game->ui_hover_text = "Coins can be used to unlock new plants and upgrades in the shop.";
   if (cuttings_hover_time > 0.5f)
      game->ui_hover_text = "Cuttings can be used to place plants in the garden.";
   if (cost_hover_time > 0.5f)
      game->ui_hover_text = "This is how much the next plant will cost.\nThe more plants you place, the more expensive they get.";

   imp.draw_npatch(game->npatch_textbox, x, y, w, h);
   imp.draw_sprite(game->spr_ui_coin_icon, 0, x + 1, y + 1, 1, 1, 0);
   imp.draw_sprite(game->spr_ui_cutting_icon, 0, x + 1, y + 13, 1, 1, 0);
   imp.draw_sprite(game->spr_ui_plus_icon, 0, x + 1, y + 25, 1, 1, 0);

   imp.draw_set_color(COL_GOLD);
   sprintf(game->text_scratch, "%lld", game->garden_state.coins);
   imp.draw_text(game->text_scratch, x + 15, y + 6, 0);
   imp.draw_set_color(COL_GREEN);
   sprintf(game->text_scratch, "%lld", game->garden_state.cuttings);
   imp.draw_text(game->text_scratch, x + 15, y + 18, 0);
   imp.draw_set_color(COL_WHITE);
   sprintf(game->text_scratch, "%lld", game->garden_state.next_flower_cost);
   imp.draw_text(game->text_scratch, x + 15, y + 30, 0);
}

//*************************************************************************************
void ui_hover_text(float x, float y, const char *text) {
   static int padding_lr = 6;
   static int padding_tb = 6;

   ImpPoint text_size = imp.font_measure_text(game->fnt_quaver, text, 0);
   int box_width = text_size.x + (padding_lr * 2);
   int box_height = text_size.y + (padding_tb * 2);

   int draw_x = x - box_width;
   if (draw_x < 0)
      draw_x = 0;

   int draw_y = y - box_height;
   if (draw_y < 0)
      draw_y = 0;

   imp.draw_set_color(COL_BLACK_TRANSPARENT);
   imp.draw_npatch(
      game->npatch_textbox,
      draw_x + 6,
      draw_y + 6,
      box_width,
      box_height
   );
   imp.draw_set_color(COL_WHITE);
   imp.draw_npatch(
      game->npatch_textbox,
      draw_x,
      draw_y,
      box_width,
      box_height
   );
   imp.draw_text(text, draw_x + padding_lr, draw_y + padding_tb, 0);
}
