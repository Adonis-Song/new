//
// Created by apple on 2022/9/15.
//

#ifndef OPENGL_UTIL_H
#define OPENGL_UTIL_H


namespace util
{
    unsigned char* extractImageFromFile(const char* filePath, int* width, int* height, int* nrChannels);
    void freeImage(unsigned char*);
};


#endif //OPENGL_UTIL_H
