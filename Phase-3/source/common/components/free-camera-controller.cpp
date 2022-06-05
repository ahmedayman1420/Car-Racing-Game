#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads sensitivities & speedupFactor from the given json object
    void FreeCameraControllerComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        rotationSensitivity = data.value("rotationSensitivity", rotationSensitivity);
        fovSensitivity = data.value("fovSensitivity", fovSensitivity);
        positionSensitivity = data.value("positionSensitivity", positionSensitivity);
        speedupFactor = data.value("speedupFactor", speedupFactor);
        linearVelocity = data.value("linearVelocity", linearVelocity);
        angularVelocity = glm::radians(data.value("angularVelocity", angularVelocity));

        speedSensitivity = data.value("speedSensitivity", speedSensitivity);
        brakeSensitivity = data.value("brakeSensitivity", brakeSensitivity);
        maxSpeed=data.value("maxSpeed", maxSpeed);
        frictionSensitivity =data.value("frictionSensitivity", frictionSensitivity);

        rotationSensitivity = data.value("rotationSensitivity", rotationSensitivity);
        maxRotationAngle = data.value("maxRotationAngle", maxRotationAngle);

        jumpSpeed = data.value("jumpSpeed", jumpSpeed);
        jumpSensitivity = data.value("jumpSensitivity", jumpSensitivity);

        originalY = data.value("originalY", originalY);
    }
}