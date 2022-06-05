/*TODO_LIGH*/
#pragma once
#include "../ecs/component.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "../shader/shader.hpp"
namespace our
{
    class LightComponent : public Component
    {
    public:
        int lightType;
        glm::vec3 diffuse = {0, 0, 0};
        glm::vec3 specular = {0, 0, 0};
        glm::vec3 attenuation = {0, 0, 0};
        glm::vec2 cone_angles = {0, 0};
        glm::vec3 ambient = {0, 0, 0};

        static std::string getID() { return "Light"; }
        void deserialize(const nlohmann::json &data) override;
    };

}