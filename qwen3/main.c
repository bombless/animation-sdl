#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 512
#define HEIGHT 512
#define BUFFER_SIZE (WIDTH * HEIGHT * 4)

void render(int step, void *buffer);

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Rectangle Animation",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             WIDTH, HEIGHT);
    if (!texture) {
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 创建512*512*4字节的缓冲区
    void *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Could not allocate buffer\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 记录程序启动时间
    Uint32 startTime = SDL_GetTicks();

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // 计算从启动以来经过的秒数
        Uint32 currentTime = SDL_GetTicks();
        int seconds = (currentTime - startTime) / 1000;

        // 调用渲染函数
        render(seconds, buffer);

        // 更新纹理
        SDL_UpdateTexture(texture, NULL, buffer, WIDTH * 4);

        // 清除渲染器
        SDL_RenderClear(renderer);

        // 复制纹理到渲染器
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // 显示
        SDL_RenderPresent(renderer);

        // 控制帧率，大约60 FPS
        SDL_Delay(16);
    }

    // 清理资源
    free(buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
