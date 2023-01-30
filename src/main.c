#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct App App;
typedef int (*Cleanup)(App app); 

struct App {
    GLFWwindow *window;
    Cleanup cleanup;
};

int _cleanup(App app) {
    glfwDestroyWindow(app.window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

App initialize() {
    App app;

    if(!glfwInit()) {
        perror("Failed to initialize glfw");
        exit(EXIT_FAILURE);
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "ProtoEngine", NULL, NULL);

    if(!window) {
        perror("Failed to create window");
        exit(EXIT_FAILURE);
    }

    app.window = window;
    app.cleanup = _cleanup;
    return app;
}

void close_callback(GLFWwindow *window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    App app = initialize();
    while(!glfwWindowShouldClose(app.window)) {
        glfwPollEvents();
    }
    return ((*app.cleanup)(app));
}
