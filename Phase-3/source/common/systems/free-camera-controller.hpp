#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/free-camera-controller.hpp"
// #include "../components/collider.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>


namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class FreeCameraControllerSystem
    {
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked
        bool isJump = false;

    public:
        // When a state enters, it should call this function and give it the pointer to the application

        void enter(Application *app)
        {
            this->app = app;
        }
        // bool checkCollision(MeshRendererComponent *car, MeshRendererComponent *heart)
        // {
        //     Entity *entity = car->getOwner();
        //     entity -
        //         glm::vec3 carPos = entity->localTransform.position + glm::vec3(entity->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //     entity = heart->getOwner();
        //     glm::vec3 heartPos = entity->localTransform.position + glm::vec3(entity->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //     bool collisionX = carPos.x + 1 >= heartPos.x &&
        //                       heartPos.x >= carPos.x;
        //     // cout << "x" << endl;  
        //     // cout << carPos.x + 1.3 << " " << heartPos.x << endl;
        //     // cout << "y" << endl;
        //     // cout << carPos.y << " " << heartPos.y << endl;
        //     // cout << "z" << endl;
        //     // cout << carPos.z + 3 << " " << heartPos.z << endl;
        //     bool collisionZ = carPos.z + 3.3 >= heartPos.z &&
        //                       heartPos.z >= carPos.z;
        //     return collisionX && collisionZ;
        // }
        // // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world, float deltaTime)
        {
            // First of all, we search for an entity containing both a CameraComponent and a FreeCameraControllerComponent
            // As soon as we find one, we break
            CameraComponent *camera = nullptr;
            FreeCameraControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<FreeCameraControllerComponent>();
                if (camera && controller)
                    break;
            }
            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!(camera && controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *entity = camera->getOwner();
            //----------------------------------------------------------------------------------
            //----------------------------------------------------------------------------------
            //----------------------------------------------------------------------------------
         


            // AMMAR : UP KEY Increases the speed until it reaches max speed
            if (app->getKeyboard().isPressed(GLFW_KEY_UP))
            {
                controller->linearVelocity += (glm::vec3(0, 0, controller->speedSensitivity));
                if (controller->linearVelocity[2] < controller->maxSpeed)
                {
                    controller->linearVelocity[2] = controller->maxSpeed;
                }
            }
            // AMMAR : Down KEY decreases the speed until it reaches 0 with brake sensitivity
            else if (app->getKeyboard().isPressed(GLFW_KEY_DOWN)) 
            {
                controller->linearVelocity += (glm::vec3(0, 0, controller->brakeSensitivity));
                if (controller->linearVelocity[2] > 0)
                    controller->linearVelocity[2] = 0;
            }

            // AMMAR : If speed button is not pressed decrease speed with friction sensitivity until zero 
            else if (controller->linearVelocity[2] != 0)
            {
                controller->linearVelocity += (glm::vec3(0, 0, controller->frictionSensitivity));
                if (controller->linearVelocity[2] > 0)
                {
                    controller->linearVelocity[2] = 0;
                }
            }

            // AMMAR : left button moves the car left with the speed of the car 
            if (app->getKeyboard().isPressed(GLFW_KEY_LEFT))
            {
                controller->linearVelocity[0] = controller->linearVelocity[2];
            }

            // AMMAR : right button moves the car right with the speed of the car 
            else if (app->getKeyboard().isPressed(GLFW_KEY_RIGHT))
            {
                controller->linearVelocity[0] = -1 * controller->linearVelocity[2];
            }

            // AMMAR : return x speed to zero if no left or right pressed 
            else
            {
                controller->linearVelocity[0] = 0;
            }

            // AMMAR :Space Button triggers jump if it is not currently jumping and starts it with giving Y a starting speed
            if (app->getKeyboard().isPressed(GLFW_KEY_SPACE))
            {
                if (!isJump)
                {
                    controller->linearVelocity[1] = controller->jumpSpeed;
                    isJump = true;
                }
            }

            // AMMAR :During jump state the Y speed keeps decreasing with jump sensitivity until it reaches negative jump speed and makes sure the car return to its original Y
            if (isJump)
            {
                controller->linearVelocity[1] += (-1 * controller->jumpSensitivity);
            }

            entity->localTransform.position += deltaTime * controller->linearVelocity;
            if (isJump && entity->localTransform.position[1] <= controller->originalY)
            {
                controller->linearVelocity[1] = 0;
                entity->localTransform.position[1] = controller->originalY;
                isJump = false;
            }


            ///Handling Road width
            if (entity->localTransform.position.x < -9)
            {
                entity->localTransform.position.x = -9;
            }
            if (entity->localTransform.position.x > 9)
            {
                entity->localTransform.position.x = 9;
            }
        }

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit()
        {
            if (mouse_locked)
            {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }
    };
}
