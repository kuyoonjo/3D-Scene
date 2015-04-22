//
//  Square.h
//  3D Scene
//
//  Created by Yu Chen on 4/8/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Square_h
#define _D_Scene_Square_h

#include "Equilateral.h"

class Square : public Equilateral
{
public:
    explicit Square(float side=0, yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
        Equilateral(side, position) {}
    
    std::vector<yc::Vector<float>> getVertices() const override {
        std::vector<yc::Vector<float>> list;
        list.push_back(getPosition());
        list.push_back(getPosition() + getXVector().getUnitVector() * side);
        list.push_back(getPosition() + getXVector().getUnitVector() * side + getYVector().getUnitVector() * side);
        list.push_back(getPosition() + getYVector().getUnitVector() * side);
        return list;
    }
};

#endif
