//
//  Movable.h
//  3D Scene
//
//  Created by Yu Chen on 4/11/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Movable_h
#define _D_Scene_Movable_h

#include <SFML/Graphics.hpp>

namespace Event
{
    class Movable
    {
    public:
        sf::Keyboard::Key LEFT = sf::Keyboard::A;
        sf::Keyboard::Key RIGHT = sf::Keyboard::D;
        sf::Keyboard::Key FORWARD = sf::Keyboard::W;
        sf::Keyboard::Key BACK = sf::Keyboard::S;
        sf::Keyboard::Key UP = sf::Keyboard::Q;
        sf::Keyboard::Key DOWN = sf::Keyboard::E;
        
        virtual void moveLeftRight(int dir) = 0;
        virtual void moveUpDown(int dir) = 0;
        virtual void moveForwardBack(int dir) = 0;
        
        void updateMoveEvent()
        {
            if (sf::Keyboard::isKeyPressed(LEFT))
                moveLeftRight(-1);
            if (sf::Keyboard::isKeyPressed(RIGHT))
                moveLeftRight(1);
            
            if (sf::Keyboard::isKeyPressed(FORWARD))
                moveForwardBack(1);
            if (sf::Keyboard::isKeyPressed(BACK))
                    moveForwardBack(-1);
                
            if (sf::Keyboard::isKeyPressed(UP))
                    moveUpDown(1);
            if (sf::Keyboard::isKeyPressed(DOWN))
                    moveUpDown(-1);
            
        }
    };
}

#endif
