//
//  Torch.h
//  3D Scene
//
//  Created by Yu Chen on 4/11/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Torch_h
#define _D_Scene_Torch_h

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "TruncatedCone.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Light.h"

class Torch :
public TruncatedCone,
public Event::Movable,
public Event::Rotatable,
public Light
{
private:
    bool switchOn = false;
    std::vector<std::vector<GLfloat>> colors;
    unsigned int colorIndex = 0;
    sf::Keyboard::Key SWITCH = sf::Keyboard::Space;
    sf::Keyboard::Key CHANGE = sf::Keyboard::G;
    
    void move(const yc::Vector<float>& direction, float distance)
    {
        auto position = getPosition();
        auto velocity = direction.getUnitVector() * distance;
        position += velocity;
        setPosition(position);
    }
public:
    GLdouble slices = 24;
    GLdouble stack = 3.0;
    float forwardSpeed = .1;
    float rotationSpeed = 1;
    
    explicit Torch(float radius_1, float radius_2, float height,
                   const yc::Vector<float>& position,
                   GLenum light):
    TruncatedCone(radius_1, radius_2, height, position), Light(light) {}
    
    ~Torch() {}

    void updateKeyboardEvent()
    {
        updateMoveEvent();
        updateRotateEvent();
    }
    
    void updateSwitchEvent(const sf::Event& event)
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == SWITCH))
        {
            if(!switchOn)
                enable();
            else
                disable();
            switchOn = !switchOn;
        }
    }
    
    void moveLeftRight(int dir) override
    {
        move(yc::Vector<float>::XAXIS,
             forwardSpeed * dir);
    }
    
    void moveUpDown(int dir) override
    {
        move(yc::Vector<float>::YAXIS,
             forwardSpeed * dir);
    }
    
    void moveForwardBack(int dir) override
    {
        move(yc::Vector<float>::ZAXIS,
             -forwardSpeed * dir);
    }

    
    void turnUpDown(int dir) override
    {
        auto xVector = getXVector();
        auto yVector = getYVector();
        auto angle = rotationSpeed * dir;
        yVector = yVector.rotateAroundAxis(xVector, angle);
        setYVector(yVector);
    }
    
    void turnRightLeft(int dir) override
    {
        auto xVector = getXVector();
        auto yVector = getYVector();
        auto zVector = getZVector();
        auto angle = rotationSpeed * dir;
        yVector = yVector.rotateAroundAxis(zVector, -angle);
        xVector = xVector.rotateAroundAxis(zVector, -angle);
        setXYVectors(xVector, yVector);
    }
    
    void addColor(std::vector<GLfloat> color)
    {
        colors.push_back(color);
    }
    
    void changeColor()
    {
        if(colors.size())
        {
            if(colorIndex >= colors.size() - 1)
                colorIndex = 0;
            else
                colorIndex ++;
            setColor(colorIndex);
        }
    }
    
    void setColor(unsigned int index)
    {
        setfv(GL_AMBIENT, colors[index].data());
    }
    
    void updateChangeColorEvent(const sf::Event& event)
    {
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == CHANGE))
        {
            changeColor();
        }
    }
};

#endif
