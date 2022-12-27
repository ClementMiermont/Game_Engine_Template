#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

static const GLuint WIDTH = 700;
static const GLuint HEIGHT = 700;

static const GLchar * vertex_Shader_Source =
        "#version 120 \n"
        "attribute vec2 coord2d;\n"
        "void main(){\n"
        "   gl_Position = vec4(coord2d, 0.0, 1.0);\n"
        "}\n";

static const GLchar * fragment_Shader_Source =
        "#version 120 \n"
        "void main() {\n"
        " gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

static GLfloat vertices[] = {
    0.0, 0.8,
        -0.8, -0.8,
        0.8, -0.8,
};

 GLuint common_get_shader_program(
         const char *vertex_shader_source,
         const char *fragment_shader_source
         ) {

     GLchar * log = NULL;
     GLint log_length, success;
     GLuint fragment_shader, program, vertex_shader;


     //vertex Shader//
     vertex_shader = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
     glCompileShader(vertex_shader);
     glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
     glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
     log = (GLchar *)malloc(log_length);
     if (log_length > 0) {
         glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
         printf("Vertex shader log :\n\n%s\n", log);
     }
     if(!success) {
         printf("Vertex shader compile error\n");
         exit(EXIT_FAILURE);
     }

     // fragment Shader//
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0) {
            log = (GLchar*)malloc(log_length);
            glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
            printf("Fragment shader log :\n\n%s\n", log);
        }
        if(!success) {
            printf("Fragment shader compile error\n");
            exit(EXIT_FAILURE);
        }

        // Link shaders //
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0) {
            log = (GLchar*)malloc(log_length);
            glGetProgramInfoLog(program, log_length, NULL, log);
            printf("Shader program log :\n\n%s\n", log);
        }
        if(!success) {
            printf("Shader program link error\n");
            exit(EXIT_FAILURE);
        }

        // Cleanup
        free (log);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return program;

 }

int main(void)
{

    GLint attribute_coord2d;
    GLuint program, vbo;
    SDL_Event event;
    SDL_GLContext gl_context;
    SDL_Window * window = nullptr;

    glfwInit();


    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL VIDEO SYSTEM could not initialize !!! SDL_Error: " << SDL_GetError() << endl;
    }
    else {
        cout << "SDL VIDEO SYSTEM initialized successfully !!!" << endl;
    }

    //before we create our window specify the version of OpenGL we want to use

    //Request a SDL window
    window = SDL_CreateWindow(__FILE__,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_OPENGL);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    gl_context = SDL_GL_CreateContext(window);
    //load all openGL functions using the SDL_GL_GetProcAddress function
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    if (gladLoadGLLoader(SDL_GL_GetProcAddress) <0)
    {
        cout << "Failed to initialize GLAD" << endl;
        return 0;
    }
    else {
        cout << "GLAD initialized" << endl;
    }

    //Shader setup
    program = common_get_shader_program(vertex_Shader_Source, fragment_Shader_Source);
    attribute_coord2d = glGetAttribLocation(program, "coord2d");

    // Buffer setup //
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //global draw state

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SwapWindow(window);

    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);


    bool mouseIsInWindow = false;
    bool softwareIsRunning = true;
    while(softwareIsRunning == true)
    {


        //glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord2d);
        SDL_GL_SwapWindow(window);

        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT) {

                glDeleteBuffers (1, &vbo);
                glDeleteProgram (program);
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                SDL_GL_DeleteContext(gl_context);
                SDL_Quit();
                glClear(GL_COLOR_BUFFER_BIT);
                SDL_DestroyWindow(window);

                cout << "EXIT" << endl;
                bool softwareIsRunning = false;
                return EXIT_SUCCESS;
            }
            // Change random color by pressing enter key
           /* if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                glClearColor((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

                SDL_GL_SwapWindow(window);
            }
*/
           // change to random color when mouse enters window
           /*if(event.type == SDL_MOUSEMOTION)
           {
               if(mouseIsInWindow == false)
               {
                   glClearColor((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
                   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
                   SDL_GL_SwapWindow(window);
                   mouseIsInWindow = true;
                   cout << "Mouse entered window" << endl;
               }
           }
           else
           {
               mouseIsInWindow = false;
               //cout << "Mouse left window so boolean mouseIsInWindow is false" << endl;
           }*/

        }
    }

    //cleanup

}


