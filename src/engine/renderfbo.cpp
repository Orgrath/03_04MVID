#include "engine/renderfbo.hpp"

#include <glad/glad.h>

RenderFBO::RenderFBO(int32_t width, int32_t height, int mode)
    : _width(width), _height(height){

    createFBO(mode);
}

void RenderFBO::createFBO(int mode) {
    uint32_t fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    _fbo = fbo;
    //_dirFBO = &fbo;

    switch (mode){
    case 0 :
        uint32_t textureColor;
        glGenTextures(1, &textureColor);
        glBindTexture(GL_TEXTURE_2D, textureColor);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);
        _textureColor = textureColor;
        //_dirTextureColor = &textureColor;

        uint32_t rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
        _rbo = rbo; 
        //_dirRBO = &rbo;

        break;

    case 1 : 
        uint32_t depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        _depthMap = depthMap;

        break;
    }
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer Incomplete" << std::endl;
    }
}

void RenderFBO::DeleteFBO() {
    glDeleteFramebuffers(1, &_fbo);
    glDeleteTextures(1, &_textureColor);
    glDeleteTextures(1, &_depthMap);
    glDeleteRenderbuffers(1, &_rbo);
}

uint32_t RenderFBO::getFBO() const {
    return _fbo;
}

uint32_t RenderFBO::getTextureColor() const{
    return _textureColor;
}

uint32_t RenderFBO::getRBO() const{
    return _rbo;
}

uint32_t RenderFBO::getDepthMap() const {
    return _depthMap;
}