#ifndef DATA_H
#define DATA_H
#include <SDL3/SDL.h>

/* Forward declaration */
typedef struct AppState AppState;

/* Scene interface — like a virtual table, one per scene */
typedef struct Scene
{
  void (*init)(AppState *state);
  void (*event)(AppState *state, SDL_Event *event);
  void (*iterate)(AppState *state);
  void (*deinit)(AppState *state);
} Scene;

typedef struct AppState
{
  /* SDL resources (lifetime of the app) */
  SDL_Window *window;
  SDL_Renderer *renderer;
  int app_quit;
  float display_scale;

  /* Scene routing */
  const Scene *current_scene;
  const Scene *next_scene;

  /* Scene-local data — allocated/freed by each scene's init/deinit */
  void *scene_data;
} AppState;

/* Call this from any scene's event to schedule a switch next frame */
void switch_scene(AppState *state, const Scene *new_scene);

#endif // __DATA_H_