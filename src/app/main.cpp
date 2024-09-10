
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "stdio.h"

#include "KitsuneAbsorption.h"
#include "Dice.h"

int main (){
    if(!glfwInit()){
        printf("Cannot init GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_DECORATED,GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    ImVec2 winSize(600,800);

    GLFWwindow* window = glfwCreateWindow(winSize.x,winSize.y, "KitsuneCalculator", nullptr, nullptr);
    
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

  
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Setup Platform/Renderer backends
    
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    KitsuneAbsorption kitsune(0,0,0);

    int damage = 0;
    int lastDamageInput = 0;

    int absorbedDamage = 0;
    int regeneratedChakra = 0;
    int storedDamage = 0;
    int healed = 0;

    Dice::Init();

     while (!glfwWindowShouldClose(window)){
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
     
        ImGui::SetNextWindowPos(viewport->WorkPos); 
        ImGui::SetNextWindowSize(viewport->WorkSize); 
        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
        

        ImGui::Begin("Calc",nullptr,ImGuiWindowFlags_NoTitleBar);
        
        ImGui::Text("Character Data");

        ImGui::InputInt("Level",&kitsune.Level,1,1);
        ImGui::InputInt("Wisdom",&kitsune.WisdomModifier,1,1);
        ImGui::InputInt("Tail Count",&kitsune.TailsCount,1,1);
        ImGui::InputInt("Absorption Capacity",&kitsune.AbsorptionCapacity,1,1);

        ImGui::InputInt("Dealt Damage", &damage,1,1);

        ImGui::Checkbox("Vest Of Inverted Reality Equipped?",&kitsune.IsVestmentsOfInvertedRealityEquipped);

        bool IsCalculationBtnPressed = ImGui::Button("Calculate Absorption",{300,50});

        if(IsCalculationBtnPressed){
            int* absorptionData = kitsune.Absorb(damage);
            absorbedDamage = absorptionData[KT_ABSORBED_DAMAGE];
            regeneratedChakra = absorptionData[KT_REGENERATED_CHAKRA];
            storedDamage = absorptionData[KT_STORED_DAMAGE];
        }

        ImGui::Text("Damage Absorbed: %d\nChakra regenerated: %d\nStored Damage: %d", absorbedDamage, regeneratedChakra, storedDamage);

        ImGui::End();

        
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);
     }
    return 0;
}