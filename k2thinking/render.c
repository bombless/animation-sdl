// 渲染函数：在缓冲区中绘制居中矩形
// step: 应用启动以来的毫秒数（用于动画）
// buffer: 512*512*4字节的RGB像素缓冲区（RGBA32格式）
void render(int step, void *buffer) {
    unsigned char *pixels = (unsigned char *)buffer;
    
    // 计算矩形边长（0-511像素）
    int side = step % 512;
    
    // 计算矩形左上角坐标（居中显示）
    int startX = (512 - side) / 2;
    int startY = (512 - side) / 2;
    
    // 清空整个缓冲区（填充黑色背景）
    // 每个像素4字节：R, G, B, A
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            int index = (y * 512 + x) * 4;
            pixels[index]   = 0;   // R
            pixels[index+1] = 0;   // G
            pixels[index+2] = 0;   // B
            pixels[index+3] = 255; // A
        }
    }
    
    // 在中心区域绘制白色矩形
    for (int y = startY; y < startY + side; y++) {
        for (int x = startX; x < startX + side; x++) {
            // 确保坐标在有效范围内
            if (x >= 0 && x < 512 && y >= 0 && y < 512) {
                int index = (y * 512 + x) * 4;
                pixels[index]   = 255; // R
                pixels[index+1] = 255; // G
                pixels[index+2] = 255; // B
                pixels[index+3] = 255; // A
            }
        }
    }
}
