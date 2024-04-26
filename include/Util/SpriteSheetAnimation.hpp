//
// Created by nudle on 2024/4/12.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEETANIMATION_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEETANIMATION_HPP
#include "SpriteSheet.hpp"

#include "pch.hpp"

#include <exception>

#include "Core/Drawable.hpp"

#include "Util/Image.hpp"

namespace Util {
/**
 * @class Animation
 * @brief Class representing an animation with frames.
 */
class SpriteSheetAnimation : public Core::Drawable {
public:
    /**
     * @brief Enum representing the state of the animation.
     */
    enum class State {
        PLAY,     /**< Animation is playing. */
        PAUSE,    /**< Animation is paused. */
        COOLDOWN, /**< Animation is COOLDOWN. */
        ENDED     /**< Animation is Ended(looping == false && Animate end.). */
    };

    /**
     * @brief Constructor for Animation class.
     * @param paths Vector of file paths for the frames.
     * @param play Whether the animation should play right away.
     * @param interval Interval between frames in milliseconds.
     * @param looping Whether the animation should loop.
     * @param cooldown Cooldown time in milliseconds before the animation can
     * restart.
     */
    SpriteSheetAnimation():m_State(State::PAUSE),
        m_Interval(0),
        m_Looping(false),
        m_Cooldown(100){};
    SpriteSheetAnimation(std::shared_ptr<SpriteSheet> spriteSheet, bool play,std::size_t interval, bool looping=true, std::size_t cooldown=100);

    void initSpriteSheetAnimation(std::shared_ptr<SpriteSheet> spriteSheet, bool play,std::size_t interval, bool looping=true, std::size_t cooldown=100);
    void setFrameRange(int start,int end){m_startFrame=start;m_endFrame=end;}
    bool getFinished(){if(m_State==State::ENDED)return true; return false;}
    /**
     * @brief Get the interval between frames.
     * @return Interval between frames in milliseconds.
     */
    void setInterval(int Interval){m_Interval=Interval;}
    int GetInterval() const { return m_Interval; }

    /**
     * @brief Check if the animation loops.
     * @return True if the animation loops, false otherwise.
     */
    void setLooping(bool Looping){m_Looping=Looping;}
    bool GetLooping() const { return m_Looping; }

    /**
     * @brief Get the cooldown time.
     * @return Cooldown time in milliseconds.
     */
    void setCooldown(int Cooldown){m_Cooldown=Cooldown;}
    int GetCooldown() const { return m_Cooldown; }

    /**
     * @brief Get the index of the current frame.
     * @return Index of the current frame.
     */
    std::size_t GetCurrentFrameIndex() const { return m_Index; }

    /**
     * @brief Get the total number of frames in the animation.
     * @return Total number of frames.
     */
    std::size_t GetFrameCount() const { return m_SpriteSheet->getSize(); }

    /**
     * @brief Get the current state of the animation
     * @return The current state of the animation
     */
    State GetState() const { return m_State; }

    /**
     * @brief Get the size of the current frame.
     * @return Size of the current frame.
     */
    glm::vec2 GetSize() const override { return m_SpriteSheet->getSpriteSize(); }

    /**
     * @brief Set the interval between frames.
     * @param interval Interval between frames in milliseconds.
     */
    void SetInterval(int interval) { m_Interval = interval; }

    /**
     * @brief Set whether the animation loops.
     * @param looping True to enable looping, false to disable.
     */
    void SetLooping(bool looping) { m_Looping = looping; }

    /**
     * @brief Set the cooldown time.
     * @param cooldown Cooldown time in milliseconds.
     */
    void SetCooldown(int cooldown) { m_Cooldown = cooldown; }

    /**
     * @brief Set the current frame of the animation.
     * @param index Index of the frame to set as current.
     */
    void SetCurrentFrame(std::size_t index);

    /**
     * @brief Draw the current frame.
     * @param transform Transformation matrix for drawing.
     * @param zIndex Z-index for drawing.
     */
    void Draw(const Util::Transform &transform, const float zIndex) override;

    /**
     * @brief Start playing the animation.
     * If the animation is already playing, this method won't do anything.
     * If the animation has ended and `looping` is set to `false`, this would
     * replay the animation once.
     */
    void Play();

    /**
     * @brief Pause the animation.
     * If the animation has already been paused, this method won't do anything.
     */
    void Pause();

private:
    /**
     * @brief Update the animation frames.
     */
    void Update();

private:
    std::vector<std::shared_ptr<Util::Image>> m_Frames;
    std::shared_ptr<SpriteSheet> m_SpriteSheet =std::make_shared<SpriteSheet>();
    State m_State;
    double m_Interval;
    bool m_Looping;
    std::size_t m_Cooldown;
    bool m_IsChangeFrame = false;

    unsigned long m_CooldownEndTime = 0;
    double m_TimeBetweenFrameUpdate = 0;

    std::size_t m_Index = 0;

    int m_startFrame=-1;
    int m_endFrame=-1;
};
} // namespace Util

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPRITESHEETANIMATION_HPP
