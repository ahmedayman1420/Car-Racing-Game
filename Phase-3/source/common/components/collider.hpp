// NOTE: HazemAbdo1
// Adding collider component so that to distinguish between the cars and hearts and other objects
#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{
    // This component denotes that the ColliderSystem
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/collision.hpp"
    class ColliderComponent : public Component
    {
    public:
        glm::vec3 position; // Each frame, the entity should have: position += length
        float length;       // Each frame, the entity should rotate as follows: length

        // The ID of this component type is "Collider"
        static std::string getID() { return "Collider"; }

        void deserialize(const nlohmann::json &data) override;
    };

}