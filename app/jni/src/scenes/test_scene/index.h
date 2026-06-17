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

extern const Scene test_scene;

#endif /* __TEST_SCENE_H_ */
