cmake_minimum_required(VERSION 3.10)

project(my_app)

# 定义 dev 变量，可通过 -Ddev=ON 或 set(dev ON) 开启
option(dev "Build as executable instead of DLL" ON)

if(NOT TARGET SDL3::SDL3)
    find_package(SDL3 CONFIG REQUIRED)
endif()

if(dev)
    # dev 模式：生成 exe
    add_executable(main
        main.c
        scenes/main_scene/index.c
        scenes/test_scene/index.c
        engine/image/index.c
        engine/music/index.c
    )
    target_link_libraries(main PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        # SDL3_ttf::SDL3_ttf
    )
    target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    # 将 sdl3.dll 复制到 exe 输出目录
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:main>"
        COMMENT "Copying SDL3.dll to output directory"
    )
    # 将 sdl3_image.dll 复制到 exe 输出目录
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_image::SDL3_image>"
            "$<TARGET_FILE_DIR:main>"
        COMMENT "Copying SDL3_image.dll to output directory"
    )
    # 将 sdl3_mixer.dll 复制到 exe 输出目录
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3_mixer::SDL3_mixer>"
            "$<TARGET_FILE_DIR:main>"
        COMMENT "Copying SDL3_mixer.dll to output directory"
    )
    # 将 assets 目录复制到 exe 输出目录
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:main>/assets"
        COMMENT "Copying assets to output directory"
    )
else()
    # 默认模式：生成 dll
    add_library(main SHARED
        main.c
        scenes/main_scene/index.c
        scenes/test_scene/index.c
    )
    target_link_libraries(main PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        # SDL3_ttf::SDL3_ttf
    )
    target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()