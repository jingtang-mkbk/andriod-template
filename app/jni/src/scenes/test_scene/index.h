#ifndef __TEST_SCENE_H_
#define __TEST_SCENE_H_
#include <SDL3/SDL.h>
#include "data.h"

/* Scene-local data */
typedef struct TestSceneData
{
  float text_scale;
  float text_w, text_h;
} TestSceneData;

static inline TestSceneData *test_scene_data(AppState *state)
{
  return (TestSceneData *)state->scene_data;
}

extern const Scene test_scene;

#endif /* __TEST_SCENE_H_ */
