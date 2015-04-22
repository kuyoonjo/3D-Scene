//
//  Light.h
//  3D Scene
//
//  Created by Yu Chen on 4/11/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#include <SFML/OpenGL.hpp>

#ifndef _D_Scene_Light_h
#define _D_Scene_Light_h



class Light
{
public:
    GLenum source;
    
    explicit Light(GLenum source)
    {
        this->source = source;
    }
    
    void setfv(GLenum pname, const GLfloat *params)
    {
        glLightfv(source, pname, params);
    }
    
    void setfv(GLenum pname, const std::initializer_list<GLfloat>& list)
    {
        std::vector<GLfloat> vector = list;
        setfv(pname, &vector[0]);
    }
    
    void setf(GLenum pname, GLfloat param)
    {
        glLightf(source, pname, param);
    }
    
    void enable()
    {
        glEnable(source);
    }
    
    void disable()
    {
        glDisable(source);
    }
};

#endif
