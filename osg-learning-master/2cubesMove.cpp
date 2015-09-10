#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osgGA/TrackballManipulator>
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <math.h>

osg::PositionAttitudeTransform* c2;
float tTime = 0;

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

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
	colors->push_back(osg::Vec4(1, 0, 0, 1));
	colors->push_back(osg::Vec4(0, 1, 0, 1));
	colors->push_back(osg::Vec4(0, 0, 1, 1));
	colors->push_back(osg::Vec4(0, 0, 0, 1));
	colors->push_back(osg::Vec4(1, 1, 1, 1));
	colors->push_back(osg::Vec4(0, 1, 1, 1));
	colors->push_back(osg::Vec4(1, 1, 0, 1));
	colors->push_back(osg::Vec4(1, 0, 1, 1));

	cubeGeo->setColorArray(colors.get());
    cubeGeo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

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

void update(float fr)
{
	tTime += fr;
	c2->setPosition(osg::Vec3(100*cos(tTime), 0, 100*sin(tTime)));	
}

int main()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	osg::ref_ptr<osg::Geode> cube = makeHead();
	root->addChild(cube.get());
	
	c2 = new osg::PositionAttitudeTransform();

	root->addChild(c2);
	c2->addChild(cube.get());
	osg::Vec3 c2pos = osg::Vec3(100,0,100);
	c2->setPosition(c2pos);

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
			update(.005);
		}
	}
	else
	{
		std::cout << "Invalid Graph!" << std::endl;
	}
}
