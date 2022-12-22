#include <SDL2/SDL.h>
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace std;

static void GLFWErrorCallback(int error, const char* description) {

    printf("GLFW Error %i: %s\n",error,description);
}

int main(int argc, char *argv[])
{


    glfwInit();
    if (glfwInit() < 0)
    {
        cout << "Failed to initialize GLFW" << endl;
        glfwSetErrorCallback(GLFWErrorCallback);
        return 0;
    }
    else {
        cout << "GLFW initialized" << endl;
    }

    // create a window data type
    SDL_Window * window = nullptr;

    //Initialize the video subsystem
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL VIDEO SYSTEM could not initialize !!! SDL_Error: " << SDL_GetError() << endl;
    }
    else {
        cout << "SDL VIDEO SYSTEM initialized successfully !!!" << endl;
    }

    //

    //before we create our window specify the version of OpenGL we want to use

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                       SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);



    //Request a SDL window
    window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640, 480,
                              SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Test for SDL Rendering
    /*SDL_SetRenderDrawColor(renderer, 200, 0, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);*/

    //OpenGL set up the graphics context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    // Set up the function pointers

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    //Infinite loop for our application



    glViewport(0, 0, 640, 480);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);


    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SwapWindow(window);

    float vertices[6] = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    glClear(GL_COLOR_BUFFER_BIT);
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices [0] * 6), &vertices[0], GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGetString(GL_VERSION);
    cout << glGetString(GL_VERSION) << endl;


    bool mouseIsInWindow = false;
    bool softwareIsRunning = true;
    while(softwareIsRunning)
    {


        SDL_Event event;
        while(SDL_PollEvent(&event))
        {

            //clear the color buffer and draw the triangle


            if(event.type == SDL_QUIT) {
                softwareIsRunning = false;
            }
            // Change random color by pressing enter key
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                glClearColor((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);



                SDL_GL_SwapWindow(window);
            }

           // change to random color when mouse enters window
           if(event.type == SDL_MOUSEMOTION)
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
           }

        }


    }

    SDL_DestroyWindow(window);
    return 0;

}


