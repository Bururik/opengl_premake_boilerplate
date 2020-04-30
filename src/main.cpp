#include <stdio.h>

#include "engine.h"
#include "window.h"
#include "shader.h"
#include "gl_utils.h"
int main()
{
    glm::vec3 vector(1, 0, 1);
    printf("%f %f %f\n", vector.x, vector.y, vector.z);

    Window window("OpenGL Boilerplate!!!", 960, 540, true);
    window.Create();

    // Setup model

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    unsigned int vao;
    GL(glGenVertexArrays(1, &vao));
    GL(glBindVertexArray(vao));
    unsigned int vbo;
    GL(glGenBuffers(1, &vbo));
    GL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));
    GL(glEnableVertexAttribArray(0));

    Shader shader("Basic", "res/basic.vert", "res/basic.frag");
    if (!shader.Create())
        return 1;

    // Setup ImGui

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;

    while (!window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        GL(glBindVertexArray(vao));
        GL(glDrawArrays(GL_TRIANGLES, 0, 3));
        shader.Unbind();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.Update();
    }

    shader.Delete();

    window.Destroy();
}