#include "hud.h"

hud::hud(osgViewer::Viewer *inputViewer)
{
    _viewer = inputViewer;

    // Get screen details
    osg::GraphicsContext::WindowingSystemInterface *wsi =
            osg::GraphicsContext::getWindowingSystemInterface();
    unsigned int screenWidth, screenHeight;
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), screenWidth, screenHeight);

    osgWidget::WindowManager *wm = new osgWidget::WindowManager(_viewer, screenWidth, screenHeight, 0xF0000000);

    labelWindow = new osgWidget::Box("title", osgWidget::Box::VERTICAL);
    menuWindow = new osgWidget::Box("menu", osgWidget::Box::HORIZONTAL);

    osgWidget::Label *mainLabel = new osgWidget::Label("", "");
    mainLabel->setWidth(520);
    mainLabel->setLabel("Welcome!");
    mainLabel->setFontSize(64);
    mainLabel->setShadow(0.1f);


    labelWindow->setOrigin((screenWidth/2) - (mainLabel->getWidth()/2), (screenHeight/2) - (mainLabel->getHeight()/2));
    labelWindow->addWidget(mainLabel);

    menuWindow->addWidget(new CustomLabelMenu("Locations"));
    menuWindow->addWidget(new CustomLabelMenu("Exit"));

    wm->addChild(labelWindow);
    wm->addChild(menuWindow);

    labelWindow->getBackground()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
    labelWindow->resizePercent(100.0f);
    menuWindow->getBackground()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
    menuWindow->resizePercent(60.0f);

    _camera = wm->createParentOrthoCamera();

    // Handle Input for Menu
    _viewer->addEventHandler(new osgWidget::MouseHandler(wm));
    _viewer->addEventHandler(new osgWidget::KeyboardHandler(wm));
}
