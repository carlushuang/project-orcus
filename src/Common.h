#ifndef __COMMON_H
#define __COMMON_H

#include <GL/glew.h>

// glfw3 header
#define GL_GLEXT_PROTOTYPES             /*must declare before glfw3.h,
                    for extensions functions like glClearBufferfv() in glext.h */
#include <GLFW/glfw3.h>

// glm header
// https://github.com/g-truc/glm/blob/master/manual.md
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/string_cast.hpp>

#endif