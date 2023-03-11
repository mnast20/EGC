#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Cam
    {
     public:
        Cam(float distance)
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            direction   = glm::vec3(0, 0, 0);
            center = glm::vec3(0, 0, 0);
            distanceToTarget = distance;
        }

        Cam(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~Cam()
        { }

        // Update Cam
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            this->center = center;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);
            direction = glm::vec3(0, 0, 0);
        }

        void restoreCamera(const glm::vec3& prev_position, const glm::vec3& prev_forward,
                            const glm::vec3& prev_up, const glm::vec3& prev_right,
                            const glm::vec3& prev_direction, const glm::vec3& prev_center) {
            position = prev_position;
            forward = prev_forward;
            up = prev_up;
            right = prev_right;
            direction = prev_direction;
            center = prev_center;
        }

        void copyCamera(const Cam *camera) {
            position = camera->position;
            forward = camera->forward;
            up = camera->up;
            right = camera->right;
            direction = camera->direction;
            center = camera->center;
            distanceToTarget = camera->distanceToTarget;
        }

        void MoveForward(float distance)
        {
            // Translates the Cam using the `dir` vector computed from
            // `forward`. Movement will always keep the Cam at the same
            // height. For example, if you rotate your head up/down, and then
            // walk forward, then you will still keep the same relative
            // distance (height) to the ground!
            direction = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += direction * distance;
        }

        void TranslateForward(float distance)
        {
            // TODO(student): Translate the Cam using the `forward` vector.
            // What's the difference between `TranslateForward()` and
            // `MoveForward()`?
            position = position + glm::normalize(forward) * distance;

        }

        void TranslateUpward(float distance)
        {
            // TODO(student): Translate the Cam using the `up` vector.
            position = position + glm::normalize(glm::vec3(0, 1, 0)) * distance;

        }

        void TranslateRight(float distance)
        {
            // TODO(student): See instructions below. Read the entire thing!
            // You need to translate the Cam using the `right` vector.
            // Usually, however, translation using Cam's `right` vector
            // is not very useful, because if the Cam is rotated around the
            // `forward` vector, then the translation on the `right` direction
            // will have an undesired effect, more precisely, the Cam will
            // get closer or farther from the ground. The solution is to
            // actually use the projected `right` vector (projected onto the
            // ground plane), which makes more sense because we will keep the
            // same distance from the ground plane.
            right = glm::cross(forward, up);
            position = position + glm::normalize(right) * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            // TODO(student): Compute the new `forward` and `up` vectors.
            // Don't forget to normalize the vectors! Use `glm::rotate()`.
            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1)));
            up = glm::cross(right, forward);
        }

        void RotateFirstPerson_OY(float angle)
        {
            // TODO(student): Compute the new `forward`, `up` and `right`
            // vectors. Use `glm::rotate()`. Don't forget to normalize the
            // vectors!

            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1)));
            up = glm::cross(right, forward);
        }

        void RotateFirstPerson_OZ(float angle)
        {
            // TODO(student): Compute the new `right` and `up`. This time,
            // `forward` stays the same. Use `glm::rotate()`. Don't forget
            // to normalize the vectors!
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, forward) * glm::vec4(right, 1)));
            // right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1)));
            up = glm::cross(forward, right);
        }

        void RotateThirdPerson_OX(float angle)
        {
            // TODO(student): Rotate the Cam in third-person mode around
            // the OX axis. Use `distanceToTarget` as translation distance.
            TranslateRight(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateRight((-1) * distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle)
        {
            // TODO(student): Rotate the Cam in third-person mode around
            // the OY axis.
            TranslateUpward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateUpward((-1) * distanceToTarget);
        }

        void RotateThirdPerson_OZ(float angle)
        {
            // TODO(student): Rotate the Cam in third-person mode around
            // the OZ axis.
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward((-1) * distanceToTarget);
        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 center;
        glm::vec3 direction;
    };
}   // namespace implemented
