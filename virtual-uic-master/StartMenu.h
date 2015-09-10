#ifndef STARTMENU_H
#define STARTMENU_H

#include <osgWidget/WindowManager>
#include <osgWidget/Util>
#include <osgWidget/Box>
#include <osgWidget/Label>
#include <osg/Camera>
#include <osgViewer/Viewer>
#include <osgWidget/ViewerEventHandlers>
#include <iostream>
#include <memory>

const unsigned int MASK_2D = 0xF0000000;

struct ColorLabel : public osgWidget::Label
{
    ColorLabel(const char* label):
    osgWidget::Label("", "")
    {
        setFontSize(50);
        setFontColor(1.0f, 1.0f, 1.0f, 1.0f);
        setColor(0.3f, 0.3f, 0.3f, 1.0f);
        //addHeight(18.0f);
        setCanFill(true);
        setLabel(label);
        setEventMask(osgWidget::EVENT_MOUSE_PUSH | osgWidget::EVENT_MASK_MOUSE_MOVE);
    }

    bool mousePush(double, double, const osgWidget::WindowManager *)
    {
        return true;
    }

    bool mouseEnter(double, double, const osgWidget::WindowManager *)
    {
        setColor(0.6f, 0.6f, 0.6f, 1.0f);

        return true;
    }

    bool mouseLeave(double, double, const osgWidget::WindowManager *)
    {
        setColor(0.3f, 0.3f, 0.3f, 1.0f);

        return true;
    }
};

class StartMenu
{
//void (*actualStartCallback)(void);

public:
    osg::Camera *_camera;

    StartMenu(osgViewer::Viewer *inputViewer, void (*p)(void));

    void hideAll();
    void showAll();


protected:
    osgViewer::Viewer *_viewer;
    osgWidget::Window *titleWindow;
    osgWidget::Window *menuWindow;
};


class ColorLabelMenu : public ColorLabel
{
    osg::ref_ptr<osgWidget::Window> _window;
    std::string windowLabel;

    void (*startCallback)(void);

public:
    ColorLabelMenu(const char *label):
    ColorLabel(label)
    {
        windowLabel = label;
        _window = new osgWidget::Box(std::string("Menu_") + label,
                                     osgWidget::Box::HORIZONTAL, true);

        _window->resize();

        setColor(0.8f, 0.8f, 0.8f, 0.8f);
    }

    ColorLabelMenu(const char *label, void (*p)(void)):
    ColorLabel(label)
    {
        windowLabel = label;
        _window = new osgWidget::Box(std::string("Menu_") + label,
                                     osgWidget::Box::HORIZONTAL, true);

        _window->resize();

        setColor(0.8f, 0.8f, 0.8f, 0.8f);

        startCallback = p;
    }

    void managed(osgWidget::WindowManager *wm)
    {
        osgWidget::Label::managed(wm);

        wm->addChild(_window.get());

        _window->hide();
    }

    bool mousePush(double, double, const osgWidget::WindowManager *)
    {
        if (windowLabel == "Exit")
        {
            exit(0);
        }
        else if (windowLabel == "Start")
        {
            startCallback();
        }

        return true;
    }

    bool mouseLeave(double, double, const osgWidget::WindowManager *)
    {
        setColor(0.8f, 0.8f, 0.8f, 0.8f);

        return true;
    }
};

#endif // STARTMENU_H
