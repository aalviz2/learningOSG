#include "BuildingLoader.h"
#include <iostream>

using namespace std;

BuildingLoader::BuildingLoader(string filename)
{
	this->fname = filename;
	this->coords = *(new vector<pair<osg::Vec3, osg::Vec3> >());
}

void BuildingLoader::read()
{
	FILE* fil = fopen(this->fname.c_str(), "r");

	fseek(fil, 0, SEEK_END);	
	int size = ftell(fil);
	fseek(fil, 0, SEEK_SET);

	char buff[size];
	rapidjson::FileReadStream inStream(fil, buff, sizeof(buff));

	rapidjson::Document doc;
	doc.ParseStream(inStream);
	fclose(fil);

	for(unsigned int i = 0; i < doc.Size(); i++)
	{
		this->coords.push_back(
			pair<osg::Vec3, osg::Vec3>(
				osg::Vec3(
					doc[i]["location"][0].GetInt(), 
					doc[i]["location"][1].GetInt(), 
					doc[i]["location"][2].GetInt() 
				),
			  	osg::Vec3(
					doc[i]["x"].GetInt(),
					doc[i]["y"].GetInt(),
					doc[i]["z"].GetInt()
				)
			)
		);
	}
}

osg::ref_ptr<osg::Group> BuildingLoader::getNodes()
{
	osg::ref_ptr<osg::Group> ret = new osg::Group();
	
	for(unsigned int i = 0; i < this->coords.size(); i++)
	{
		osg::ref_ptr<osg::Geode> building = new osg::Geode();
		building->addDrawable(new osg::ShapeDrawable(new osg::Box(this->coords[i].first, this->coords[i].second[0], this->coords[i].second[1], this->coords[i].second[2])));
		ret->addChild(building.get());
	}

	return ret;
}

vector<pair<osg::Vec3, osg::Vec3> > BuildingLoader::getCoords()
{
	return this->coords;
}

string BuildingLoader::toString()
{
	stringstream res;
	for(unsigned int i = 0; i < this->coords.size(); i++)
	{
		res << "(" << (coords[i].first[0]) << ",";
		res << (coords[i].first[1]) << ",";
		res << (coords[i].first[2]) << ") (";
		res << (coords[i].second[0]) << ",";
		res << (coords[i].second[1]) << ",";
		res << (coords[i].second[2]) << ")\n";
	}

	return res.str();
}
