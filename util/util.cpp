//
// Created by apple on 2022/9/15.
//

#include "util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace util {
    unsigned char* extractImageFromFile(const char* filePath, int* width, int* height, int* nrChannels)
    {
        //这里需要将图片 纵向进行颠倒 将纹理和图片对应起来
        //因为对于图片来说，它的左上角是（0， 0），编码的时候，也是从（0， 0）开始编码的
        //所以解码完成的时候，它的（0， 0）也会当成解码出的RGB的（0， 0），
        //但是纹理是把左下角当成（0， 0）的，所以，原图片的左上角，就会变成纹理的左下脚，造成图片和纹理纵向颠倒
        //还不清楚看这个链接
        //https://juejin.cn/post/6854573205378727949
        stbi_set_flip_vertically_on_load(true);
        return stbi_load(filePath, width, height, nrChannels, 0);
    }
    void freeImage(unsigned char* data)
    {
        stbi_image_free(data);
    }
};
