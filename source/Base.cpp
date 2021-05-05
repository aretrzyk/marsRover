#include "Base.h"

glm::vec3 Base::lightPos = glm::vec4(0.f, 10.f, 0.f, 1.f);
glm::vec3 Base::lightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);

glm::vec3 Base::cameraPos = glm::vec3(0.f, 0.f, 3.f);

glm::mat4 Base::viewMatrix = glm::mat4(1.f);
glm::mat4 Base::projectionMatrix = glm::mat4(1.f);

float Base::dt = 0.1;
