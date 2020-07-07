#ifndef __RENDERFBO_H__
#define __RENDERFBO_H__

#include <iostream>

class RenderFBO {
    public:
        RenderFBO(int32_t width, int32_t height, int mode = 0);

        uint32_t getFBO() const;
        uint32_t getTextureColor() const;
        uint32_t getRBO() const;
        uint32_t getDepthMap() const;

        void DeleteFBO();

    private:
        void createFBO(int mode);

    private:
        uint32_t _fbo, _textureColor, _rbo, _depthMap;
        int32_t _width, _height;
};

#endif