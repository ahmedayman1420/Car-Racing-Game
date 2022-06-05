// NOTE: HazemAbdo3
#pragma once
#include "../ecs/world.hpp"
#include "../components/collider.hpp"
#include "../components/movement.hpp"
#include "../components/mesh-renderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>
namespace our
{

    class CollisionSystem
    {
        std::vector<ColliderComponent *> cars, hearts;
        std::vector<MeshRendererComponent *> healthBar;

    public:
        // NOTE: HazemAbdo3.1 function checkCollision()
        // return pair of two flags
        // first flag indicates whether the collision happened [1-->collision happened, 0-->no collision]
        // second flag indicates whether the collision happened with a heart that will increase the health
        // or a heart that will decrease the health [1-->positive heart, 0-->negative heart]
        pair<bool, bool> checkCollision(ColliderComponent *heartComponent, ColliderComponent *carComponent)
        {
            pair<bool, bool> result = make_pair(false, false);
            auto car = carComponent->getOwner();
            auto heart = heartComponent->getOwner();
            glm::vec3 carCenter = carComponent->position + glm::vec3(car->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 heartCenter = heartComponent->position + glm::vec3(heart->getLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            glm::vec3 heartLengths = glm::vec3(heartComponent->length, heartComponent->length, heartComponent->length) * heart->localTransform.scale;
            glm::vec3 difference = carCenter - heartCenter;
            // min(max(x, minVal), maxVal)
            glm::vec3 clampedDifference = glm::clamp(difference, heartLengths * glm::vec3(-1.0f, -1.0f, -1.0f), heartLengths);
            glm::vec3 heartPoint = heartCenter + clampedDifference;
            difference = heartPoint - carCenter;
            float carRadius = carComponent->length * glm::length(car->localTransform.scale);
            result.first = glm::length(difference) < carRadius;
            // the only heart that will increase the health is the green heart
            if (heart->getComponent<MeshRendererComponent>()->material == AssetLoader<Material>::get("green"))
            {
                result.second = true;
            }
            else
            {
                result.second = false;
            }
            return result;
        }
        // NOTE: HazemAbdo3.2 function update()
        int update(World *world, float deltaTime)
        {
            // cout << "update collision" << endl;
            // cout << cars.size() << " " << hearts.size() << endl;
            hearts.clear();
            cars.clear();
            healthBar.clear();
            for (const auto &entity : world->getEntities())
            {
                if (entity->name == "heart")
                {
                    // cout << "heart" << endl;
                    auto heart = entity->getComponent<ColliderComponent>();
                    hearts.push_back(heart);
                }
                else if (entity->name == "car")
                {
                    auto car = entity->getComponent<ColliderComponent>();
                    cars.push_back(car);
                }
                else if (entity->name == "healthbar")
                {
                    auto healthBar = entity->getComponent<MeshRendererComponent>();
                    this->healthBar.push_back(healthBar);
                }
            }
            // cout << "BEFOR SORT" << endl;
            healthBar = sortHealthBars(healthBar);
            // cout << "AFTER SORT" << endl;
            // cout << cars.size() << " " << hearts.size() << endl;
            // cout << "before for" << endl;
            for (auto heart : hearts)
            {
                // if collision happened with a heart
                if (checkCollision(heart, cars[0]).first)
                {

                    if (checkCollision(heart, cars[0]).second && healthBar.size() > 0)
                    {
                        // add last health bar after collision with special color heart (green)
                        Entity *addedHealthBar = world->add();
                        addedHealthBar->parent = healthBar[healthBar.size() - 1]->getOwner()->parent;
                        addedHealthBar->name = "healthbar";
                        addedHealthBar->addComponent<MeshRendererComponent>();
                        addedHealthBar->getComponent<MeshRendererComponent>()->mesh = healthBar[healthBar.size() - 1]->mesh;
                        addedHealthBar->getComponent<MeshRendererComponent>()->material = healthBar[healthBar.size() - 1]->material;
                        addedHealthBar->localTransform = healthBar[healthBar.size() - 1]->getOwner()->localTransform;
                        addedHealthBar->localTransform.position.x = healthBar[healthBar.size() - 1]->getOwner()->localTransform.position.x + 0.15;
                        //   remove heart after collision
                        world->markForRemoval(heart->getOwner());
                        world->deleteMarkedEntities();
                    }
                    else
                    {
                        //   remove heart after collision
                        world->markForRemoval(heart->getOwner());
                        world->deleteMarkedEntities();
                        // remove last health bar after collision
                        world->markForRemoval(healthBar[healthBar.size() - 1]->getOwner());
                        world->deleteMarkedEntities();
                        healthBar.pop_back();
                    }
                }
            }

            // world->deleteMarkedEntities();
            return healthBar.size();
        }
        // sort based on x of position
        std::vector<MeshRendererComponent *> sortHealthBars(std::vector<MeshRendererComponent *> vec)
        {

            std::sort(vec.begin(), vec.end(), [](MeshRendererComponent *a, MeshRendererComponent *b)
                      { return a->getOwner()->localTransform.position.x < b->getOwner()->localTransform.position.x; });
            return vec;
        }
    };
}