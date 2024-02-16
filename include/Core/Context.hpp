#ifndef CORE_CONTEXT_HPP
#define CORE_CONTEXT_HPP

#include "Util/Input.hpp"
#include "config.hpp"
#include "pch.hpp" // IWYU pragma: export
constexpr int CURSORATWINDOWBOARDERMARGIN = 3;
namespace Core {
class Context {
public:
    /**
     * @brief Initialize context for SDL, OpenGL, and create a window
     */
    Context();
    Context(const Context &) = delete;
    Context(Context &&) = delete;

    ~Context();

    Context &operator=(const Context &) = delete;
    Context &operator=(Context &&) = delete;

    static std::shared_ptr<Context> GetInstance();

    bool GetExit() const { return m_Exit; }
    unsigned int GetWindowWidth() const { return m_WindowWidth; }
    unsigned int GetWindowHeight() const { return m_WindowHeight; }

    void SetExit(bool exit) { m_Exit = exit; }
    void SetWindowWidth(unsigned int width) { m_WindowWidth = width; }
    void SetWindowHeight(unsigned int height) { m_WindowHeight = height; }

    static int IsCurosrAtBoarder() {
        /*
         * will check if the cursor at the window boarder
         * Up:0
         * Right:1
         * Down:2
         * Left:3
         * None:4
         */

        glm::vec2 CursorPostion = Util::Input::GetCursorPosition();
        float halfWindowHeight = s_Instance->m_WindowHeight / 2;
        float halfWindowWidth = s_Instance->m_WindowWidth / 2;
        if (halfWindowWidth - abs(CursorPostion.x) <=
            CURSORATWINDOWBOARDERMARGIN) {
            if (CursorPostion.x > 0) {
                return 1;
            } else {
                return 3;
            }
        }
        if (halfWindowHeight - abs(CursorPostion.y) <=
            CURSORATWINDOWBOARDERMARGIN) {
            if (CursorPostion.y > 0) {
                return 0;
            } else {
                return 2;
            }
        }
        return 4;
    }

    void Update();

private:
    SDL_Window *m_Window;
    SDL_GLContext m_GlContext;

    static std::shared_ptr<Context> s_Instance;
    bool m_Exit = false;

    unsigned int m_WindowWidth = WINDOW_WIDTH;
    unsigned int m_WindowHeight = WINDOW_HEIGHT;
};

} // namespace Core

#endif
