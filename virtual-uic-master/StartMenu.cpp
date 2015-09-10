#include "StartMenu.h"

StartMenu::StartMenu(osgViewer::Viewer *inputViewer, void (*p)(void))
{
    _viewer = inputViewer;

    // Get screen details
    osg::GraphicsContext::WindowingSystemInterface *wsi =
            osg::GraphicsContext::getWindowingSystemInterface();
    unsigned int screenWidth, screenHeight;
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), screenWidth, screenHeight);

    osgWidget::WindowManager *wm = new osgWidget::WindowManager(_viewer, screenWidth, screenHeight, MASK_2D);

    titleWindow = new osgWidget::Box("title", osgWidget::Box::VERTICAL);
    menuWindow = new osgWidget::Box("menu", osgWidget::Box::HORIZONTAL);

    osgWidget::Label *title = new osgWidget::Label("", "");
    title->setWidth(520);
    title->setLabel("Virtual UIC");
    title->setFontSize(64);
    title->setShadow(0.1f);

    osgWidget::Label *creators = new osgWidget::Label("", "");
    creators->setHeight(100);
    creators->setLabel("Created by UIC VRUPL");
    creators->setFontSize(32);
    creators->setShadow(0.1f);

    titleWindow->setOrigin((screenWidth/2) - (title->getWidth()/2), (screenHeight/2) - (title->getHeight()/2));

    titleWindow->addWidget(creators);
    titleWindow->addWidget(title);

    //actualStartCallback = p;

    menuWindow->addWidget(new ColorLabelMenu("Start", p));
    menuWindow->addWidget(new ColorLabelMenu("Exit"));

    wm->addChild(titleWindow);
    wm->addChild(menuWindow);

    titleWindow->getBackground()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
    titleWindow->resizePercent(100.0f);
    menuWindow->getBackground()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
    menuWindow->resizePercent(100.0f);

    _viewer->setUpViewInWindow(1000, 1000, screenWidth, screenHeight);
    _camera = wm->createParentOrthoCamera();

    // Handle Input for Menu
    _viewer->addEventHandler(new osgWidget::MouseHandler(wm));
    _viewer->addEventHandler(new osgWidget::KeyboardHandler(wm));
}

void StartMenu::hideAll()
{
    titleWindow->hide();
    menuWindow->hide();
}

void StartMenu::showAll()
{
    titleWindow->show();
    menuWindow->show();
}














