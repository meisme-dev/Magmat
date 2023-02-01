#ifndef APP_H
#define APP_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef struct Magmatis Magmatis;

struct Magmatis {
    GLFWwindow *window;
    int (*cleanup)(struct Magmatis *self);
};

Magmatis *_program__new(unsigned int w, unsigned int h, char *title);

#ifndef USE_LONG_NAMES_PROGRAM
#define new_program(...) _program__new(__VA_ARGS__)
#endif

#endif