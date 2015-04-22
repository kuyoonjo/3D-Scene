//
//  RoundLabel.h
//  3D Scene
//
//  Created by Yu Chen on 4/17/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_RoundLabel_h
#define _D_Scene_RoundLabel_h

#include "TruncatedCone.h"

class RoundLabel : public TruncatedCone
{
public:
    float angle;
    explicit RoundLabel(float radius=0, float height=0, float angle=0,
                        yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
    TruncatedCone(radius, radius, height, position), angle(angle) {}
    
    std::vector<yc::Vector<float>> getVertices() const
    {
        std::vector<yc::Vector<float>> list;
        float rotateSpeed = angle / slices;
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
        return list;
    }
};

#endif
