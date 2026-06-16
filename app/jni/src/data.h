#ifndef DATA_H
#define DATA_H
#include <SDL3/SDL.h>
#include "stb_ds.h"

/* Forward declaration */
typedef struct AppState AppState;

/* Scene interface — like a virtual table, one per scene */
typedef struct Scene
{
  void (*init)(AppState *);
  void (*event)(AppState *, SDL_Event *);
  void (*iterate)(AppState *);
  void (*deinit)(AppState *);
} Scene;

/* Hash map entry: string key → Scene pointer */
typedef struct SceneEntry
{
  char *key;
  const Scene *value;
} SceneEntry;

typedef struct AppState
{
  /* SDL resources (lifetime of the app) */
  SDL_Window *window;
  SDL_Renderer *renderer;
  int app_quit;
  float display_scale;

  /* Scene routing */
  SceneEntry *scene_map; /* string → Scene* hash table */
  const Scene *current_scene;
  const Scene *next_scene;
  void *scene_data;
  void (*switch_scene)(AppState *, const char *name);
} AppState;

#endif // __DATA_H_