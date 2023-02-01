#include "core/magmatis.h"
#include "program_info.h"

int main() {
    Magmatis *magmatis = new_program(DEFAULT_W, DEFAULT_H, PROGRAM_NAME);

    while(!glfwWindowShouldClose(magmatis->window)) {
        glfwPollEvents();
    }
    
    return magmatis->cleanup(magmatis);
}
