#ifndef __RENDERFBO_H__
#define __RENDERFBO_H__

class RenderFBO {
    public:
        RenderFBO(int32_t width, int32_t height);

        uint32_t getFBO() const;
        uint32_t getTextureColor() const;
        uint32_t getRBO() const;

        void DeleteFBO();

    private:
        void createFBO();

    private:
        uint32_t _fbo; uint32_t _textureColor; uint32_t _rbo;
        int32_t _width; int32_t _height;
};

#endif