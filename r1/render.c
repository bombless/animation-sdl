#include <stdint.h>
#include <string.h>

void render(int step, void *buffer) {
    uint8_t *pixels = (uint8_t*)buffer;
    const int width = 512;
    const int height = 512;
    
    // 计算矩形边长（对512取模）
    int side_length = step % 512;
    
    // 清空缓冲区为黑色
    memset(pixels, 0, width * height * 4);
    
    // 如果边长为0，则不绘制
    if (side_length == 0) {
        return;
    }
    
    // 计算矩形位置（居中）
    int start_x = (width - side_length) / 2;
    int start_y = (height - side_length) / 2;
    
    // 绘制矩形（白色边框）
    for (int y = 0; y < side_length; y++) {
        for (int x = 0; x < side_length; x++) {
            int px = start_x + x;
            int py = start_y + y;
            
            // 只绘制边框
            if (x == 0 || x == side_length - 1 || y == 0 || y == side_length - 1) {
                int index = (py * width + px) * 4;
                pixels[index] = 255;     // R
                pixels[index + 1] = 255; // G
                pixels[index + 2] = 255; // B
                pixels[index + 3] = 255; // A
            }
        }
    }
}
