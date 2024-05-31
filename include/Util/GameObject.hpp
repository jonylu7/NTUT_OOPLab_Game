#ifndef UTIL_GAME_OBJECT_HPP
#define UTIL_GAME_OBJECT_HPP

#include <memory>
#include <vector>

#include "Camera.hpp"
#include "Core/Drawable.hpp"
#include "Util/Transform.hpp"

namespace Util {
/**
 * @class GameObject
 * @brief A class representing a game object.
 *
 * This class encapsulates the properties and behaviors of a game object.
 * @note This is an abstract class. Inherit from this class to create your own
 * game objects.
 *
 */
class GameObject {
public:
    Util::Transform m_Transform;

public:
    /**
     * @brief Default constructor.
     */
    GameObject() = default;

    /**
     * @brief Parameterized constructor.
     *
     * @param drawable The Util::Drawable component of the game object.
     * @param zIndex The z-index of the game object.
     * @param visible The visibility of the game object.
     * @param children The children of the game object.
     * @param movingRelativeToCamera Whether the object can move relative to
     * camera position
     * @param transfrom predefined transform
     */
    GameObject(const std::shared_ptr<Core::Drawable> &drawable,
               const float zIndex, const bool visible = true,
               const bool movingRelativeToCamera = true,
               const Util::Transform transfrom = Util::Transform())
        : m_Drawable(std::move(drawable)),
          m_ZIndex(zIndex),
          m_Visible(visible),
          b_MovingRelativeToCamera(movingRelativeToCamera),
          m_Transform(transfrom) {}

    /**
     * @brief Copy constructor.
     * @param other
     *
     * @note This is a shallow copy constructor, meaning the m_Drawable points
     * to the same reference as same as `other`'s does.
     */
    GameObject(const GameObject &other) = default;

    /**
     * @brief Default move constructor..
     */
    GameObject(GameObject &&other) = default;

    /**
     * @brief Default destructor.
     */
    virtual ~GameObject() = default;

    // Deleted assignment operator.
    GameObject &operator=(const GameObject &other) = delete;

    /**
     * @brief Get the z-index of the game object.
     *
     * @return The z-index of the game object.
     */
    float GetZIndex() const { return m_ZIndex; }

    void SetTransform(Util::Transform transform) { m_Transform = transform; }

    /**
     * @brief Get the transform of the game object.
     *
     * @return The transform of the game object.
     */
    Transform GetTransform() const { return m_Transform; }

    /**
     * @brief Get the size of its drawable component.
     *
     * @return vec2(x, y) representing the size of the drawable component.
     */
    glm::vec2 GetScaledSize() const {
        return m_Drawable->GetSize() * m_Transform.scale;
    };

    /**
     * @brief Get the children of the game object.
     *
     * @return The children of the game object.
     */

    /**
     * @brief Set the z-index of the game object.
     * z-index is used to determine the order in which game objects are drawn,
     * the greater z-index, the topper the its Util::Drawable is
     *
     * @param index The new z-index of the game object.
     */
    void SetZIndex(float index) { m_ZIndex = index; }

    /**
     * @brief Set the drawable component of the game object.
     *
     * @param drawable The new drawable component of the game object.
     */
    void SetDrawable(const std::shared_ptr<Core::Drawable> &drawable) {
        m_Drawable = drawable;
    }

    /**
     * @brief Set the visibility of the game object.
     *
     * @param visible The new visibility of the game object.
     */
    void SetVisible(const bool visible) { m_Visible = visible; }

    /**
     * @brief Set the object can move relative to camera position
     *
     * @param movingRelativeToCamera The new status of moving
     */
    void setMovingRelativeToCamera(const bool movingRelativeToCamera) {
        b_MovingRelativeToCamera = movingRelativeToCamera;
    };

    virtual void Draw();

    // should be removed
    virtual void Start(){};
    virtual void Update(){};
    virtual void Update(const Util::Transform &transform){};

protected:
    std::shared_ptr<Core::Drawable> m_Drawable = nullptr;

    float m_ZIndex = 1;
    bool m_Visible = true;
    bool b_MovingRelativeToCamera = true;
};
} // namespace Util
#endif
