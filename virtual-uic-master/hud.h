#ifndef HUD_H
#define HUD_H

#include <osgWidget/WindowManager>
#include <osgWidget/Util>
#include <osgWidget/Box>
#include <osgWidget/Label>
#include <osg/Camera>
#include <osgViewer/Viewer>
#include <osgWidget/ViewerEventHandlers>
#include <iostream>
#include <memory>

struct CustomLabel : public osgWidget::Label
{
    std::string windowLabel;

    CustomLabel(const char* label):
    osgWidget::Label("", "")
    {
        windowLabel = label;

        setFontSize(32);
        setFontColor(1.0f, 1.0f, 1.0f, 1.0f);
        setColor(0.3f, 0.3f, 0.3f, 1.0f);
        addHeight(18.0f);
        setCanFill(true);
        setLabel(label);
        setEventMask(osgWidget::EVENT_MOUSE_PUSH | osgWidget::EVENT_MASK_MOUSE_MOVE);
    }

    // Location selection logic
    bool mousePush(double, double, const osgWidget::WindowManager *)
    {
        if (windowLabel == "Student Center East (SCE)")
        {
            exit(0);
        }

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


class CustomLabelMenu : public CustomLabel
{
    osg::ref_ptr<osgWidget::Window> _window;
    std::string windowLabel;

    void (*startCallback)(void);

public:
    CustomLabelMenu(const char *label):
    CustomLabel(label)
    {
        windowLabel = label;
        _window = new osgWidget::Box(std::string("Menu_") + label,
                                     osgWidget::Box::VERTICAL, true);

        _window->addWidget(new CustomLabel("Student Center East (SCE)"));
        _window->addWidget(new CustomLabel("Lecture Center A (LCA)"));
        _window->addWidget(new CustomLabel("Burnham Hall (BH)"));

        _window->resize();

        setColor(0.8f, 0.8f, 0.8f, 0.8f);
    }

    void managed(osgWidget::WindowManager *wm)
    {
        osgWidget::Label::managed(wm);

        wm->addChild(_window.get());

        _window->hide();
    }

    void positioned()
    {
        osgWidget::Label::positioned();

        _window->setOrigin(getX(), getHeight());
        _window->resize(getWidth());
    }

    bool mousePush(double, double, const osgWidget::WindowManager *)
    {
        if (windowLabel == "Locations")
        {
            if (!_window->isVisible())
            {
                _window->show();

            }
            else
            {
                _window->hide();
            }
        }


        if (windowLabel == "Exit")
        {
            _window->hide();
            exit(0);
        }

        return true;
    }

    bool mouseLeave(double, double, const osgWidget::WindowManager *)
    {
        setColor(0.8f, 0.8f, 0.8f, 0.8f);

        return true;
    }
};

class hud
{
public:
    osg::Camera *_camera;

    hud(osgViewer::Viewer *inputViewer);

    void hideAll();
    void showAll();


protected:
    osgViewer::Viewer *_viewer;
    osgWidget::Window *labelWindow;
    osgWidget::Window *menuWindow;
};

#endif // HUD_H
