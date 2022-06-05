#include "world.hpp"
#include "../components/mesh-renderer.hpp"
#include "../asset-loader.hpp"
#include "string"

namespace our
{

    // This will deserialize a json array of entities and add the new entities to the current world
    // If parent pointer is not null, the new entities will be have their parent set to that given pointer
    // If any of the entities has children, this function will be called recursively for these children
    void World::deserialize(const nlohmann::json &data, Entity *parent)
    {
        if (!data.is_array())
            return;
        for (const auto &entityData : data)
        {
            Entity *entity = add();
            entity->parent = parent;
            entity->deserialize(entityData);

            // AhmedKhaled5
            // if (entity->name == "road")
            // {
            //     for (int i = 0; i < 2000; i++)
            //     {
            //         Entity *child = add();
            //         child->parent = parent;
            //         child->deserialize(entityData);
            //         child->localTransform.position.z = i * -1 * 10;
            //     }
            // }
            if (entity->name == "heart")
            {
                // generate random positions for the hearts with a random color
                string colors[] = {"red", "green", "blue", "green", "black", "white", "black", "red", "black", "black", "white", "green"};
                for (int i = 0; i < 100; i++)
                {
                    Entity *child = add();
                    child->parent = parent;
                    child->deserialize(entityData);
                    child->localTransform.position.z = i * -1 * 10;
                    child->localTransform.position.x = rand() % 18 - 9;
                    child->localTransform.position.y = rand() % 6 - 2;
                    child->getComponent<MeshRendererComponent>()->material = AssetLoader<Material>::get(colors[rand() % 12]);
                }
            }
            if (entityData.contains("children"))
                this->deserialize(entityData["children"], entity);
        }
    }

}