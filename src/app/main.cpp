
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <memory>
#include "Window.h"
#include "KitsuneAbsorption.h"
#include "Dice.h"
#include <Render/Animation.h>
#include <Render/Texture.h>



const GLFWvidmode* GetScreenResolution()
{
    return glfwGetVideoMode(glfwGetPrimaryMonitor());
}

int main (){
    if(!glfwInit()){
        printf("Cannot init GLFW");
    }
    if (Window::Init() == -1)
    {
        return -1;
    }

    std::unique_ptr<Window> window = std::make_unique<Window>(0.5f,0.5f,300,300,"Brand new window");
    window->SetProperty(WindowPropertyName::DECORATIONS, false);
    window->SetProperty(WindowPropertyName::RESIZABLE, false);
    window->SetProperty(WindowPropertyName::TRASPERENT_BACKGROUND, true);

    window->Create();

    //window->EnableVsync();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    window->MakeCurrentContext();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);

    KitsuneAbsorption kitsune(20,10,9);
    int lastDamageInput = 0;

    int absorbedDamage = 0;
    int regeneratedChakra = 0;
    int storedDamage = 0;
    int healed = 0;
    int* damageDealt = new int[2] {0};

    Dice::Init();



    int currentImage = 0;
    float lastFrame = 0;
    float currentFrame = 0;
    float deltaTime = 0;
    window->GetDeltaTime();

    std::vector<KeyFrame>* frames = new std::vector <KeyFrame>();
    frames->push_back(KeyFrame("Animations/MusicHappy/_000_125.png", 0));
    frames->push_back(KeyFrame("Animations/MusicHappy/_001_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_002_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_003_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_004_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_005_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_006_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_007_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_008_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_009_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_010_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_011_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_012_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_013_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_014_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_015_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_016_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_017_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_018_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_019_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_020_125.png", 100));
    frames->push_back(KeyFrame("Animations/MusicHappy/_021_125.png", 100));

    /*frames->push_back(KeyFrame("Animations/Dance/4_000_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_001_250.png", 250));
    frames->push_back(KeyFrame("Animations/Dance/4_002_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_003_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_004_250.png", 250));
    frames->push_back(KeyFrame("Animations/Dance/4_005_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_006_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_007_250.png", 250));
    frames->push_back(KeyFrame("Animations/Dance/4_008_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_009_125.png", 125));
    frames->push_back(KeyFrame("Animations/Dance/4_010_250.png", 250));
    frames->push_back(KeyFrame("Animations/Dance/4_011_125.png", 125));*/

    Animation anim(frames);

    while (true){

        currentFrame = window->GetDeltaTime();
        deltaTime = currentFrame - lastFrame;

        anim.MakeStep(glfwGetTime() * 1000);
        
        window->BeginRender();

        ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

        ImGui::Begin("Calc", nullptr, ImGuiWindowFlags_NoTitleBar);

        ImGui::Text("Character Data");
        ImGui::InputInt("Level", &kitsune.Level, 1, 1);
        ImGui::InputInt("Wisdom", &kitsune.WisdomModifier, 1, 1);
        ImGui::InputInt("Tail Count", &kitsune.TailsCount, 1, 1);
        ImGui::InputInt("Absorption Capacity", &kitsune.AbsorptionCapacity, 1, 1);

        ImGui::InputInt2("Dealt damage (physical, magical)", damageDealt);

        ImGui::Checkbox("Vest Of Inverted Reality Equipped?", &kitsune.IsVestmentsOfInvertedRealityEquipped);

        bool IsCalculationBtnPressed = ImGui::Button("Calculate Absorption", { 300,50 });

        if (IsCalculationBtnPressed)
        {
            int* absorptionData = kitsune.Absorb(damageDealt[0], damageDealt[1]);
            absorbedDamage = absorptionData[KT_ABSORBED_DAMAGE];
            regeneratedChakra = absorptionData[KT_REGENERATED_CHAKRA];
            storedDamage = absorptionData[KT_STORED_DAMAGE];
            healed = absorptionData[KT_HEALED];
        }
        
        ImGui::End();
        
        ImVec2 notificationSize = { 400,400 };
        const GLFWvidmode* screenSize = GetScreenResolution();
        

        ImGui::Begin("Notification");
        //ImGui::SetWindowSize(notificationSize);
        
        ImGui::Image((ImTextureID)(intptr_t)anim.CurrentSprite, ImVec2(500,500));

        ImGui::Text("Chakra regenerated: %d\nStored Damage: %d", regeneratedChakra, storedDamage);
        ImGui::Text("Absorbed Damage: %d", absorbedDamage);
        ImGui::Text("Total Damage %d", (damageDealt[0] + damageDealt[1]));
        ImGui::Text("Damage Dealt: %d", (damageDealt[0] + damageDealt[1]) - absorbedDamage);
        ImGui::Text("Heal %d", healed);
        ImGui::Text("Total Damage %d", ((damageDealt[0] + damageDealt[1]) - absorbedDamage) - healed);

        ImGui::End();

        window->EndRender();

        lastFrame = currentFrame;
     }
    return 0;
}