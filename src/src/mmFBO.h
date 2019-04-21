////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2018-2019 Michele Morrone
//  All rights reserved.
//
//  mailto:me@michelemorrone.eu
//  mailto:brutpitt@gmail.com
//  
//  https://github.com/BrutPitt
//
//  https://michelemorrone.eu
//  https://BrutPitt.com
//
//  This software is distributed under the terms of the BSD 2-Clause license
//  
////////////////////////////////////////////////////////////////////////////////
#ifndef _mm_FBO_
#define _mm_FBO_

#include "glm/vec2.hpp"
#include <vector>

//#include "GPU.h"

using namespace glm;



class mmFBO 
{
public:
    enum secondaryBufferType { depthBuffer, stencilBuffer, depthStencilBuffer };
    enum depthBufferType { depthTexture, depthBuiltIn };
    
    mmFBO()  { resetData(); }
    ~mmFBO() { deleteFBO(); }

    void buildFBO(int num, int sizeX, int sizeY, GLenum precision, int levelAA=0);
    void reBuildFBO(int num, int sizeX, int sizeY, GLenum precision, int levelAA=0);
    void reSizeFBO(int sizeX, int sizeY);
    void deleteFBO();

    GLuint getFB(int num)  { return num<m_NumFB ? m_fb[num] : -1; }
    GLuint getTex(int num) { return num<m_NumFB ? m_tex[num] : -1; }
    GLuint getRB(int num)  { return num<m_NumFB ? m_rb[num] : -1; }
    GLuint getDepth(int num) { return num<m_NumFB ? m_depth[num] : -1; }
    GLuint getTexMultiFB(int num) { return num<numMultiDraw ? multiDrawFB[num] : -1; }

    void attachDB(bool builtIN)    { attachSecondaryBuffer(builtIN, depthBuffer); }
    void attachSB(bool builtIN)    { attachSecondaryBuffer(builtIN, stencilBuffer); }
    void attachDB_SB(bool builtIN) { attachSecondaryBuffer(builtIN, depthStencilBuffer); };

    int getSizeX() { return m_sizeX; }
    int getSizeY() { return m_sizeY; }

    void defineTexture(GLuint iTex, GLuint intFormat, GLuint format = GL_RGBA, GLuint type = GL_FLOAT);
    void attachMultiFB(int num);

// static members
    static void onReshape() { onReshape(mmFBO::m_winSize.x, mmFBO::m_winSize.y); }
    static void onReshape(int w, int h);
    static void Init(int w, int h) { mmFBO::onReshape(w, h); }

    static ivec2 m_winSize;
    static vec2 m_winAspect;     
    static vec2 m_winInvSize;
    static float m_reduction;

static GLuint vboVertexBufferID;
static GLuint vboTexBufferID;
static GLuint vbaID;


private:
    void initFB(GLuint fbuff, GLuint iText);
    void attachSecondaryBuffer(bool builtIN, secondaryBufferType type); //depthBuffer + Stencil
    void CheckFramebufferStatus(GLenum status);
    void resetData();

    int m_NumFB, aaLevel = 0;
    bool isBuilded;
    bool haveRB = false;
    bool isBuiltIn = true;


    GLuint glPrecision;

    GLuint *m_fb    = nullptr;
    GLuint *m_rb    = nullptr;
    GLuint *m_tex   = nullptr;
    GLuint *m_depth = nullptr;
    GLuint *multiDrawFB = nullptr;
    secondaryBufferType dsBufferType = depthBuffer;
    int numMultiDraw = 0;

    int m_sizeX, m_sizeY;
};


#endif