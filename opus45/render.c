#include "render.h"
#include <string.h>

void render(int step, void *buffer)
{
    unsigned char *pixels = (unsigned char *)buffer;
    
    // 计算矩形边长：对512取模
    int side = step % 512;
    
    // 清空缓冲区为黑色
    memset(buffer, 0, WIDTH * HEIGHT * BYTES_PER_PIXEL);
    
    // 计算矩形位置（居中显示）
    int start_x = (WIDTH - side) / 2;
    int start_y = (HEIGHT - side) / 2;
    
    // 绘制白色矩形
    for (int y = start_y; y < start_y + side; y++)
    {
        for (int x = start_x; x < start_x + side; x++)
        {
            // 确保在边界内
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                int index = (y * WIDTH + x) * BYTES_PER_PIXEL;
                // RGBA格式
                pixels[index + 0] = 255;  // R
                pixels[index + 1] = 255;  // G
                pixels[index + 2] = 255;  // B
                pixels[index + 3] = 255;  // A
            }
        }
    }
}
