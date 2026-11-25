#include <imp.h>
#include "game.h"

static UiElement play_button = {
   .x = (BASE_WIDTH / 2) - 64, .y = 240,
   .w = 128, .h = 16,
   .text = "Play",
   .center_text = true
};

static UiElement settings_button = {
   .x = (BASE_WIDTH / 2) - 64, .y = 264,
   .w = 128, .h = 16,
   .text = "Settings",
   .center_text = true
};

static UiElement quit_button = {
   .x = (BASE_WIDTH / 2) - 64, .y = 288,
   .w = 128, .h = 16,
   .text = "Quit",
   .center_text = true
};

//*************************************************************************************
void main_menu_enter(void) {

}

//*************************************************************************************
void main_menu_tick(float dt) {
   ImpPoint mouse_pos = imp.input_get_mouse_pos();

   imp.draw_begin();
   imp.draw_clear_color(COL_BACKGROUND);

   if (ui_button(&play_button))
      screen_swap(SCREEN_GARDEN);
   if (ui_button(&settings_button))
      imp.log(IMP_LOG_INFO, "Settings pressed!");
   if (ui_button(&quit_button))
      imp.quit();

   imp.draw_end();
}

//*************************************************************************************
void main_menu_leave(void) {

}
