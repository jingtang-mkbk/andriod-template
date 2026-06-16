#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#define STB_DS_IMPLEMENTATION    /* generate stb_ds function bodies in this TU */
#include <stdlib.h>
#include <SDL3/SDL_main.h>
#include "scenes/main_scene/index.h"
#include "scenes/test_scene/index.h"

/* Scene switcher: call with scene name string to request a switch next frame */
void switch_scene(AppState *state, const char *name)
{
    const Scene *s = shget(state->scene_map, name);
    if (s)
        state->next_scene = s;
    else
        SDL_Log("switch_scene: unknown scene '%s'", name);
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_WindowFlags flag = 0;
    int width, height;

    /* Must allocate on heap, stack variable would be destroyed after return */
    AppState *state = (AppState *)SDL_calloc(1, sizeof(AppState));
    if (!state)
    {
        return SDL_APP_FAILURE;
    }

#ifdef __ANDROID__
    width = 392;
    height = 872;
    flag = SDL_WINDOW_FULLSCREEN;
#else
    width = 800;
    height = 600;
    flag = SDL_WINDOW_RESIZABLE;
#endif
    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", width, height, flag, &state->window, &state->renderer))
    {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        SDL_free(state);
        return SDL_APP_FAILURE;
    }

    state->display_scale = SDL_GetWindowDisplayScale(state->window);

    /* Build scene hash map: string name → Scene* */
    state->scene_map = NULL;
    shput(state->scene_map, "main_scene", &main_scene);
    shput(state->scene_map, "test_scene", &test_scene);

    /* Boot the first scene */
    state->current_scene = &main_scene;
    state->next_scene = &main_scene;
    state->current_scene->init(state);
    state->switch_scene = switch_scene;

    *appstate = state;

    SDL_Log("Window created with display scale: %f", state->display_scale);
    SDL_SetRenderVSync(state->renderer, -1);
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState *state = (AppState *)appstate;
    state->current_scene->event(state, event);
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *state = (AppState *)appstate;

    /* Check for pending scene switch */
    if (state->next_scene != state->current_scene)
    {
        state->current_scene->deinit(state);
        state->current_scene = state->next_scene;
        state->current_scene->init(state);
    }

    state->current_scene->iterate(state);
    return state->app_quit;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState *state = (AppState *)appstate;
    if (state)
    {
        shfree(state->scene_map);
        SDL_free(state);
    }
}
