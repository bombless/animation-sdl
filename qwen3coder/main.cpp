// main.c
#include <SDL.h>
#include <stdio.h>
#include <time.h>

// 声明 render.c 中的函数
extern "C" void render(int step, void *buffer);

// 屏幕常量
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const int SCREEN_PITCH = SCREEN_WIDTH * 4; // 4 bytes per pixel (RGBA)

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* sdl_renderer = NULL; // 我们不直接用它绘图，但需要它来创建纹理
    SDL_Texture* screen_texture = NULL;
    SDL_Surface* screen_surface = NULL;
    Uint32 frame_start, frame_time;

    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    window = SDL_CreateWindow("Render Test",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    // 创建渲染器
    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    // 创建一个用于绘制的软件表面
    screen_surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                          0x00FF0000, // R
                                          0x0000FF00, // G
                                          0x000000FF, // B
                                          0xFF000000  // A
                                         );
    if (screen_surface == NULL)
    {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    // 创建一个纹理，用于将表面内容快速复制到渲染器
    screen_texture = SDL_CreateTexture(sdl_renderer,
                                       SDL_PIXELFORMAT_ARGB8888, // 匹配 surface 格式
                                       SDL_TEXTUREACCESS_STREAMING, // 允许频繁更新
                                       SCREEN_WIDTH, SCREEN_HEIGHT);
    if (screen_texture == NULL)
    {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(screen_surface);
        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 5;
    }

    // --- 主循环 ---
    bool quit = false;
    SDL_Event e;

    // 记录程序启动时间
    time_t start_time = time(NULL);

    while (!quit)
    {
        frame_start = SDL_GetTicks(); // 记录帧开始时间

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // 1. 计算自启动以来的秒数
        time_t current_time = time(NULL);
        int elapsed_seconds = (int)(current_time - start_time);

        // 2. 调用 render 函数，将结果绘制到 surface 的像素缓冲区
        render(elapsed_seconds, screen_surface->pixels);

        // 3. 将 surface 的内容更新到纹理
        SDL_UpdateTexture(screen_texture, NULL, screen_surface->pixels, screen_surface->pitch);

        // 4. 清空渲染器
        SDL_RenderClear(sdl_renderer);

        // 5. 将纹理内容复制到渲染器
        SDL_RenderCopy(sdl_renderer, screen_texture, NULL, NULL);

        // 6. 显示渲染结果
        SDL_RenderPresent(sdl_renderer);

        // 简单的帧率控制 (60 FPS)
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < 16) // 1000 ms / 60 fps ~ 16.67 ms
        {
            SDL_Delay(16 - frame_time);
        }
    }

    // --- 清理资源 ---
    SDL_DestroyTexture(screen_texture);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
