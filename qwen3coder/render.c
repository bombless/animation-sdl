// render.c
#include <stdint.h>
#include <string.h> // for memset

/**
 * @brief 渲染函数
 * @param step 应用启动以来的秒数
 * @param buffer 指向 512x512x4 字节 RGBA 缓冲区的指针
 */
void render(int step, void *buffer) {
    uint32_t *pixels = (uint32_t*)buffer;
    const int width = 512;
    const int height = 512;

    // 计算矩形边长
    int side_length = step % 512;

    // 将整个缓冲区清空为黑色 (ARGB: 0xFF000000)
    // 每个像素是 uint32_t，所以清空 512*512 个 uint32_t
    memset(buffer, 0, width * height * 4);

    // 绘制一个红色矩形 (ARGB: 0xFFFF0000)
    // 矩形从 (0, 0) 开始
    uint32_t red_pixel = 0xFFFF0000; // Red, Green=0, Blue=0, Alpha=255
    for (int y = 0; y < side_length; y++) {
        for (int x = 0; x < side_length; x++) {
            pixels[y * width + x] = red_pixel;
        }
    }
}
