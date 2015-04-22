//
//  Bottle.h
//  3D Scene
//
//  Created by Yu Chen on 4/11/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Bottle_h
#define _D_Scene_Bottle_h

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Object3D.h"
#include "TruncatedCone.h"
#include "Circle.h"
#include "RoundLabel.h"

class Bottle : public yc::Object3D, public sf::Drawable
{
private:
    std::vector<TruncatedCone> outers;
    std::vector<TruncatedCone> inners;
    std::vector<TruncatedCone> liquids;
    TruncatedCone bottom;
    Circle top;
    
public:
    RoundLabel label;
    std::vector<float> radius;
    std::vector<float> heights;
    float thickness;
    float liquid;
    sf::Texture* labelTexture = nullptr;
    std::vector<float> labelCorlor;
    sf::Texture* innerTexture = nullptr;
    std::vector<float> innerCorlor = {1, 1, 1, 0.1};
    sf::Texture* outerTexture = nullptr;
    std::vector<float> outerCorlor = {1, 1, 1, 0.6};
    sf::Texture* liquidTexture = nullptr;
    std::vector<float> liquidCorlor = {1, 0, 0, 0.7};
    
    explicit Bottle(const yc::Vector<float>& position,
                    const std::vector<float>& radius,
                    const std::vector<float>& heights,
                    float thickness,
                    float liquid):
    Object3D(position), radius(radius), heights(heights), thickness(thickness), liquid(liquid) {}
    
    void init()
    {
        auto position = getPosition();
        bottom = TruncatedCone(0, radius[0] - thickness, thickness * 2, position);
        bottom.setColor(liquidCorlor);
        bottom.setTexture(liquidTexture, bottom.generateTextureVertices());
        float height = 0;
        bool filled = false;
        int i;
        for(i = 0; i < radius.size() - 1; i ++)
        {
            auto heightNext = heights[i] + height;
            
            // outer
            TruncatedCone outer(radius[i], radius[i + 1], heights[i],
                                yc::Vector<float>(0, height, 0) + position);
            outer.setColor(outerCorlor);
            outer.setTexture(outerTexture, outer.generateTextureVertices());
            outers.push_back(outer);
            
            // inner
            TruncatedCone inner(radius[i] - thickness,
                                radius[i + 1] - thickness,
                                heights[i],
                                yc::Vector<float>(0, height, 0) + position);
            inner.setColor(innerCorlor);
            inner.setTexture(innerTexture, inner.generateTextureVertices());
            inners.push_back(inner);
            
            // liquid
            if(!filled)
            {
                if(heightNext > liquid)
                {
                    float heightTemp = liquid - height;
                    float r = (radius[i + 1] - radius[i]) * heights[i] / heightTemp;
                    float radiusTemp = radius[i] + r;
                    TruncatedCone liq(radius[i] - thickness,
                                      radiusTemp - thickness,
                                      heightTemp,
                                      yc::Vector<float>(0, height, 0)  + position);
                    liq.setColor(liquidCorlor);
                    liq.setTexture(liquidTexture, liq.generateTextureVertices());
                    liquids.push_back(liq);
                    
                    top.setDrawType(GL_TRIANGLE_FAN);
                    top.setRadius(radiusTemp - thickness);
                    top.setPosition(yc::Vector<float>(0, height + heightTemp, 0) + position);
                    top.setColor(liquidCorlor);
                    filled = true;
                }
                else
                {
                    TruncatedCone liq(radius[i] - thickness,
                                      radius[i + 1] - thickness,
                                      heights[i],
                                      yc::Vector<float>(0, height, 0) + position);
                    liq.setColor(liquidCorlor);
                    liq.setTexture(liquidTexture, liq.generateTextureVertices());
                    liquids.push_back(liq);
                }
            }
            
            height = heightNext;
        }
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
        
        // liquid
        target.draw(bottom);
        std::for_each(liquids.begin(), liquids.end(), [&](const TruncatedCone& tc)
                      {
                          target.draw(tc);
                      });
        target.draw(top);
        // label
        target.draw(label);
        // bottle
        std::for_each(inners.begin(), inners.end(), [&](const TruncatedCone& tc)
                      {
                          target.draw(tc);
                      });
        std::for_each(outers.begin(), outers.end(), [&](const TruncatedCone& tc)
                      {
                          target.draw(tc);
                      });

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
        glDisable(GL_BLEND);
    }
};

#endif
