#ifndef __MAIN_SCENE_H_
#define __MAIN_SCENE_H_
#include <SDL3/SDL.h>
#include "data.h"

/* Scene-local data — only main_scene.c touches this */
typedef struct MainSceneData
{
  float text_scale;
  float text_x, text_y, text_w, text_h;
} MainSceneData;

/* Helper: get the scene data from AppState */
static inline MainSceneData *main_scene_data(AppState *state)
{
  return (MainSceneData *)state->scene_data;
}

extern const Scene main_scene;

#endif /* __MAIN_SCENE_H_ */