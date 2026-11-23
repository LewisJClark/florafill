#ifndef LEWTILS_H
#define LEWTILS_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
   void *base;
   size_t size;
   size_t offset;
   size_t committed;
} MemArena;

typedef void *(*LewAlloc)(size_t size);
typedef void (*LewFree)(void *ptr);

void lew_set_alloc(LewAlloc alloc_proc);
void lew_set_free(LewFree free_proc);

MemArena *lew_arena_create(size_t size);
void lew_arena_destroy(MemArena *arena);
void *lew_arena_alloc(MemArena *arena, size_t size);
void lew_arena_clear(MemArena *arena);

#endif // LEWTILS_H

//********************************************************************************************************************
// IMPLEMENTATION
//********************************************************************************************************************

#ifdef LEWTILS_IMPL

static LewAlloc lew_alloc = malloc;
static LewFree lew_free = free;

#define is_pwr_of_two(x) ((x != 0) && ((x & (x - 1)) == 0))

//*************************************************************************************
static uintptr_t align_forward(uintptr_t ptr, size_t alignment) {
   if (!is_pwr_of_two(alignment))
      return 0;

   uintptr_t p = ptr;
   uintptr_t align = (uintptr_t)alignment;
   uintptr_t modulo = p & (align - 1);

   if (modulo)
      p += align - modulo;

   return p;
}

//*************************************************************************************
void lew_set_alloc(LewAlloc alloc_proc) {
   lew_alloc = alloc_proc;
}

//*************************************************************************************
void lew_set_free(LewFree free_proc) {
   lew_free = free_proc;
}

//*************************************************************************************
MemArena *lew_arena_create(size_t size) {
   MemArena *arena = lew_alloc(sizeof(MemArena));
   arena->base = lew_alloc(size);
   arena->size = size;

   return arena;
}

//*************************************************************************************
void lew_arena_destroy(MemArena *arena) {
   lew_free(arena->base);
   lew_free(arena);
}

//*************************************************************************************
void *lew_arena_alloc(MemArena *arena, size_t size) {
   uintptr_t current = (uintptr_t)arena->base + (uintptr_t)arena->offset;
   uintptr_t offset = align_forward(current, sizeof(void *) * 2);
   offset -= (uintptr_t)arena->base;

   if (offset + size > arena->size)
      return NULL;

   arena->committed += size;
   void *result = (uint8_t *)arena->base + offset;
   arena->offset = offset + size;

   return result;
}

//*************************************************************************************
void lew_arena_clear(MemArena *arena) {
   arena->offset = 0;
   arena->committed = 0;
}

#endif // LEWTILS_IMPL
