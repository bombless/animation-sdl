#include "render.h"
#include <string.h>

#define WIDTH  512
#define HEIGHT 512

void render(int step, void *buffer)
{
    unsigned char *pixels = (unsigned char *)buffer;
    
    // 清空缓冲区（黑色背景）
    memset(buffer, 0, WIDTH * HEIGHT * 4);
    
    // 计算矩形边长：对秒数取模512
    int side = step % 512;
    
    // 绘制白色矩形（从左上角开始）
    for (int y = 0; y < side; y++) {
        for (int x = 0; x < side; x++) {
            int index = (y * WIDTH + x) * 4;
            pixels[index + 0] = 255;    // R
            pixels[index + 1] = 255;    // G
            pixels[index + 2] = 255;    // B
            pixels[index + 3] = 255;    // A
        }
    }
}
