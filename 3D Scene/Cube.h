//
//  Cube.h
//  3D Scene
//
//  Created by Yu Chen on 4/8/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Cube_h
#define _D_Scene_Cube_h

#include "Equilateral.h"
#include "Square.h"

class Cube : public Equilateral
{
public:
    explicit Cube(float side=0, yc::Vector<float> position=yc::Vector<float>(0, 0, 0)):
    Equilateral(side, position)
    {
        setDrawType(GL_QUADS);
    }
    
    std::vector<Square> getFaces() const
    {
        std::vector<Square> list;
        auto position = getPosition();
        auto xVector = getXVector();
        auto yVector = getYVector();
        auto zVector = getZVector();
        Square bottom(side, position);
        bottom.setXYVectors(xVector, yVector);
        Square top(side, position + zVector.getUnitVector() * side);
        top.setXYVectors(yVector, xVector);
        Square left(side, position);
        left.setXYVectors(yVector, zVector);
        Square right(side, position + xVector.getUnitVector() * side);
        right.setXYVectors(zVector, yVector);
        Square front(side, position);
        front.setXYVectors(zVector, xVector);
        Square back(side, position + yVector.getUnitVector() * side);
        back.setXYVectors(xVector, zVector);
        list.push_back(bottom);
        list.push_back(left);
        list.push_back(front);
        list.push_back(back);
        list.push_back(right);
        list.push_back(top);
        return list;
    }
    
    std::vector<yc::Vector<float>> getVertices() const override {
        std::vector<yc::Vector<float>> list;
        for(auto face: getFaces())
        {
            for(auto vertice: face.getVertices())
            {
                list.push_back(vertice);
            }
        }
        return list;
    }
    
};

#endif
