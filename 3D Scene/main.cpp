////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "Camera.h"
#include "ChequeredFloor.h"
#include "Cube.h"
#include "Torch.h"
#include "Light.h"
#include "Bottle.h"
#include "ResourcePath.hpp"

int main()
{
    // load texture, font
    sf::Texture rosewood, woodash, colordice, itclogo, bottleColor;
    sf::Font font;
    rosewood.loadFromFile(resourcePath() + "rosewood.jpg");
    woodash.loadFromFile(resourcePath() + "woodash.jpg");
    colordice.loadFromFile(resourcePath() + "ColorDice.png");
    itclogo.loadFromFile(resourcePath() + "ITC_Logo.png");
    bottleColor.loadFromFile(resourcePath() + "bottleColor.png");
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    // Create the main window
    const int width=600, height=600;
    sf::ContextSettings settings;
    settings.depthBits         = 24; // Request a 24-bit depth buffer
    settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
    settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
    sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL", sf::Style::Default, settings);
    App.setFramerateLimit(60);
    
    // Create a clock for measuring time elapsed
    sf::Clock Clock;
    
    // Switch controler camera/torch
    bool switchOn = true;   // true for camera, false for torch
    const sf::Keyboard::Key SWITCH = sf::Keyboard::F;
    
    // Help message
    sf::String helpMessage = "Press F to swith controller Camera/Torch\n";
    helpMessage += "Press G to change Torch color Yellow, Blue, Red\n";
    helpMessage += "Press SPACE to swith Torch On/Off";
    sf::Text help(helpMessage, font, 15);

    // Camara
    Camera camera(1, // forward speed
                  5, // rotation speed
                  yc::Vector<float>(0, 5, 0),      // position
                  yc::Vector<float>(0, 0, -10),    // forward
                  yc::Vector<float>::YAXIS);       // up
    
    // ChequeredFloor
    ChequeredFloor floor(yc::Vector<int>(200, 200),        // number of cells
                         yc::Vector<float>(1, 1),          // size
                         yc::Vector<float>(-100, -100),    // position
                         rosewood,  // texture 1
                         woodash);  // texture 2
    
    // Dice
    Cube dice(3,    // length of side
              yc::Vector<float>(0, 0, -5));    // position
    auto dice_axis_vector = yc::Vector<float>::YAXIS;
    {
        auto xVector = dice.getXVector();
        auto yVector = dice.getYVector();
        auto zv = dice.getZVector();
        auto xv = xVector.rotateAroundAxis(zv, 45);
        xv = xv.rotateAroundAxis(xVector, -45);
        auto yv = yVector.rotateAroundAxis(zv, 45);
        yv = yv.rotateAroundAxis(xVector, -45);
        dice.setXYVectors(xv, yv);
    }
    std::vector<yc::Vector<float>> dice_texture_vertices;
    for(int i = 0; i < 6; i ++)
    {
        dice_texture_vertices.push_back(yc::Vector<float>(i * (1/6.0), i * (1/6.0)));
        dice_texture_vertices.push_back(yc::Vector<float>((i + 1) * (1/6.0), i * (1/6.0)));
        dice_texture_vertices.push_back(yc::Vector<float>((i + 1) * (1/6.0), (i + 1) * (1/6.0)));
        dice_texture_vertices.push_back(yc::Vector<float>(i * (1/6.0), (i + 1) * (1/6.0)));
    }
    dice.setTexture(&colordice, dice_texture_vertices);
    
    // Torch
    Torch torch(.2, .5, 1,      // radius 1, radius 2, height
                yc::Vector<float>(5,5,-5), // position
                GL_LIGHT1); // light
    torch.setYVector(yc::Vector<float>(0, -1, 0));
    torch.addColor({1, 0, 1, 1});
    torch.addColor({1, 1, 0, 1});
    torch.addColor({0, 1, 1, 1});
    torch.setColor(0);
    torch.setfv(GL_DIFFUSE, {.8, .8, .8, .8});
    torch.setfv(GL_SPECULAR, {1, 1, 1, 1});
    torch.setf(GL_SPOT_CUTOFF, 30);
    torch.setf(GL_SPOT_EXPONENT, 5);
    torch.setf(GL_CONSTANT_ATTENUATION, .01);
    torch.setf(GL_LINEAR_ATTENUATION, .01);
    torch.setf(GL_QUADRATIC_ATTENUATION, .01);
    
    // Bottle
    Bottle bottle(yc::Vector<float>(-5, 0, 0),     // position
                  {1, 1, .95, .85, .7, .5, .4, .4},     // radius
                  {4, .2, .2, .2, .2, 2, 1},            // heights
                  .1, 4.2);     // thickness of bottle, height of liquid
    bottle.label = RoundLabel(1, 3, 240, yc::Vector<float>(-5, .6, 0));
    bottle.label.slices = 120;
    bottle.label.setColor({1, 1, 1, .8});
    bottle.label.setTexture(&itclogo, bottle.label.generateTextureVertices());
    bottle.outerTexture = &bottleColor;
    bottle.innerTexture = &bottleColor;
    bottle.init();
    //prepare OpenGL surface for HSR
    glClearDepth(1.f);
    glClearColor(0.01f, 0.01f, 0.2f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glShadeModel(GL_SMOOTH);
    // Lighting
    glEnable(GL_LIGHTING);
    GLfloat globel_ambient[] = {0, 0, 0, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT , globel_ambient);

    Light globalLight(GL_LIGHT0);
    globalLight.setfv(GL_AMBIENT, {.4, .4, .4, 1});
    globalLight.setfv(GL_DIFFUSE, {.1, .1, .1, 1});
    globalLight.setfv(GL_SPECULAR, {1, 1, 1, 1});
    globalLight.setfv(GL_POSITION, {0, -1, 0, 0});
    globalLight.enable();
    

    // Material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat materialSpecular[4] = {1, 1, 1, 1};
    GLfloat materialAmbient[4] = {.1, .1, .1, .1};
    GLfloat materialDiffuse[4] = {.8, .8, .8, .8};
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMateriali(GL_FRONT, GL_SHININESS, 100);
    
    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //set up a 3D Perspective View volume
    gluPerspective(90.f, (float)width/height, 1.f, 50.0f);//fov, aspect, zNear, zFar
    
        // Start game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();
            
            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();
            
            // switch the cotroller camera/torch
            if(Event.type == sf::Event::KeyPressed && Event.key.code == SWITCH)
                switchOn = !switchOn;
            // switch light on/off
            torch.updateSwitchEvent(Event);
            // change torch color
            torch.updateChangeColorEvent(Event);
            
        }
        
        if(switchOn)
            camera.updateKeyboardEvent();   //update the camera
        else
            torch.updateKeyboardEvent();    // update the torch
        
        
        //Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Apply some transformations
        //initialise the worldview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        //get the viewing transform from the camera
        camera.ViewingTransform();
        
        // Draw Chequred Floor
        App.draw(floor);
        
        
        // Draw Dice
        dice.rotate(dice_axis_vector, 1);
        App.draw(dice);
        
        // Draw Torch
        App.draw(torch);
        auto position = torch.getPosition();
        auto yVector = torch.getYVector();
        torch.setfv(GL_POSITION, {position.x, position.y, position.z, 1});
        torch.setfv(GL_SPOT_DIRECTION, {yVector.x, yVector.y, yVector.z});
        
        // Draw Bottle
        App.draw(bottle);
        // Help message
        App.pushGLStates();
        App.draw(help);
        App.popGLStates();
        // Finally, display rendered frame on screen
        
             App.display();
    }
    
    return EXIT_SUCCESS; 
}