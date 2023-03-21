
rock_find_qt4(OPTIONAL QtOpenGL)
rock_find_qt5(OPTIONAL Core OpenGL Widgets UiPlugin)

if (ROCK_QT_VERSION_4)
include(RockRuby)

QT4_ADD_RESOURCES(PROPERTY_BROWSER_RESOURCES qtpropertybrowser/qtpropertybrowser.qrc)

rock_library(vizkit3d
    SOURCES
        QtThreadedWidget.cpp
        NodeLink.cpp
        ColorConversionHelper.cpp
        GridNode.cpp
        TextureBox.cpp
        AxesNode.cpp
        OsgVisitors.cpp
        TransformerGraph.cpp
        CoordinateFrame.cpp
        DefaultManipulator.cpp
        EnableGLDebugOperation.cpp
        ${PROPERTY_BROWSER_RESOURCES} 
    MOC
        Vizkit3DPlugin.cpp 
        Vizkit3DWidget.cpp
        QVizkitMainWindow.cpp
        qtpropertybrowser/qteditorfactory.cpp
        qtpropertybrowser/qtvariantproperty.cpp
        qtpropertybrowser/qtpropertymanager.cpp
        qtpropertybrowser/qtbuttonpropertybrowser.cpp
        qtpropertybrowser/qtpropertybrowser.cpp
        qtpropertybrowser/qtpropertybrowserutils.cpp
        qtpropertybrowser/qttreepropertybrowser.cpp
        qtpropertybrowser/qtgroupboxpropertybrowser.cpp
        QPropertyBrowserWidget.cpp
        ${MOC_EXTRA}
    HEADERS
        TransformerGraph.hpp
        GridNode.hpp
        TextureBox.hpp
        NodeLink.hpp
        AxesNode.hpp
        OsgVisitors.hpp
        QtThreadedWidget.hpp
        Vizkit3DBase.hpp
        Vizkit3DPlugin.hpp
        Vizkit3DWidget.hpp
        QVizkitMainWindow.hpp
        ColorConversionHelper.hpp
        CoordinateFrame.hpp
        EnvPluginBase.hpp
        DefaultManipulator.hpp
        ${HEADERS_EXTRA}
    LIBS ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY}
    DEPS_CMAKE OpenGL
    DEPS_PKGCONFIG openscenegraph openscenegraph-osgQt osgViz
                   PrimitivesFactory ManipulationClickHandler ${DEPS_EXTRA})

rock_library(vizkitwidgetloader
    MOC QVizkitWidgetLoader.cpp
    DEPS vizkit3d
    NOINSTALL) # installs in a non-standard location
#rock_library(vizkitmainwindowloader
#    MOC QVizkitMainWindowLoader.cpp
#    DEPS vizkit3d
#    NOINSTALL) # installs in a non-standard location

endif()

if (ROCK_QT_VERSION_5)
find_package(QtPropertyBrowser REQUIRED)

pkg_check_modules(OSGQT QUIET osgQt)
pkg_check_modules(OPENSCENEGRAPH_OSGQT5 QUIET openscenegraph-osgQt5)

if(${OPENSCENEGRAPH_OSGQT5_FOUND})
  set(OSGQT_PKGCONFIG_NAME "openscenegraph-osgQt5")
elseif(${OSGQT_FOUND})
  set(OSGQT_PKGCONFIG_NAME "osgQt")
else()
  message(SEND_ERROR "Could not find osgQt or openscenegraph-osgQt5 with pkg-config")
endif()

rock_library(vizkit3d
    SOURCES
        QtThreadedWidget.cpp
        NodeLink.cpp
        ColorConversionHelper.cpp
        GridNode.cpp
        TextureBox.cpp
        AxesNode.cpp
        OsgVisitors.cpp
        TransformerGraph.cpp
        CoordinateFrame.cpp
        DefaultManipulator.cpp
        EnableGLDebugOperation.cpp
        Vizkit3DPlugin.cpp
        Vizkit3DWidget.cpp
        QVizkitMainWindow.cpp
        QPropertyBrowserWidget.cpp
    HEADERS
        QPropertyBrowserWidget.hpp

        TransformerGraph.hpp
        GridNode.hpp
        TextureBox.hpp
        NodeLink.hpp
        AxesNode.hpp
        OsgVisitors.hpp
        QtThreadedWidget.hpp
        Vizkit3DBase.hpp
        Vizkit3DPlugin.hpp
        Vizkit3DWidget.hpp
        QVizkitMainWindow.hpp
        ColorConversionHelper.hpp
        CoordinateFrame.hpp
        EnvPluginBase.hpp
        DefaultManipulator.hpp
    DEPS_TARGET
# QtPropertyBrowser properly sets up its target, fails to setup the plain
# cmake variables(thus cannot be used with DEPS_CMAKE) and does not have a
# pkg-config file(cannot be used with DEPS_PKGCONFIG).
        QtPropertyBrowser
    LIBS
# Qt has proper targets so potentially could be used with DEPS_TARGET, but
# it also provides proper pkg-config files, that are prefered there. Here,
# we have the qt dependencies hardcoded into the .pc.in and use the cmake
# targets for the cmake side.
        Qt5::Core
        Qt5::Widgets
        Qt5::OpenGL
        Qt5::UiPlugin
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
    DEPS_PKGCONFIG
        osgViz
        ${OSGQT_PKGCONFIG_NAME}
        ManipulationClickHandler
)

rock_library(vizkitwidgetloader
    SOURCES
        QVizkitWidgetLoader.cpp
    DEPS
        vizkit3d
    NOINSTALL # installs in a non-standard location
)

rock_library(vizkitmainwindowloader
    SOURCES
        QVizkitMainWindowLoader.cpp
    DEPS
        vizkit3d
    NOINSTALL # installs in a non-standard location
)

install(TARGETS vizkitmainwindowloader
    LIBRARY DESTINATION lib/qt/designer
    ARCHIVE DESTINATION lib/qt/designer)

endif()

install(TARGETS vizkitwidgetloader #vizkitmainwindowloader
    LIBRARY DESTINATION lib/qt/designer
    ARCHIVE DESTINATION lib/qt/designer)
