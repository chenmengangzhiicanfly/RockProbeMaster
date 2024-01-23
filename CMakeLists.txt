cmake_minimum_required(VERSION 3.5)

project(RockProbeMaster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# opencv
set(OpenCV_DIR E:/rockprobe/opencv/build)
find_package(OpenCV REQUIRED)
#message(STATUS  "OpenCV library status:")
#message(STATUS "    version: ${OpenCV_VERSION}")
#message(STATUS "    libraries: ${OpenCV_LIBS}")
#message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Qt6 REQUIRED COMPONENTS Multimedia)


# setup CUDA
find_package(CUDA REQUIRED)
#message(STATUS "    libraries: ${CUDA_LIBRARIES}")
#message(STATUS "    include path: ${CUDA_INCLUDE_DIRS}")
include_directories(${CUDA_INCLUDE_DIRS})
enable_language(CUDA)

#tensorrt
set(TRT_DIR "E:/4060deepsort/TensorRT-8.6.1.6")



#5.设置Eigen路径,我用的是Eigen-3.3.9.zip(set the path of Eigen)
set(Eigen3_PATH E:/4060deepsort/eigen-3.4.0)
#6.设置dirent路径(set the path of Dirent, download it from https://codeload.github.com/tronkko/dirent/zip/refs/heads/master)
set(Dirent_INCLUDE_DIRS "E:/4060deepsort/dirent-master/include") #11

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS AxContainer)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)

add_subdirectory(QXlsx)


include_directories(${TRT_DIR}/include)
include_directories(F:/QTProject/02_project/count/Include)

include_directories(
        ${Eigen3_PATH}
        ${Dirent_INCLUDE_DIRS}
)

link_directories(F:/QTProject/02_project/count/Lib)

link_directories(${TRT_DIR}/lib)
link_directories(${OpenCV_LIB_DIRS})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RockProbeMaster
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        RockProbeMaster.qrc
        "rockprobe.rc"


        form.h form.cpp form.ui
        registerwidget.h registerwidget.cpp registerwidget.ui
        registerwidget.cpp registerwidget.h registerwidget.ui
        loginwidget.h loginwidget.cpp loginwidget.ui
        excelreaderanddisplayer.h excelreaderanddisplayer.cpp excelreaderanddisplayer.ui
        databaseconnector.h databaseconnector.cpp
        databaseinsertpage.h databaseinsertpage.cpp databaseinsertpage.ui
        excelexporter.h excelexporter.cpp
        excelimporter.h excelimporter.cpp
        test.h test.cpp
        videoreviewwidget.h videoreviewwidget.cpp videoreviewwidget.ui
        detectormanagersingleton.h detectormanagersingleton.cpp videoreviewslots.cpp
        workspacefilemanager.h workspacefilemanager.cpp workspacefilemanager.ui
        workspaceopener.h workspaceopener.cpp workspaceopener.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RockProbeMaster APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RockProbeMaster SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RockProbeMaster
            ${PROJECT_SOURCES}
            "rockprobe.rc"
        )
    endif()
endif()





target_link_libraries(RockProbeMaster PRIVATE nvinfer nvinfer_plugin
nvinfer_dispatch nvinfer_lean nvonnxparser nvinfer_vc_plugin nvparsers)
#target_link_libraries(RockProbeMaster PRIVATE nvinfer nvonnxparser)
target_link_libraries(RockProbeMaster PRIVATE deepsort.lib yolosort.lib yolov5_trt.lib)
target_link_libraries(RockProbeMaster PRIVATE Qt6::Sql)
target_link_libraries(RockProbeMaster PRIVATE Qt6::AxContainer)
target_link_libraries(RockProbeMaster PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(RockProbeMaster PRIVATE QXlsx::QXlsx)

target_link_libraries(RockProbeMaster PRIVATE ${OpenCV_LIBS})
target_link_libraries(RockProbeMaster PRIVATE ${CUDA_LIBRARIES})
target_link_libraries(RockProbeMaster PRIVATE Qt6::Multimedia)
target_link_libraries(RockProbeMaster PRIVATE Qt6::MultimediaWidgets)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RockProbeMaster)
endif()
set_target_properties(RockProbeMaster PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RockProbeMaster
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RockProbeMaster)
endif()
