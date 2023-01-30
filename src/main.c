#include "core/program.h"
#include "program_info.h"

int main() {
    Program *program = new_program(DEFAULT_W, DEFAULT_H, PROGRAM_NAME);

    while(!glfwWindowShouldClose(program->window)) {
        glfwPollEvents();
    }
    
    return program->cleanup(program);
}
