//
//  Equilateral.h
//  3D Scene
//
//  Created by Yu Chen on 4/8/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Equilateral_h
#define _D_Scene_Equilateral_h

#include "Object3D.h"
#include "Drawable.h"

class Equilateral : public yc::Object3D, public Drawable
{
public:
    float side;
    
    explicit Equilateral(float side=0, yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
    Object3D(position), side(side) {}
    
    virtual std::vector<yc::Vector<float>> getVertices() const = 0;
};

#endif
