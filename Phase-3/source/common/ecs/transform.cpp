#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const
    {
        // DONE: (Req 2)  Write this function

        // ========== // ---- Steps of transformations function ---- // ========== //
        //==// 1-Create identity matrix that will used in (scaling & translation).

        //==// 2- Create scaling matrix using glm::scale
        // glm::scale: it builds a scale 4 * 4 matrix created from 3 scalars.
        // Parameters: (Input matrix multiplied by this scale matrix, Ratio of scaling for each axis)

        //==// 3- Create rotation matrix using glm::yawPitchRoll
        // Creates a 3D 4 * 4 homogeneous rotation matrix from euler angles (Y * X * Z).

        //==// 4- Create scaling matrix using glm::translate
        // glm::translate: it builds a scale 4 * 4 matrix created from 3 scalars.
        // Parameters: (Input matrix multiplied by this translation matrix, Coordinates of a translation vector).

        //==// 5- multiply the matrices by this order (translation, rotation, scale) & return the result which will be the transformation matrix.
        // ========== // ---- End ---- // ========== //

        glm::mat4 identityMatrix(1.0f);
        glm::mat4 scaleMatrix = glm::scale(identityMatrix, scale);
        glm::mat4 rotationMatrix = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        glm::mat4 translationMatrix = glm::translate(identityMatrix, position);
        glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        return transformationMatrix;
    }

    // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json &data)
    {
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale = data.value("scale", scale);
    }

}