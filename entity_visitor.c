#include <imp.h>
#include "game.h"

//*************************************************************************************
int entity_create_visitor(float x, float y) {
   int handle = entity_get_free_handle();
   Entity *e = entity_ptr_from_handle(handle);
   if (e == NULL)
      return -1;

   e->active = true;
   e->type = ENT_VISITOR;
   e->sprite = game->spr_visitor_bird;
   e->sprite_xscale = 1;
   e->sprite_yscale = 1;
   e->xspeed = 16;
   e->x = x;
   e->y = y;


   return handle;
}

//*************************************************************************************
void entity_update_visitor(Entity *e, float dt) {

}

//*************************************************************************************
void entity_draw_visitor(Entity *e) {
   imp.draw_sprite(e->sprite, e->sprite_frame, e->x, e->y, e->sprite_xscale, e->sprite_yscale, e->sprite_angle);
}

//*************************************************************************************
void entity_destroy_visitor(Entity *e) {

}
