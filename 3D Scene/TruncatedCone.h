//
//  TruncatedCone.h
//  3D Scene
//
//  Created by Yu Chen on 4/10/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_TruncatedCone_h
#define _D_Scene_TruncatedCone_h

#include "Object3D.h"
#include "Drawable.h"

class TruncatedCone : public yc::Object3D, public Drawable
{
public:
    float height;
    float radius_1;
    float radius_2;
    int slices = 24;
    explicit TruncatedCone(float radius_1=0, float radius_2=0, float height=0,
                           yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
    Object3D(position), radius_1(radius_1), radius_2(radius_2), height(height)
    {
        setDrawType(GL_QUAD_STRIP);
    }
    
    std::vector<yc::Vector<float>> getVertices() const
    {
        std::vector<yc::Vector<float>> list;
        float rotateSpeed = 360.0f / slices;
        auto axis = getYVector();
        auto position_1 = getPosition();
        auto position_2 = position_1 + axis.getUnitVector() * height;
        auto unitVector = getXVector().getUnitVector();
        auto vector_1 = unitVector * radius_1;
        auto vector_2 = unitVector * radius_2;
        list.push_back(vector_1 + position_1);
        list.push_back(vector_2 + position_2);
        for (int i = 1; i < slices; i ++) {
            auto v1 = vector_1.rotateAroundAxis(axis, rotateSpeed * i);
            auto v2 = vector_2.rotateAroundAxis(axis, rotateSpeed * i);
            auto p1 = position_1 + v1;
            auto p2 = position_2 + v2;
            list.push_back(p1);
            list.push_back(p2);
        }
        list.push_back(vector_1 + position_1);
        list.push_back(vector_2 + position_2);
        return list;
    }
    
    std::vector<yc::Vector<float>> generateTextureVertices() const
    {
        std::vector<yc::Vector<float>> list;
        auto vertices = getVertices();
        auto texture_coordinate = 1.0f / slices;
        for(int i = 0; i < vertices.size(); i ++)
            list.push_back(yc::Vector<float>(i / 2 * texture_coordinate, i % 2));
        return list;
    }

};

#endif
