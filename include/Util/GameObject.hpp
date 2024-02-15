#ifndef UTIL_GAME_OBJECT_HPP
#define UTIL_GAME_OBJECT_HPP

#include <memory>
#include <vector>

#include "Core/Drawable.hpp"
#include "Util/Transform.hpp"

namespace Util {
class GameObject {
public:
    GameObject() = default;

    GameObject(std::unique_ptr<Core::Drawable> drawable, const float zIndex,
               const std::vector<std::shared_ptr<GameObject>> &children =
                   std::vector<std::shared_ptr<GameObject>>())
        : m_Drawable(std::move(drawable)),
          m_Children(children),
          m_ZIndex(zIndex) {}

    GameObject(const GameObject &other) = delete;

    GameObject(GameObject &&other) = delete;

    GameObject &operator=(const GameObject &other) = delete;

    virtual ~GameObject() = default;

    float GetZIndex() const { return m_ZIndex; }

    std::vector<std::shared_ptr<GameObject>> &GetChildren() {
        return m_Children;
    }

    void SetZIndex(float index) { m_ZIndex = index; }

    void SetDrawable(std::unique_ptr<Core::Drawable> drawable) {
        m_Drawable = std::move(drawable);
    }

    void AppendChild(std::shared_ptr<GameObject> child) {
        m_Children.push_back(std::move(child));
    }

    virtual void Start() = 0;

    virtual void
    Update(const Util::Transform &transform = Util::Transform()) = 0;

    virtual void Draw();

protected:
    Util::Transform m_Transform; // idk if this should be here.

    std::unique_ptr<Core::Drawable> m_Drawable = nullptr;
    std::vector<std::shared_ptr<GameObject>> m_Children;

    float m_ZIndex;
};
} // namespace Util
#endif
