#include <iostream>
#include <string>

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ref_ptr>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#ifndef OMEGALIB
	#include <osgViewer/Viewer>
#endif
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include <FirstPersonController.h>
#include "BuildingLoader.h"
#include "hud.h"
#include "StartMenu.h"

using namespace std;

char* filename;
osg::ref_ptr<osg::Node> genWorld(char* fname);
StartMenu *startMenu;
hud *mainHud;
osg::ref_ptr<osg::Group> root(new osg::Group);
osgViewer::Viewer viewer;

#ifdef OMEGALIB
#include <omega.h>
#include <omegaOsg/omegaOsg.h>

using namespace omega;
using namespace omegaOsg;

class VUICApplication: public EngineModule
{
	public:
		void initialize()
		{
			// Create and setup the omegalib osg integration module
			ModuleServices::addModule(new OsgModule()); 

			// Create an omegalib scene node and attach the root osg node to it. This is used to interact with the 
			// osg object through omegalib interactors.
			OsgSceneObject* oso = new OsgSceneObject(genWorld(filename).get());
			const AlignedBox3* bbox = oso->getBoundingBox();
			myOsg->setRootNode(oso->getTransformedNode());

			// Resize the entire scene
			myRoot = SceneNode::create("osgRoot");
			myRoot->addComponent(oso);
			myRoot->setScale(0.05f, 0.05f, 0.05f);
		}
	private:
		Ref<OsgModule> myOsg;
		Ref<SceneNode> myRoot;
};

// Omegalib main
int main(int argc, char** argv) 
{
	filename = argv[1];
	Application<VUICApplication> app("vuic");
	return omain(app, argc, argv);
}

#else

void startApplication()
{
	startMenu->hideAll();	
	
	osg::ref_ptr<osg::Node> groundRoot = genWorld(filename);
	root->addChild(groundRoot);

	osg::ref_ptr<FirstPersonController> controller = new FirstPersonController(&viewer);
    	viewer.setCameraManipulator(controller);

	// Add main HUD
    	mainHud = new hud(&viewer);
    	root->addChild(mainHud->_camera);

	// Set user position (aka camera)
	    osg::Vec3d eye( 0.0, -1.0, 0.0 );
	    osg::Vec3d center( 0.0, 0.0, 0.0 );
	    osg::Vec3d up( 0.0, 0.0, 90.0 );

	    viewer.getCameraManipulator()->setHomePosition(eye, center, up);
	    viewer.home();
}

int main(int argc, char** argv)
{
	viewer.setSceneData(root.get());
	filename = argv[1];	
	
	startMenu = new StartMenu(&viewer, startApplication);
	root->addChild(startMenu->_camera);


	if(root.valid())
	{	
		
		//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
		viewer.realize();
	
		while(!viewer.done())
		{
			viewer.frame();
			//update();
		}
	}
	else
	{
		std::cout << "Invalid Graph!" << std::endl;
	}
	
	return 0;
}
#endif

osg::ref_ptr<osg::Node> genWorld(char* fname)
{
	osg::ref_ptr<osg::Group> tempRoot = new osg::Group();

	osg::ref_ptr<osg::Geode> ground = new osg::Geode();
	ground->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 0, 0), 590, 695, .001)));

	osg::ref_ptr<osg::Texture2D> groundTex = new osg::Texture2D(osgDB::readImageFile("assets/uic.jpg"));
	ground->getOrCreateStateSet()->setTextureAttributeAndModes(0, groundTex.get());

	//root->addChild(ground.get());
	BuildingLoader* bl = new BuildingLoader(fname);
	bl->read();
	tempRoot->addChild(bl->getNodes());
	
	return tempRoot;
}
