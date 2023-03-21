
rock_find_qt4(OPTIONAL)
rock_find_qt5(OPTIONAL Core)

if (ROCK_QT_VERSION_4)
rock_vizkit_plugin(vizkit3d-viz
    PluginLoader.cpp
    MOC GridVisualization.cpp TextureBoxVisualization.cpp ModelVisualization.cpp
    DEPS vizkit3d
    HEADERS GridVisualization.hpp TextureBoxVisualization.hpp ModelVisualization.hpp
)
endif()

if (ROCK_QT_VERSION_5)
rock_vizkit_plugin(vizkit3d-viz
    SOURCES
        PluginLoader.cpp
        GridVisualization.cpp
        TextureBoxVisualization.cpp
        ModelVisualization.cpp
    HEADERS
        GridVisualization.hpp
        TextureBoxVisualization.hpp
        ModelVisualization.hpp
    MOC
        GridVisualization.hpp
        TextureBoxVisualization.hpp
        ModelVisualization.hpp
        PluginLoader.hpp
    DEPS
        vizkit3d
)
endif()
