#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

// 声明render函数
void render(int step, void *buffer);

int main(int argc, char *argv[]) {
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow(
        "SDL Rectangle Animation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        512, 512,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "创建窗口失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "创建渲染器失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 创建纹理（32位RGBA格式）
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        512, 512
    );
    if (!texture) {
        fprintf(stderr, "创建纹理失败: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 分配像素缓冲区 (512*512*4 字节)
    unsigned char *buffer = (unsigned char *)malloc(512 * 512 * 4);
    if (!buffer) {
        fprintf(stderr, "内存分配失败\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 主循环标志
    int running = 1;
    SDL_Event event;

    // 主循环
    while (running) {
        // 处理事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // 获取应用启动以来的毫秒数
        int ticks = SDL_GetTicks();

        // 调用render函数填充缓冲区
        render(ticks, buffer);

        // 更新纹理
        SDL_UpdateTexture(texture, NULL, buffer, 512 * 4);

        // 渲染到屏幕
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        // 控制帧率（约60 FPS）
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
