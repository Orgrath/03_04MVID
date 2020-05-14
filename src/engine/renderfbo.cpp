#include "engine/renderfbo.hpp"

#include <glad/glad.h>

RenderFBO::RenderFBO(int32_t width, int32_t height)
    : _width(width), _height(height){

    createFBO();
}

void RenderFBO::createFBO() {
    uint32_t fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    _fbo = fbo;
    //_dirFBO = &fbo;

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

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer Incomplete" << std::endl;
    }
}

void RenderFBO::DeleteFBO() {
    glDeleteFramebuffers(1, &_fbo);
    glDeleteTextures(1, &_textureColor);
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