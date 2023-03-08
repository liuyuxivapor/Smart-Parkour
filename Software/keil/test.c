#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 双线性插值函数
int bilinear_interp(unsigned char* src, int src_width, int src_height, unsigned char* dst, int dst_width, int dst_height)
{
    int x, y;
    float x_ratio = ((float)(src_width - 1)) / dst_width;
    float y_ratio = ((float)(src_height - 1)) / dst_height;
    float x_diff, y_diff;
    int offset = 0;
    int index;
    int a, b, c, d, pixel;

    for (int i = 0; i < dst_height; i++) {
        for (int j = 0; j < dst_width; j++) {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = (y * src_width + x);

            a = src[index];
            b = src[index + 1];
            c = src[index + src_width];
            d = src[index + src_width + 1];

            pixel = (int)(a * (1 - x_diff) * (1 - y_diff) + b * x_diff * (1 - y_diff) +
                          c * y_diff * (1 - x_diff) + d * x_diff * y_diff);

            dst[offset++] = (unsigned char)pixel;
        }
    }

    return 0;
}

// 主函数
int main(int argc, char* argv[])
{
    // 读取原始图像
    FILE* fp = fopen("lena.raw", "rb");
    if (fp == NULL) {
        printf("Error: could not open input file.\n");
        return -1;
    }

    int src_width = 512;
    int src_height = 512;
    unsigned char* src = (unsigned char*)malloc(src_width * src_height * sizeof(unsigned char));
    fread(src, sizeof(unsigned char), src_width * src_height, fp);
    fclose(fp);

    // 缩放图像
    int dst_width = 256;
    int dst_height = 256;
    unsigned char* dst = (unsigned char*)malloc(dst_width * dst_height * sizeof(unsigned char));
    bilinear_interp(src, src_width, src_height, dst, dst_width, dst_height);

    // 保存结果图像
    fp = fopen("lena_small.raw", "wb");
    if (fp == NULL) {
        printf("Error: could not open output file.\n");
        return -1;
    }

    fwrite(dst, sizeof(unsigned char), dst_width * dst_height, fp);
    fclose(fp);

    free(src);
    free(dst);

    return 0;
}
