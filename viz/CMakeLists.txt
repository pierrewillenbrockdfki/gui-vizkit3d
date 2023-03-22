
rock_find_qt4(OPTIONAL)
rock_find_qt5(OPTIONAL Core)

set(VIZKIT3D_VIZ_SOURCES
    PluginLoader.cpp
    GridVisualization.cpp
    TextureBoxVisualization.cpp
    ModelVisualization.cpp
    )

set(VIZKIT3D_VIZ_MOC
    GridVisualization.hpp
    TextureBoxVisualization.hpp
    ModelVisualization.hpp
    PluginLoader.hpp
    )

set(VIZKIT3D_VIZ_HEADERS
    GridVisualization.hpp
    TextureBoxVisualization.hpp
    ModelVisualization.hpp
    )

if (ROCK_QT_VERSION_4)
rock_vizkit_plugin(vizkit3d-viz
    ${VIZKIT3D_VIZ_SOURCES}
    MOC ${VIZKIT3D_VIZ_MOC}
    DEPS vizkit3d
    HEADERS ${VIZKIT3D_VIZ_HEADERS}
)
endif()

if (ROCK_QT_VERSION_5)
rock_vizkit_plugin_qt5(vizkit3d-viz-qt5
    SOURCES ${VIZKIT3D_VIZ_SOURCES}
    MOC5    ${VIZKIT3D_VIZ_MOC}
    HEADERS ${VIZKIT3D_VIZ_HEADERS}
    DEPS
        vizkit3d-qt5
)
endif()
