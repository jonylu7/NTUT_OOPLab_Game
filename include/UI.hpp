//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
class UI{
public:
    UI(){};
    ~UI(){};
    void Update(){
        /**
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // put the stuff in here
        ImGui::Begin("Structure Selection Menu");
        ImGui::Text("$ {}",1000);
        ImGui::Text("02:31");
        ImGui::Text("{} L",50);
        if(ImGui::BeginTabBar("",ImGuiTabBarFlags_None) ){
            if (ImGui::BeginTabItem("Buildings")) {
                if (ImGui::Button("Power Plants")) {
                    currentModde = buttonMode::A;
                } else if (ImGui::Button("Barracks")) {
                    currentModde = buttonMode::B;
                    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
                } else if (ImGui::Button("Naval Yard")) {
                    currentModde = buttonMode::C;
                    m_Inf->SetObjectLocation(glm::vec2(-190,100));
                    m_Inf->SetCurrentUpdateMode(Infantry::updateMode::MovingToDestination);
                } else if (ImGui::Button("Ore Refinery")) {
                    currentModde = buttonMode::C;
                    m_Inf->SetCurrentUpdateMode(Infantry::updateMode::Standing);
                } else if (ImGui::Button("War Factory")) {
                    currentModde = buttonMode::C;
                } else if (ImGui::Button("Radar Dome")) {
                    currentModde = buttonMode::C;
                } else if (ImGui::Button("Service Depot")) {
                    currentModde = buttonMode::C;
                } else if (ImGui::Button("Advance Power")) {
                    currentModde = buttonMode::C;
                } else if (ImGui::Button("HeliPad")) {
                    currentModde = buttonMode::C;
                } else if (ImGui::Button("Tech Center")) {
                    currentModde = buttonMode::C;
                }
                ImGui::EndTabItem();
            } else if (ImGui::BeginTabItem("Barracks")) {
                if (ImGui::Button("Normal Troops")) {
                    currentModde = buttonMode::C;
                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();

        //and above
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //ImGui::ShowDemoWindow();

         **/
    }
};


#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
