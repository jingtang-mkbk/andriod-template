#include "index.h"
#include "scenes/main_scene/index.h"

static void init(AppState *state)
{
  TestSceneData *d = (TestSceneData *)SDL_calloc(1, sizeof(TestSceneData));
  state->scene_data = d;

  const char *text = "Back";
  d->text_scale = state->display_scale * 4.0f;
  d->text_w = SDL_strlen(text) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
  d->text_h = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
}

static void event(AppState *state, SDL_Event *event)
{
  TestSceneData *d = test_scene_data(state);

  if (event->type == SDL_EVENT_KEY_DOWN ||
      event->type == SDL_EVENT_QUIT)
  {
    state->app_quit = SDL_APP_SUCCESS;
    return;
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
  {
    float mx = event->button.x;
    float my = event->button.y;

    SDL_ConvertEventToRenderCoordinates(state->renderer, event);
    mx = event->button.x;
    my = event->button.y;

    /* "Back" text at (0, 100) */
    float tx = 0.0f;
    float ty = 50.0f * d->text_scale;
    float tw = d->text_w * d->text_scale;
    float th = d->text_h * d->text_scale;
    if (mx >= tx && mx <= tx + tw &&
        my >= ty && my <= ty + th)
    {
      switch_scene(state, &main_scene);
    }
  }
}

static void iterate(AppState *state)
{
  TestSceneData *d = test_scene_data(state);

  SDL_SetRenderDrawColor(state->renderer, 0, 80, 0, 255);
  SDL_RenderClear(state->renderer);

  SDL_SetRenderScale(state->renderer, d->text_scale, d->text_scale);
  SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);
  SDL_RenderDebugText(state->renderer, 0.0f, 50.0f, "Back");
  SDL_SetRenderScale(state->renderer, 1.0f, 1.0f);

  SDL_RenderPresent(state->renderer);
}

static void deinit(AppState *state)
{
  SDL_free(state->scene_data);
  state->scene_data = NULL;
}

const Scene test_scene = {
    .init = init,
    .event = event,
    .iterate = iterate,
    .deinit = deinit,
};
