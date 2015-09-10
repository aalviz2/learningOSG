#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osg/Texture2D>
#include <osg/StateSet>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <iostream>
#include <osg/PositionAttitudeTransform>

osg::ref_ptr<osg::Geode> makeHead()
{
	osg::ref_ptr<osg::Geode> cube = new osg::Geode();

	osg::ref_ptr<osg::Geometry> cubeGeo = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> cubeVerts = new osg::Vec3Array();
	cubeVerts->push_back(osg::Vec3(-5, 0, 10));
	cubeVerts->push_back(osg::Vec3(5, 0, 10));
	cubeVerts->push_back(osg::Vec3(-5, 0, 0));
	cubeVerts->push_back(osg::Vec3(5, 0, 0));
	cubeVerts->push_back(osg::Vec3(-5, 10, 10));
	cubeVerts->push_back(osg::Vec3(5, 10, 10));
	cubeVerts->push_back(osg::Vec3(-5, 10, 0));
	cubeVerts->push_back(osg::Vec3(5, 10, 0));

	cubeGeo->setVertexArray(cubeVerts.get());

	osg::Vec2Array* texes = new osg::Vec2Array();
	texes->push_back(osg::Vec2(0, 0));
	texes->push_back(osg::Vec2(0, 1));
	texes->push_back(osg::Vec2(1, 0));
	texes->push_back(osg::Vec2(1, 1));
	texes->push_back(osg::Vec2(0, 0));
	texes->push_back(osg::Vec2(0, 1));
	texes->push_back(osg::Vec2(1, 0));
	texes->push_back(osg::Vec2(1, 1));

	cubeGeo->setTexCoordArray(0, texes);

	osg::DrawElementsUInt* top = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	top->push_back(0);
	top->push_back(1);
	top->push_back(5);
	top->push_back(4);
	cubeGeo->addPrimitiveSet(top);

	osg::DrawElementsUInt* bottom = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	bottom->push_back(2);
	bottom->push_back(3);
	bottom->push_back(7);
	bottom->push_back(6);
	cubeGeo->addPrimitiveSet(bottom);

	osg::DrawElementsUInt* side1 = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	side1->push_back(0);
	side1->push_back(2);
	side1->push_back(6);
	side1->push_back(4);
	cubeGeo->addPrimitiveSet(side1);

	osg::DrawElementsUInt* side2 = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	side2->push_back(1);
	side2->push_back(3);
	side2->push_back(7);
	side2->push_back(5);
	cubeGeo->addPrimitiveSet(side2);

	osg::DrawElementsUInt* side4 = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	side4->push_back(4);
	side4->push_back(5);
	side4->push_back(7);
	side4->push_back(6);
	cubeGeo->addPrimitiveSet(side4);

	osg::DrawElementsUInt* side3 = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	side3->push_back(0);
	side3->push_back(1);
	side3->push_back(3);
	side3->push_back(2);
	cubeGeo->addPrimitiveSet(side3);

	cube->addDrawable(cubeGeo.get());
	
	return cube;
}
int main()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	osg::ref_ptr<osg::Geode> cube = makeHead();
	root->addChild(cube.get());
	
	osg::PositionAttitudeTransform* c2 = new osg::PositionAttitudeTransform();

	root->addChild(c2);
	c2->addChild(cube.get());
	osg::Vec3 c2pos = osg::Vec3(20,0,0);
	c2->setPosition(c2pos);

	osg::Texture2D* texture = new osg::Texture2D();
	texture->setDataVariance(osg::Object::DYNAMIC);

	osg::Image* img = osgDB::readImageFile("assets/pumice.jpg");
	if(!img)
	{
		std::cout << "No such image file." << std::endl;
		return -1;
	}

	texture->setImage(img);

	osg::StateSet* texState = new osg::StateSet();
	texState->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	cube->setStateSet(texState);

	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

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
}
