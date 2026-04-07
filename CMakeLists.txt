cmake_minimum_required(VERSION 3.16)
project(ksnipsnip VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_MIN_VERSION "6.6.0")

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

add_subdirectory(src)

install(FILES org.kde.ksnipsnip.desktop DESTINATION share/applications)
