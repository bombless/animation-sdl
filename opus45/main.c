#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "render.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    void *buffer = NULL;
    int running = 1;
    Uint32 start_time;
    
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL初始化失败: %s\n", SDL_GetError());
        return 1;
    }
    
    // 创建窗口
    window = SDL_CreateWindow(
        "animation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!window)
    {
        fprintf(stderr, "窗口创建失败: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "渲染器创建失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // 创建纹理
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );
    
    if (!texture)
    {
        fprintf(stderr, "纹理创建失败: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // 分配像素缓冲区
    buffer = malloc(WIDTH * HEIGHT * BYTES_PER_PIXEL);
    if (!buffer)
    {
        fprintf(stderr, "内存分配失败\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // 记录启动时间
    start_time = SDL_GetTicks();
    
    // 主循环
    while (running)
    {
        SDL_Event event;
        
        // 处理事件
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = 0;
                }
            }
        }
        
        // 计算启动以来的秒数
        Uint32 current_time = SDL_GetTicks();
        int elapsed_seconds = (current_time - start_time) / 1000;
        
        // 调用render函数
        render(elapsed_seconds, buffer);
        
        // 更新纹理
        SDL_UpdateTexture(texture, NULL, buffer, WIDTH * BYTES_PER_PIXEL);
        
        // 清空并渲染
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        // 控制帧率（约60fps）
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
