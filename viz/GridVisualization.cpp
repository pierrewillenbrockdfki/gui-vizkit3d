#include "GridVisualization.hpp"
#include "../src/GridNode.hpp"

namespace vizkit3d
{
    GridVisualization::GridVisualization(QObject *parent):
        vizkit3d::VizPluginBase(parent),
            grid_color(120,120,120,255),
            grid_rows(20),
            grid_cols(20),
            grid_dx(1),
            grid_dy(1),
            show_grid_coordinates(false)
    {
        setDirty();
    }

    void GridVisualization::updateMainNode(::osg::Node* node)
    {
        osg::Group *group = node->asGroup();
        if(!group)
            return;

        group->removeChildren(0,group->getNumChildren());
        osg::Vec4 color(1.0/255*grid_color.red(),
                1.0/255*grid_color.green(),
                1.0/255*grid_color.blue(),
                1.0/255*grid_color.alpha());

        ::osg::Node *grid= GridNode::create(grid_rows, grid_cols, grid_dx, grid_dy, show_grid_coordinates, color);
        group->addChild(grid);
    }

    bool GridVisualization::areCoordinatesShown()
    {
        return show_grid_coordinates;
    }
    int GridVisualization::getGridRows()
    {
        return grid_rows;
    }

    int GridVisualization::getGridCols()
    {
        return grid_cols;
    }

    double GridVisualization::getGridDx()
    {
        return grid_dx;
    }

    double GridVisualization::getGridDy()
    {
        return grid_dy;
    }

    QColor GridVisualization::getGridColor()
    {
        return grid_color;
    }

    void GridVisualization::setShowCoordinates(bool b)
    {
        show_grid_coordinates = b;
        setDirty();
    }

    void GridVisualization::setGridRows(int val)
    {
        if(val <= 0)
            return;
        grid_rows=val;
        setDirty();
    }

    void GridVisualization::setGridCols(int val)
    {
        if(val <= 0)
            return;
        grid_cols=val;
        setDirty();
    }

    void GridVisualization::setGridDx(double val)
    {
        if(val <= 0)
            return;
        grid_dx=val;
        setDirty();
    }

    void GridVisualization::setGridDy(double val)
    {
        if(val <= 0)
            return;
        grid_dy=val;
        setDirty();
    }

    void GridVisualization::setGridColor(QColor color)
    {
        grid_color=color;
        setDirty();
    }
}
