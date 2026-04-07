set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(ksnipsnip-helper
    main.cpp
    snipper.cpp
    snipper.h
    cropwindow.cpp
    cropwindow.h
)

target_link_libraries(ksnipsnip-helper
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS ksnipsnip-helper DESTINATION bin)
