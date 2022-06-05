/*TODO_LIGH*/
#include "light.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../deserialize-utils.hpp"
#include <iostream>

namespace our
{
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        lightType = data.value("lightType", 0);
        diffuse = data.value("diffuse", diffuse);
        specular = data.value("specular", specular);
        attenuation = data.value("attenuation", attenuation);
        cone_angles = data.value("cone_angles", cone_angles);
        ambient = data.value("ambient", ambient);
    }

}