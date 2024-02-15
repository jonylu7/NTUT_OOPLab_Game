#include "App.hpp"
#include "Core/Context.hpp"

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
