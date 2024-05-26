#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "freetype-gl.h"
#include "vertex-buffer.h"
#include "texture-atlas.h"
#include "texture-font.h"

#include <iostream>

void render_text(const char *text, float x, float y, float sx, float sy, texture_font_t *font, vertex_buffer_t *buffer) {
    vec2 pen = {{x, y}};
    float scale = sx;
    texture_glyph_t *glyph = NULL;

    for (const char *p = text; *p; ++p) {
        glyph = texture_font_get_glyph(font, *p);
        if (glyph) {
            if (p > text) {
                float kerning = texture_glyph_get_kerning(glyph, *(p - 1));
                pen.x += kerning * scale;
            }

            float x0 = pen.x + glyph->offset_x * scale;
            float y0 = pen.y - glyph->offset_y * scale;
            float x1 = x0 + glyph->width * scale;
            float y1 = y0 + glyph->height * scale;

            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;

            vertex_t vertices[] = {
                {{x0, y0}, {s0, t0}},
                {{x1, y0}, {s1, t0}},
                {{x1, y1}, {s1, t1}},
                {{x0, y0}, {s0, t0}},
                {{x1, y1}, {s1, t1}},
                {{x0, y1}, {s0, t1}}
            };

            vertex_buffer_push_back(buffer, vertices, 6);
            pen.x += glyph->advance_x * scale;
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Text Rendering with FreeTypeGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // FreeTypeGL
    texture_atlas_t *atlas = texture_atlas_new(512, 512, 1);
    texture_font_t *font = texture_font_new_from_file(atlas, 48, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    // Set up the vertex buffer
    vertex_buffer_t *buffer = vertex_buffer_new("vertex:2f,tex_coord:2f");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        render_text("Hello, World!", 100, 100, 1.0, 1.0, font, buffer);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindVertexArray(buffer->vao);
        glUseProgram(texture_font_get_shader(font));
        glUniformMatrix4fv(texture_font_get_uniform(font), 1, 0, glm::value_ptr(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f)));
        glBindTexture(GL_TEXTURE_2D, atlas->id);
        glDrawArrays(GL_TRIANGLES, 0, buffer->size);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    vertex_buffer_delete(buffer);
    texture_font_delete(font);
    texture_atlas_delete(atlas);
    glfwTerminate();
    return 0;
}