/**********************************************************************
 *
 *	FILE:			Group.cpp
 *
 *	DESCRIPTION:	Read/Write osg::Group in binary format to disk.
 *
 *	CREATED BY:		Auto generated by iveGenerated
 *					and later modified by Rune Schmidt Jensen.
 *
 *	HISTORY:		Created 17.3.2003
 *
 *	Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "Node.h"
#include "Group.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "LightSource.h"
#include "Billboard.h"
#include "Sequence.h"
#include "LOD.h"
//#include "ViewPoint.h"
#include "PositionAttitudeTransform.h"
#include "Transform.h"

using namespace ive;

void Group::write(DataOutputStream* out){
	// Write Group's identification.
	out->writeInt(IVEGROUP);
	// If the osg class is inherited by any other class we should also write this to file.
	osg::Node* node = dynamic_cast<osg::Node*>(this);
	if(node){
		static_cast<ive::Node*>(node)->write(out);
	}
	else
		throw Exception("Group::write(): Could not cast this osg::Group to an osg::Node.");

	// Write Group's properties.

	// Write number of children.
	out->writeInt(getNumChildren());
	// Write children.
    for(unsigned int i=0; i<getNumChildren(); i++){
		osg::Node* child = getChild(i);
		if(dynamic_cast<osg::MatrixTransform*>(child)){
			((ive::MatrixTransform*)(child))->write(out);
		}
// 		else if(dynamic_cast<osgfIVE::ViewPoint*>(child)){
// 			((ive::ViewPoint*)(child))->write(out);
// 		}
		else if(dynamic_cast<osg::PositionAttitudeTransform*>(child)){
			((ive::PositionAttitudeTransform*)(child))->write(out);
		}
		else if(dynamic_cast<osg::LightSource*>(child)){
			((ive::LightSource*)(child))->write(out);
		}
		else if(dynamic_cast<osg::Sequence*>(child)){
			((ive::Sequence*)(child))->write(out);
		}
		else if(dynamic_cast<osg::LOD*>(child)){
			((ive::LOD*)(child))->write(out);
		}
		else if(dynamic_cast<osg::Transform*>(child)){
			((ive::Transform*)(child))->write(out);
		}
		else if(dynamic_cast<osg::Group*>(child)){
			((ive::Group*)(child))->write(out);
		}
		else if(dynamic_cast<osg::Billboard*>(child)){
			((ive::Billboard*)(child))->write(out);
		}
		else if(dynamic_cast<osg::Geode*>(child)){
			((ive::Geode*)(child))->write(out);
		}
		else
			throw Exception("Unknown child in Group::write()");
    }
}

void Group::read(DataInputStream* in){
	// Read Group's identification.
	int id = in->peekInt();
	if(id == IVEGROUP){
		// Read Group's identification.
		id = in->readInt();

		// If the osg class is inherited by any other class we should also read this from file.
		osg::Node* node = dynamic_cast<osg::Node*>(this);
		if(node){
			((ive::Node*)(node))->read(in);
		}
		else
			throw Exception("Group::read(): Could not cast this osg::Group to an osg::Node.");


		// Read groups properties.

		// Read number of children.
		int size = in->readInt();
		// Read children.
		for(int i=0; i<size; i++){
			int id = in->peekInt();
			osg::Node* child;
			if(id == IVEMATRIXTRANSFORM){
				child = new osg::MatrixTransform();
				((ive::MatrixTransform*)(child))->read(in);
				addChild(child);
			}
// 			else if(id == IVEVIEWPOINT){
// 				child = new osgfIVE::ViewPoint();
// 				((ive::ViewPoint*)(child))->read(in);
// 				addChild(child);
// 			}
			else if(id == IVEPOSITIONATTITUDETRANSFORM){
				child = new osg::PositionAttitudeTransform();
				((ive::PositionAttitudeTransform*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVELIGHTSOURCE){
				child = new osg::LightSource();
				((ive::LightSource*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVESEQUENCE){
				child = new osg::Sequence();
				((ive::Sequence*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVELOD){
				child = new osg::LOD();
				((ive::LOD*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVETRANSFORM){
				child = new osg::Transform();
				((ive::Transform*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVEGROUP){
				child = new osg::Group();
				((ive::Group*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVEBILLBOARD){
				child = new osg::Billboard();
				((ive::Billboard*)(child))->read(in);
				addChild(child);
			}
			else if(id == IVEGEODE){
				child = new osg::Geode();
				((ive::Geode*)(child))->read(in);
				addChild(child);
			}
			else{
				throw Exception("Unknown child identification in Group::read()");
			}
		}
	}
	else{
		throw Exception("Group::read(): Expected Group identification");
	}
}
