//
//  Camera.h
//  3D Scene
//
//  Created by Yu Chen on 3/4/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Camera_h
#define _D_Scene_Camera_h

#include <SFML/Graphics.hpp>
#include "Object3D.h"
#include "Movable.h"
#include "Rotatable.h"

class Camera :
public yc::Object3D,
public Event::Movable,
public Event::Rotatable
{
public:
    float forwardSpeed;
    float rotationSpeed;
    
    const float MaxSightAngle = 170;
    const float MinSightAngle = 10;
    const float Maxheight = 30;
    const float Minheight = 5;
    const float LimitForward = -98;
    const float LimitBack = 98;
    const float LimitLeft = -98;
    const float LimitRight = 98;
    
    explicit Camera(float forwardSpeed=1, float rotationSpeed=1):
    forwardSpeed(forwardSpeed),rotationSpeed(rotationSpeed), Object3D() {}
    
    explicit Camera(float forwardSpeed, float rotationSpeed,
                    const yc::Vector<float>& position,
                    const yc::Vector<float>& forward,
                    const yc::Vector<float>& up):
    forwardSpeed(forwardSpeed),rotationSpeed(rotationSpeed),
    Object3D(position, forward, up) {}
    
    void updateKeyboardEvent()
    {
        updateMoveEvent();
        updateRotateEvent();
    }
    
    void move(yc::Vector<float>& position, yc::Vector<float>& forward)
    {
        auto oldPosition = position;
        if (position.x < LimitLeft) position.x = LimitLeft;
        if (position.x > LimitRight) position.x = LimitRight;
        if (position.y < Minheight) position.y = Minheight;
        if (position.y > Maxheight) position.y = Maxheight;
        if (position.z < LimitForward) position.z = LimitForward;
        if (position.z > LimitBack) position.z = LimitBack;
        forward = forward + position - oldPosition;
        setPosition(position);
        setXVector(forward);
    }
    
    void moveLeftRight(int dir) override
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        auto distance = forwardSpeed * dir;
        auto direction = (forward - position).crossMultiply(up);
        auto velocity = direction.getUnitVector() * distance;
        forward += velocity;
        position += velocity;
        move(position, forward);
    }
    
    void moveUpDown(int dir) override
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        auto distance = forwardSpeed * dir;
        auto velocity = up * distance;
        forward += velocity;
        position += velocity;
        move(position, forward);
    }
    
    void moveForwardBack(int dir) override
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        auto distance = forwardSpeed * dir;
        auto direction = up.crossMultiply((forward - position).crossMultiply(up));
        auto velocity = direction.getUnitVector() * distance;
        forward += velocity;
        position += velocity;
        move(position, forward);
    }
    
    void turnRightLeft(int dir) override
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        auto angle = rotationSpeed * dir;
        auto direction = forward - position;
        auto newDirection = direction.rotateAroundAxis(up, -angle);
        forward = position + newDirection;
        setXVector(forward);
    }
    
    void turnUpDown(int dir) override
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        auto angle = rotationSpeed * dir;
        auto direction = forward - position;
        auto axisVector = direction.crossMultiply(up);
        auto newDirection = direction.rotateAroundAxis(axisVector, angle);
        auto newForward = position + newDirection;
        auto newAngle = up.getAngleBetween(newDirection);
        if(newAngle >= MinSightAngle && newAngle <= MaxSightAngle)
            setXVector(newForward);
    }
    
    void ViewingTransform()
    {
        auto forward = getXVector();
        auto up = getYVector();
        auto position = getPosition();
        gluLookAt(position.x, position.y, position.z,// camera position
                  forward.x, forward.y, forward.z, //look at this point //TODO: BUG here!! what is it ??
                  up.x, up.y, up.z); //camera up
    }
    
};

#endif
