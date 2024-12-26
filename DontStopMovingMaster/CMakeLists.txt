cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
set(CMKAE_CXX_STANDARD_REQUIRED ON)

project(FasterQuicker VERSION 1.0)


set(SOURCES

DontStopMoving/Src/App/main.cpp
DontStopMoving/Src/Controller/Controller.cpp
DontStopMoving/Src/Controller/Controller.h
DontStopMoving/Src/Math/Rectangle.h
DontStopMoving/Src/Render/Window.cpp
DontStopMoving/Src/Render/Window.h
DontStopMoving/Src/Render/Text.cpp
DontStopMoving/Src/Render/Text.h
DontStopMoving/Src/Sounds/Sound.cpp
DontStopMoving/Src/Sounds/Sound.h
)

add_executable(FasterQuicker ${SOURCES})

add_custom_command(
    TARGET FasterQuicker  # Replace with your target name
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/DLL/SDL2.dll  # Source DLL
        ${PROJECT_BINARY_DIR}/Debug  # Destination directory
    COMMENT "Copying DLL to the build directory"
)

add_custom_command(
    TARGET FasterQuicker  # Replace with your target name
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/DLL/SDL2_image.dll  # Source DLL
        ${PROJECT_BINARY_DIR}/Debug  # Destination directory
    COMMENT "Copying DLL to the build directory"
)

add_custom_command(
    TARGET FasterQuicker  # Replace with your target name
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/DLL/SDL2_ttf.dll  # Source DLL
        ${PROJECT_BINARY_DIR}/Debug  # Destination directory
    COMMENT "Copying DLL to the build directory"
)

add_custom_command(
    TARGET FasterQuicker  # Replace with your target name
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/DLL/OpenAL32.dll  # Source DLL
        ${PROJECT_BINARY_DIR}/Debug  # Destination directory
    COMMENT "Copying DLL to the build directory"
)


target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} DontStopMoving/Src)
target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Deps/OPENAL/Include)
target_link_libraries(FasterQuicker PUBLIC Deps/OPENAL/Lib/OpenAL32)
target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Deps/LIBSND/Include)
target_link_libraries(FasterQuicker PUBLIC Deps/LIBSND/Lib/sndfile)
target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Deps/SDL/Include)
target_link_libraries(FasterQuicker PUBLIC Deps/SDL/lib/x64/SDL2)
target_link_libraries(FasterQuicker PUBLIC Deps/SDL/lib/x64/SDL2main)
target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Deps/SDLImage/Include)
target_link_libraries(FasterQuicker PUBLIC Deps/SDLImage/lib/x64/SDL2_image)
target_include_directories(FasterQuicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Deps/SDLText/Include)
target_link_libraries(FasterQuicker PUBLIC Deps/SDLText/lib/x64/SDL2_ttf)