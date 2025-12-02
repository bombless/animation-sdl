#include <SDL.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// 声明render函数
void render(int step, void *buffer);

#define WIDTH 512
#define HEIGHT 512
#define BPP 4  // 每个像素4字节（RGBA）

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow(
        "矩形动画",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        fprintf(stderr, "创建窗口失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer) {
        fprintf(stderr, "创建渲染器失败: %s\n", SDL_GetError());
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
        fprintf(stderr, "创建纹理失败: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // 分配像素缓冲区（512x512x4字节）
    uint8_t *pixel_buffer = (uint8_t*)malloc(WIDTH * HEIGHT * BPP);
    if (!pixel_buffer) {
        fprintf(stderr, "分配内存失败\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Event event;
    int running = 1;
    Uint32 start_time = SDL_GetTicks();
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            }
        }
        
        // 计算程序运行秒数
        Uint32 current_time = SDL_GetTicks();
        int step = (current_time - start_time) / 1000;  // 转换为秒
        
        // 调用render函数
        render(step, pixel_buffer);
        
        // 更新纹理
        SDL_UpdateTexture(texture, NULL, pixel_buffer, WIDTH * BPP);
        
        // 渲染
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    // 清理资源
    free(pixel_buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
