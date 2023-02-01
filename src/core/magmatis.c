#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "../program_info.h"
#include "../extra/colors.h"
#include "magmatis.h"

static int _program__cleanup(struct Magmatis *self) {
    glfwDestroyWindow(self->window);
    glfwTerminate();
    free(self);
    return EXIT_SUCCESS;
}

Magmatis *_program__new(unsigned int w, unsigned int h, char *title) {
    Magmatis *magmatis = (Magmatis *)malloc(sizeof(Magmatis));

    if(magmatis == NULL) {
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

    char debug_utils_extension[] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    int *instance_extensions[] = {
       (int*) &debug_utils_extension
    };

    VkApplicationInfo application_info;
    memset(&application_info, 0, sizeof(application_info));
    application_info.pApplicationName = PROGRAM_NAME;
    application_info.applicationVersion = VK_MAKE_API_VERSION(V_VARIANT, V_MAJOR, V_MINOR, V_PATCH);
    application_info.pEngineName = ENGINE_NAME;
    application_info.engineVersion = VK_MAKE_API_VERSION(V_VARIANT, V_MAJOR, V_MINOR, V_PATCH);
    application_info.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 2);

    uint32_t layer_prop_count = 0;
    vkEnumerateInstanceLayerProperties(&layer_prop_count, NULL);

    VkLayerProperties layer_properties[layer_prop_count];
    vkEnumerateInstanceLayerProperties(&layer_prop_count, layer_properties);

    printf("%sAvailabe layers:\n", B_GREEN);
    for(uint32_t i = 0; i < layer_prop_count - 1; i++) {
        printf("%s├── %s%s\n", GREEN, CYAN, layer_properties[i].layerName);
    }
    printf("%s└── %s%s\n\n", GREEN, CYAN, layer_properties[layer_prop_count - 1].layerName);

    uint32_t required_extension_count = 0;
    const char **required_extensions;

    required_extensions = glfwGetRequiredInstanceExtensions(&required_extension_count);

    VkInstanceCreateInfo instance_create_info;
    memset(&instance_create_info, 0, sizeof(instance_create_info));
    instance_create_info.pApplicationInfo = &application_info;
    instance_create_info.ppEnabledExtensionNames = required_extensions;
    instance_create_info.enabledExtensionCount = required_extension_count;

    VkInstance instance;
    if(vkCreateInstance(&instance_create_info, NULL, &instance) != VK_SUCCESS) {
        fprintf(stderr, "%sFailed to create instance%s", RED, CLEAR);
        exit(EXIT_FAILURE);
    };


    magmatis->window = window;
    magmatis->cleanup = _program__cleanup;
    return magmatis;
}