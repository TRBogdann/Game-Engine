#include "handler.h"


void handleEvents(Event& event, Actor& actor,float deltaTime)
{
    static unsigned char axis = 0;

    if(event.key.triggered && event.key.action == KEY_PRESSED)
    {
        if(event.key.keysym.key == KEY_R)
        {
            axis += 1;
            actor.setRotation({0.0,0.0,0.0});
        }
        if(event.key.keysym.key == KEY_S)
        {
            axis = 0;
        }

    }

    if(axis > 3)
    {
        axis = 0;
    }

    if(axis > 0)
    {
        glm::vec3 rotation = actor.getRotation();
        rotation[axis-1] += ROTATION_CHANGE*deltaTime;
        actor.setRotation(rotation);
    }

}