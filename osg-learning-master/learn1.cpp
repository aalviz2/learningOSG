#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osgGA/TrackballManipulator>
#include <iostream>

int main()
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Geode> square = new osg::Geode();
	osg::ref_ptr<osg::Geometry> squareGeometry = new osg::Geometry();

	square->addDrawable(squareGeometry.get());
	root->addChild(square.get());

	osg::ref_ptr<osg::Vec3Array> sqVerts = new osg::Vec3Array();
	sqVerts->push_back(osg::Vec3(-10, 0, -10));
	sqVerts->push_back(osg::Vec3(1, 0, -1.0f));
	sqVerts->push_back(osg::Vec3(10, 0, 10));
	sqVerts->push_back(osg::Vec3(-1, 0, 1));

	squareGeometry->setVertexArray(sqVerts.get());

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
	colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

	squareGeometry->setColorArray(colors.get());
	squareGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
	squareGeometry->setNormalArray(n.get());
	squareGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	squareGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	if(root.valid())
	{
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
