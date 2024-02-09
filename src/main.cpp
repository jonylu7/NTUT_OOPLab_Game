#include "App.hpp"
#include <iostream>
#include "Core/Context.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

int main(int, char **) {

    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        context->Update();
        switch (app.GetCurrentState()) {
        case App::State::START:
            app.Start();
            break;
        case App::State::UPDATE:
            app.Update();
            break;

        case App::State::END:
            app.End();
            context->SetExit(true);
            break;
        }



    }
    return 0;
}
