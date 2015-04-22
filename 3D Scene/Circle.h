//
//  Circle.h
//  3D Scene
//
//  Created by Yu Chen on 4/17/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Circle_h
#define _D_Scene_Circle_h

#include "Equilateral.h"

class Circle : public Equilateral
{
public:
    int slices = 24;
    explicit Circle(float radius=0, yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
    Equilateral(radius, position)
    {
        setDrawType(GL_TRIANGLE_FAN);
    }
    
    float getRadius() const {
        return side;
    }
    
    void setRadius(float radius)
    {
        side = radius;
    }
    
    std::vector<yc::Vector<float>> getVertices() const override {
        std::vector<yc::Vector<float>> list;
        float rotateSpeed = 360.0f / slices;
        auto axis = getYVector();
        auto vector = getXVector().getUnitVector() * getRadius();
        auto position = getPosition();
        list.push_back(position);
        list.push_back(vector + position);
        for (int i = 1; i < slices; i ++)
            list.push_back(position + vector.rotateAroundAxis(axis, rotateSpeed * i));
        list.push_back(vector + position);
        return list;
    }
};

#endif
