#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>


#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"imgui/imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"

#define WIDTH 1920
#define HEIGHT 1080

//includes local
#include"game.hpp"

//yaw and vec3 var frontpos
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
float lastX = WIDTH/2.0f;
float lastY = HEIGHT/2.0f;
float fov = 45.0f;
//screen callback
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
  glViewport(0,0,width,height);
}

//scroll callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  fov -=(float)yoffset;
  if(fov < 1.0f){
    fov = 1.0f;
  }
  if(fov >45.0f){
    fov = 45.0f;
  }
}

//mousr callback
void mouse_callback(GLFWwindow* window,double xpos,double ypos){
  if(firstMouse){
    lastX=WIDTH/2.0f;
    lastY = HEIGHT/2.0f;;
    firstMouse = false;
  }
  float xOffset = xpos- lastX;
  float yOffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;

  const float sensitivity = 0.05f;
  xOffset *=sensitivity;
  yOffset *=sensitivity;
  
  yaw  +=xOffset;
  pitch+=yOffset;

  if(pitch >=89.0f){
    pitch = 89.0f;
  }
  if(pitch<-89.0f){
    pitch = -89.0f;
  }

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
  
}

//for key inputs
bool up = false;
bool down = false;
bool left = false;
bool right = false;
void myKeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods){
  if(key == GLFW_KEY_UP && action == GLFW_PRESS){
    up= true;
  }
  if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
    down= true;
  }
  if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
    left = true;
  }
  if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
    right = true;
  }
}

int processInput(GLFWwindow *window){
  if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window,true);
    return 0;
  }
  if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
    return 1;
  }
  if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
    return 2;
  }
  if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
    return 3;
  }
  if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
    return 4;
  }
  //for light
  if(up){
    up =false;
    return 6;
  }
  if(down){
    down = false;
    return 7;
  }
  if(left){
    left =false;
    return 8;
  }
  if(right){
    right = false;
    return 9;
  }
  return 5;
}


int main(){
  //init glfw and version
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

  //window
  GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"hello window",NULL,NULL);
  if(window == NULL){
    std::cout<<"Failed to create GLFW window"<<std::endl;
    glfwTerminate();
  }
  glfwSwapInterval(1);
  //callbacks
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window,mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetKeyCallback(window,myKeyCallbackFunc);

  //init imgui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();(void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  //set style
  ImGui::StyleColorsDark();

  //setup backends
  
  ImGui_ImplGlfw_InitForOpenGL(window,true);

  const char* glsl_version = "#version 330 core";
  ImGui_ImplOpenGL3_Init(glsl_version);

  //state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f,0.55f,0.60f,1.0f);
  
  
  
  //load glad
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Failed to initialize GLAD"<<std::endl;
    
  }
  //enable depth test
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_ALWAYS);
  glDepthFunc(GL_LESS);
  //inside window mousr
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  //wireframe
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  //MAIN GAME OBJECT
  Game game;

  static float filter = 0.5f;
  //MAIN LOOP
  while(!glfwWindowShouldClose(window)){

    glfwPollEvents();
    //check if window is minimized
    if(glfwGetWindowAttrib(window,GLFW_ICONIFIED) != 0){
      ImGui_ImplGlfw_Sleep(10);
      continue;
    }
    //start imgui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //set val of demo window
    if(show_demo_window){
      ImGui::ShowDemoWindow(&show_demo_window);
    }
    //place inside brackets to just code organization,code limitation
    static int counter = 0;
    
    ImGui::Begin("Helloworld box");
    ImGui::Text("Some random text");
    ImGui::Checkbox("DEmo window",&show_demo_window);
    ImGui::Checkbox("DEmo another window",&show_another_window);
    
    ImGui::SliderFloat("float",&filter,0.0f,1.0f);
    ImGui::ColorEdit3("clear col",(float*)&clear_color);
    
    if(ImGui::Button("Button")){
      counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d",counter);
    
    ImGui::Text("App avg %.3f ms/frame (%.1f FPS)",1000.0f/io.Framerate,io.Framerate);
    ImGui::End();

    //show another asample window
    if(show_another_window){
      ImGui::Begin("Another window",&show_another_window);
      ImGui::Text("Hello from another window");
      if(ImGui::Button("close me")){
	show_another_window = false;
      }
      ImGui::End();
    }
    
    //handle input
    game.HandleInput(processInput(window));

    //std::cout<<"filter val before up: "<<filter<<std::endl;
    //update
    game.Update(cameraFront,fov,filter);

    //render rimgui as well
    ImGui::Render();
    
    //render
    //glClearColor(0.678f,0.847f,0.902f,1.0f);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render gui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    game.Draw();
    
    
    glfwSwapBuffers(window);

  }


  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
  
}
