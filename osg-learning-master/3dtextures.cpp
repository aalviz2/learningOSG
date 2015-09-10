#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osg/Texture3D>
#include <osg/StateSet>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <iostream>
#include <osg/PositionAttitudeTransform>

int main()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::Node* battle_dino = osgDB::readNodeFile("assets/penta_castle_v4_ff.stl");



	root->addChild(battle_dino);

	if(root.valid())
	{	
		osgViewer::Viewer viewer;
		viewer.setSceneData(root);
		viewer.setCameraManipulator(new osgGA::TrackballManipulator());
		viewer.realize();
	
		while(!viewer.done())
		{
			viewer.frame();
		}
	}
	else
	{
		std::cout << "Invalid Graph!" << std::endl;
	}
	return 0;
}
