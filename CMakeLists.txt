cmake_minimum_required(VERSION 3.16)
project(PracticalToolsForSimpleDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    set(TARGET_COMPILE_OPTIONS
            /W4
    )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build)
else ()
    set(TARGET_COMPILE_OPTIONS
            -Wall -Wextra -pedantic
    )
endif ()

option(PTSD_ENABLE_PCH "Turn on PCH to increase compilation speed" OFF)

include(cmake/Dependencies.cmake)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_FILES
        ${SRC_DIR}/Core/Context.cpp
        ${SRC_DIR}/Core/DebugMessageCallback.cpp
        ${SRC_DIR}/Core/VertexArray.cpp
        ${SRC_DIR}/Core/VertexBuffer.cpp
        ${SRC_DIR}/Core/IndexBuffer.cpp
        ${SRC_DIR}/Core/Shader.cpp
        ${SRC_DIR}/Core/Program.cpp
        ${SRC_DIR}/Core/Texture.cpp
        ${SRC_DIR}/Core/TextureUtils.cpp


        ${SRC_DIR}/Util/LoadTextFile.cpp
        ${SRC_DIR}/Util/Logger.cpp
        ${SRC_DIR}/Util/Time.cpp
        ${SRC_DIR}/Util/Input.cpp
        ${SRC_DIR}/Util/SFX.cpp
        ${SRC_DIR}/Util/BGM.cpp
        ${SRC_DIR}/Util/Image.cpp
        ${SRC_DIR}/Util/Text.cpp
        ${SRC_DIR}/Util/TransformUtils.cpp
        ${SRC_DIR}/Util/GameObject.cpp
        ${SRC_DIR}/Util/Root.cpp
        ${SRC_DIR}/Util/Color.cpp
        ${SRC_DIR}/Util/Animation.cpp

        ${SRC_DIR}/Util/ImageArray.cpp
        ${SRC_DIR}/Util/CustomizableImage.cpp

        ${SRC_DIR}/imgui/imgui.cpp
        ${SRC_DIR}/imgui/imgui_demo.cpp
        ${SRC_DIR}/imgui/imgui_draw.cpp
        ${SRC_DIR}/imgui/imgui_impl_sdl2.cpp
        ${SRC_DIR}/imgui/imgui_tables.cpp
        ${SRC_DIR}/imgui/imgui_widgets.cpp
        ${SRC_DIR}/imgui/imgui_impl_sdlrenderer2.cpp
        ${SRC_DIR}/imgui/imgui_impl_opengl3.cpp

        ${SRC_DIR}/App.cpp
        ${SRC_DIR}/Triangle.cpp
        #${SRC_DIR}/Giraffe.cpp
        ${SRC_DIR}/Capybara.cpp
        ${SRC_DIR}/Barracks.cpp
        ${SRC_DIR}/Structure.cpp
        ${SRC_DIR}/Rectangle.cpp
        ${SRC_DIR}/Infantry.cpp
        ${SRC_DIR}/Grid.cpp

        ${SRC_DIR}/Scene/DefaultScene.cpp
        ${SRC_DIR}/Camera.cpp
        ${SRC_DIR}/SpriteSheet.cpp
        ${SRC_DIR}/UI.cpp


)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_FILES
        ${INCLUDE_DIR}/Core/Context.hpp
        ${INCLUDE_DIR}/Core/DebugMessageCallback.hpp
        ${INCLUDE_DIR}/Core/VertexArray.hpp
        ${INCLUDE_DIR}/Core/VertexBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.inl
        ${INCLUDE_DIR}/Core/IndexBuffer.hpp
        ${INCLUDE_DIR}/Core/Shader.hpp
        ${INCLUDE_DIR}/Core/Program.hpp
        ${INCLUDE_DIR}/Core/Texture.hpp
        ${INCLUDE_DIR}/Core/TextureUtils.hpp
        ${INCLUDE_DIR}/Core/Drawable.hpp


        ${INCLUDE_DIR}/Util/LoadTextFile.hpp
        ${INCLUDE_DIR}/Util/Logger.hpp
        ${INCLUDE_DIR}/Util/Time.hpp
        ${INCLUDE_DIR}/Util/Input.hpp
        ${INCLUDE_DIR}/Util/Keycode.hpp
        ${INCLUDE_DIR}/Util/SFX.hpp
        ${INCLUDE_DIR}/Util/BGM.hpp
        ${INCLUDE_DIR}/Util/Image.hpp
        ${INCLUDE_DIR}/Util/Text.hpp
        ${INCLUDE_DIR}/Util/Transform.hpp
        ${INCLUDE_DIR}/Util/TransformUtils.hpp
        ${INCLUDE_DIR}/Util/GameObject.hpp
        ${INCLUDE_DIR}/Util/Root.hpp
        ${INCLUDE_DIR}/Util/Color.hpp
        ${INCLUDE_DIR}/Util/Animation.hpp
        ${INCLUDE_DIR}/Util/ImageArray.hpp
        ${INCLUDE_DIR}/Util/CustomizableImage.hpp

        ${INCLUDE_DIR}/UI.hpp
        ${INCLUDE_DIR}/App.hpp
        ${INCLUDE_DIR}/Tile.hpp
        #${INCLUDE_DIR}/GiraffeText.hpp
        #${INCLUDE_DIR}/Cat.hpp
        ${INCLUDE_DIR}/config.hpp
        ${INCLUDE_DIR}/Triangle.hpp
        ${INCLUDE_DIR}/config.hpp
        ${INCLUDE_DIR}/Capybara.hpp
        ${INCLUDE_DIR}/Barracks.hpp
        ${INCLUDE_DIR}/Structure.hpp
        ${INCLUDE_DIR}/Infantry.hpp
        ${INCLUDE_DIR}/Cell.hpp
        ${INCLUDE_DIR}/Rectangle.hpp
        ${INCLUDE_DIR}/Sprite.hpp
        ${INCLUDE_DIR}/Settings.hpp
        ${INCLUDE_DIR}/Camera.hpp

        ${INCLUDE_DIR}/imgui/imconfig.h
        ${INCLUDE_DIR}/imgui/imgui.h
        ${INCLUDE_DIR}/imgui/imgui_impl_sdl2.h
        ${INCLUDE_DIR}/imgui/imgui_internal.h
        ${INCLUDE_DIR}/imgui/imstb_rectpack.h
        ${INCLUDE_DIR}/imgui/imstb_textedit.h
        ${INCLUDE_DIR}/imgui/imstb_truetype.h
        ${INCLUDE_DIR}/imgui/imgui_impl_sdlrenderer2..h
        ${INCLUDE_DIR}/imgui/imgui_impl_opengl3.h
        ${INCLUDE_DIR}/imgui/imgui_impl_opengl3_loader.h

        ${INCLUDE_DIR}/Scene/Scene.hpp

        ${INCLUDE_DIR}/Core/Context.hpp
        ${INCLUDE_DIR}/Core/DebugMessageCallback.hpp
        ${INCLUDE_DIR}/Core/VertexArray.hpp
        ${INCLUDE_DIR}/Core/VertexBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.inl
        ${INCLUDE_DIR}/Core/IndexBuffer.hpp
        ${INCLUDE_DIR}/Core/Shader.hpp
        ${INCLUDE_DIR}/Core/Program.hpp
        ${INCLUDE_DIR}/Core/Texture.hpp


)

