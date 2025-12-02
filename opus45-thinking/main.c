#include <SDL.h>
#include <stdlib.h>
#include "render.h"

#define WIDTH  512
#define HEIGHT 512

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow(
        "SDL Animation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 创建纹理
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT
    );
    if (!texture) {
        SDL_Log("SDL_CreateTexture failed: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 分配缓冲区 512*512*4 字节
    void *buffer = malloc(WIDTH * HEIGHT * 4);
    if (!buffer) {
        SDL_Log("malloc failed");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 记录启动时间
    Uint32 start_time = SDL_GetTicks();
    int running = 1;

    // 主循环
    while (running) {
        // 事件处理
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN && 
                event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            }
        }

        // 计算启动以来的秒数
        int step = (SDL_GetTicks() - start_time) / 1000;

        // 调用 render 函数进行渲染
        render(step, buffer);

        // 更新纹理
        SDL_UpdateTexture(texture, NULL, buffer, WIDTH * 4);

        // 渲染到屏幕
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // 清理资源
    free(buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
