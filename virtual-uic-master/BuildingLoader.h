#ifndef BUILDINGLOADER_H
#define BUILDINGLOADER_H

#include <string>
#include <utility>
#include <fstream>
#include <osg/Vec3>
#include <osg/Group>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class BuildingLoader
{
	public:
		BuildingLoader(std::string);
		void read();
		std::vector<std::pair<osg::Vec3, osg::Vec3> > getCoords();
		osg::ref_ptr<osg::Group> getNodes();
		std::string toString();

	private:
		std::string fname;
		std::vector<std::pair<osg::Vec3, osg::Vec3> > coords;
};

#endif