set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(TEST_FILES
        ${TEST_DIR}/SimpleTest.cpp
        ${TEST_DIR}/NotSimpleTest.cpp
        ${TEST_DIR}/TransformTest.cpp
)

add_executable(Sample
        ${SRC_FILES}
        ${SRC_DIR}/main.cpp
)
target_link_libraries(Sample
        SDL2::SDL2main # IDK what happens if we don't link SDL2main
        ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(Sample SYSTEM PRIVATE
        ${DEPENDENCY_INCLUDE_DIRS}
)
target_include_directories(Sample PRIVATE
        ${INCLUDE_DIR}
)
if (${PTSD_ENABLE_PCH})
    target_precompile_headers(Sample PRIVATE
            include/pch.hpp
    )
endif ()
target_compile_options(Sample PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)


enable_testing()

add_executable(Tests
        ${TEST_FILES}
        ${SRC_FILES}
)
target_link_libraries(Tests
        GTest::gtest_main
        ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(Tests SYSTEM PRIVATE
        ${DEPENDENCY_INCLUDE_DIRS}
        lib/googletest/googletest/include
        lib/googletest/googlemock/include
)
target_include_directories(Tests PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(Tests PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)

add_executable(AudioTest
        ${TEST_DIR}/Interactive/Audio.cpp
        ${SRC_FILES}
)
target_link_libraries(AudioTest
        GTest::gtest_main
        ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(AudioTest SYSTEM PRIVATE
        ${DEPENDENCY_INCLUDE_DIRS}
        lib/googletest/googletest/include
        lib/googletest/googlemock/include
)
target_include_directories(AudioTest PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(AudioTest PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)


include(GoogleTest)
gtest_discover_tests(Tests)
