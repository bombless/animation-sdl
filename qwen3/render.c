#include <string.h>

#define WIDTH 512
#define HEIGHT 512

void render(int step, void *buffer) {
    // 清空缓冲区（设置为黑色背景）
    memset(buffer, 0, WIDTH * HEIGHT * 4);
    
    // 计算矩形边长（对启动秒数取模512）
    int size = step % 512;
    
    // 计算矩形的起始位置，使其居中显示
    int startX = (WIDTH - size) / 2;
    int startY = (HEIGHT - size) / 2;
    
    // 设置矩形颜色为白色（ARGB格式：0xFFFFFFFF）
    unsigned int color = 0xFFFFFFFF;
    
    // 绘制实心矩形
    for (int y = startY; y < startY + size; y++) {
        for (int x = startX; x < startX + size; x++) {
            // 直接访问缓冲区中的像素
            ((unsigned int *)buffer)[y * WIDTH + x] = color;
        }
    }
}
