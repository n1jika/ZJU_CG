#include "render_flag.h"

RenderFlag::RenderFlag(const Options& options) : Application(options) {
    // create star shader
    const char* vsCode =
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPosition;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0f, 1.0f);\n"
        "}\n";

    const char* fsCode =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(1.0f, 0.870f, 0.0f, 1.0f);\n"
        "}\n";

    _starShader.reset(new GLSLProgram);
    _starShader->attachVertexShader(vsCode);
    _starShader->attachFragmentShader(fsCode);
    _starShader->link();

    float aspect_of_the_window = static_cast<float>(options.windowWidth) / static_cast<float>(options.windowHeight);
    float rotation_in_radians[5];
    glm::vec2 ndc_position[5];
    float size_of_star = 0.05f;

    rotation_in_radians[0] = M_PI / 10.0f + atan(0.6);
    ndc_position[0] = glm::vec2(-1.0f / 3.0f, 0.8f);

    rotation_in_radians[1] = M_PI / 10.0f + atan2(1 ,7 );
    ndc_position[1] = glm::vec2(-0.2f, 0.6f);

    rotation_in_radians[2] = M_PI / 10.0f - atan2(2, 7);
    ndc_position[2] = glm::vec2(-0.2f, 0.3f);

    rotation_in_radians[3] = M_PI / 10.0f - atan(0.8);
    ndc_position[3] = glm::vec2(-1.0f / 3.0f, 0.1f);

    rotation_in_radians[4] = 0;
    ndc_position[4] = glm::vec2(-2.0f / 3.0f , 0.5f);

    for (int i = 0; i < 4; i++)
        _stars[i].reset(new Star(ndc_position[i], rotation_in_radians[i], size_of_star, aspect_of_the_window));
    _stars[4].reset(new Star(ndc_position[4], rotation_in_radians[4], size_of_star * 3.0f, aspect_of_the_window));
}

void RenderFlag::handleInput() {
    if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
        glfwSetWindowShouldClose(_window, true);
        return;
    }
}

void RenderFlag::renderFrame() {
    showFpsInWindowTitle();

    // we use background as the flag
    glClearColor(0.87f, 0.161f, 0.063f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _starShader->use();
    for (int i = 0; i < 5; ++i) {
        if (_stars[i] != nullptr) {
            _stars[i]->draw();
        }
    }
}