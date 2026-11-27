#include <imp.h>
#include "game.h"

//*************************************************************************************
int entity_visitor_create(float x, float y) {

   int handle = entity_get_free_handle();
   Entity *e = entity_ptr_from_handle(handle);
   if (e == NULL)
      return -1;

   e->active = true;
   e->type = ENT_VISITOR;
   e->sprite = game->spr_visitor_bird;
   e->xspeed = 16;

   return handle;
}

//*************************************************************************************
void entity_visitor_update(Entity *e, float dt) {

}

//*************************************************************************************
void entity_visitor_draw(Entity *e) {

}

//*************************************************************************************
void entity_visitor_destroy(Entity *e) {

}
