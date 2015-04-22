//
//  ChequeredFloor.h
//  3D Scene
//
//  Created by Yu Chen on 4/11/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_ChequeredFloor_h
#define _D_Scene_ChequeredFloor_h

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Object3D.h"

class ChequeredFloor : public yc::Object3D, public sf::Drawable
{
private:
    yc::Vector<int> numberOfCells;
    yc::Vector<float> sizeOfCell;
    sf::Texture texture1;
    sf::Texture texture2;
    
    void drawCells(bool flag, const sf::Texture& texture) const
    {
        auto position = getPosition();
        sf::Texture::bind(&texture);
        glBegin(GL_QUADS);
        for(int i = 0; i < numberOfCells.x; i ++)
        {
            for(int j = 0; j < numberOfCells.y; j ++)
            {
                if((i + j) % 2 == flag)
                {
                    glTexCoord2f(0.0f,0.0f);
                    glVertex3f(position.x + i * sizeOfCell.x + 0.0f, 0.0f,
                               position.y + j * sizeOfCell.y + 0.0f);
                    glTexCoord2f(1.0f,0.0f);
                    glVertex3f(position.x + i * sizeOfCell.x + 1.0f, 0.0f,
                               position.y + j * sizeOfCell.y + 0.0f);
                    glTexCoord2f(1.0f,1.0f);
                    glVertex3f(position.x + i * sizeOfCell.x + 1.0f, 0.0f,
                               position.y + j * sizeOfCell.y + 1.0f);
                    glTexCoord2f(0.0f,1.0f);
                    glVertex3f(position.x + i * sizeOfCell.x + 0.0f, 0.0f,
                               position.y + j * sizeOfCell.y + 1.0f);
                }
            }
        }
        glEnd();
        sf::Texture::bind(nullptr);
    }
public:
    explicit ChequeredFloor(const yc::Vector<int>& numberOfCells,
                            const yc::Vector<float>& sizeOfCell,
                            const yc::Vector<float>& position,
                            const sf::Texture& texture1,
                            const sf::Texture& texture2):
    numberOfCells(numberOfCells), sizeOfCell(sizeOfCell),
    Object3D(position),
    texture1(texture1), texture2(texture2) {}
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        drawCells(true, texture1);
        drawCells(false, texture2);
        
    }
};

#endif
