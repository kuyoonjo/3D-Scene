//
//  Locatable.h
//  3D Scene
//
//  Created by Yu Chen on 4/10/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Object3D_h
#define _D_Scene_Object3D_h

#include "Vector.h"
#include <vector>

namespace yc
{
    class Object3D
    {
    private:
        Vector<float> position;
        Vector<float> xVector;
        Vector<float> yVector;
        
    public:
        explicit Object3D(Vector<float> position=Vector<float>(0, 0, 0),
                           Vector<float> xVector=Vector<float>(1, 0, 0),
                           Vector<float> yVector=Vector<float>(0, 1, 0)):
        position(position), xVector(xVector), yVector(yVector) {}
        
        Vector<float> getPosition() const
        {
            return position;
        }
        
        Vector<float> getXVector() const
        {
            return xVector;
        }
        Vector<float> getYVector() const
        {
            return yVector;
        }
        Vector<float> getZVector() const
        {
            return xVector.crossMultiply(yVector);
        }
        
        void setPosition(const Vector<float>& position)
        {
            this->position = position;
        }
        
        void setXVector(const Vector<float>& xVector)
        {
            this->xVector = xVector;
        }
        void setYVector(const Vector<float>& yVector)
        {
            this->yVector = yVector;
        }
        void setXYVectors(const Vector<float>& xVector, const Vector<float>& yVector)
        {
            setXVector(xVector);
            setYVector(yVector);
        }
        void rotate(const Vector<float>& axisVector, float angle)
        {
            xVector = xVector.rotateAroundAxis(axisVector, angle);
            yVector = yVector.rotateAroundAxis(axisVector, angle);
        }
        
    };
}

#endif
