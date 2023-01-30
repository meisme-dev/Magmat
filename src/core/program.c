#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../program_info.h"
#include "program.h"

static int _program__cleanup(struct Program *self) {
    glfwDestroyWindow(self->window);
    glfwTerminate();
    free(self);
    return EXIT_SUCCESS;
}

Program *_program__new(unsigned int w, unsigned int h, char *title) {
    Program *program = (Program *)malloc(sizeof(Program));

    if(program == NULL) {
        fprintf(stderr, "Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    if(!glfwInit()) {
        perror("Failed to initialize glfw");
        exit(EXIT_FAILURE);
    }

    GLFWwindow *window = glfwCreateWindow(w, h, title, NULL, NULL);

    if(!window) {
        perror("Failed to create window");
        exit(EXIT_FAILURE);
    }

    program->window = window;
    program->cleanup = _program__cleanup;
    return program;
}