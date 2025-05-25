cmake_minimum_required(VERSION 3.14)

project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt modules
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    TextToSpeech
    Sql
)

# Add executable and source files
set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(FORMS
    mainwindow.ui
)

set(RESOURCES
    Resources.qrc
)

qt5_wrap_ui(UI_HEADERS ${FORMS})
qt5_add_resources(RESOURCE_FILES ${RESOURCES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::TextToSpeech
    Qt5::Sql
)

# Icon for Windows
if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "pngaaa.com-1524756.ico")
    target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
endif()

# Install target
if(UNIX AND NOT ANDROID)
    set(INSTALL_PATH /opt/${PROJECT_NAME}/bin)
elseif(QNX)
    set(INSTALL_PATH /tmp/${PROJECT_NAME}/bin)
endif()

if(INSTALL_PATH)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_PATH})
endif()

