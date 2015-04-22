//
//  Drawable.h
//  3D Scene
//
//  Created by Yu Chen on 4/17/15.
//  Copyright (c) 2015 Yu Chen. All rights reserved.
//

#ifndef _D_Scene_Drawable_h
#define _D_Scene_Drawable_h

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Drawable : public sf::Drawable
{
private:
    GLenum type;
    std::vector<float> color={1, 1, 1, 1};
    sf::Texture* texture = nullptr;
    std::vector<yc::Vector<float>> texture_vertices;
public:
    explicit Drawable(GLenum type=GL_QUAD_STRIP): type(type) {}
    void setDrawType(GLenum type)
    {
        this->type = type;
    }
    void setColor(const std::vector<float>& color)
    {
        this->color = color;
    }
    void setTexture(sf::Texture* texture,
                    const std::vector<yc::Vector<float>>& texture_vertices)
    {
        this->texture = texture;
        this->texture_vertices = texture_vertices;
    }
    virtual std::vector<yc::Vector<float>> getVertices() const = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if(texture)
        {
            auto vertices = getVertices();
            sf::Texture::bind(texture);
            glBegin(type);
            glColor4f(color[0], color[1], color[2], color[3]);
            for(int i = 0; i < vertices.size(); i ++)
            {
                glNormal3f(vertices[i].x, vertices[i].y, vertices[i].z);
                glTexCoord2f(texture_vertices[i].x, texture_vertices[i].y);
                glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
            }
            glEnd();
            sf::Texture::bind(nullptr);
        }
        else
        {
            auto vertices = getVertices();
            glBegin(type);
            glColor4f(color[0], color[1], color[2], color[3]);
            for(int i = 0; i < vertices.size(); i ++)
            {
                glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
            }
            glEnd();
        }
    }
};

#endif
