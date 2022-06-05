#pragma once

#include "../ecs/world.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
   

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic. 
    // For more information, see "common/components/movement.hpp"
    class MovementSystem {

        Application* app; // The application in which the state runs
    public:

        void enter(Application* app){
            this->app = app;
        }

        // This should be called every frame to update all entities containing a MovementComponent. 
        void update(World* world, float deltaTime) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                // Get the movement component if it exists
                MovementComponent* movement = entity->getComponent<MovementComponent>();
                // If the movement component exists
                if(movement){
                    // Ammar: Normal movement objects if not car
                    if (entity->name != "car")
                    {
                        entity->localTransform.position += deltaTime * movement->linearVelocity;
                        entity->localTransform.rotation += deltaTime * movement->angularVelocity;
                    }

                    // Ammar: if the object is car it only rotates 45 degrees left and right 
                    else
                    {
                        if(app->getKeyboard().isPressed(GLFW_KEY_LEFT))
                        {

                            entity->localTransform.rotation[1]=(180+45)*(22/7.0)/180.0;
                            
                        }
                        else if (app->getKeyboard().isPressed(GLFW_KEY_RIGHT))
                        {

                            entity->localTransform.rotation[1]=(180-45)*(22/7.0)/180.0;

                        }
                        else {
                            entity->localTransform.rotation[1]=22/7.0;
                        }
                    }

                    
                }
            }
        }

    };

}
