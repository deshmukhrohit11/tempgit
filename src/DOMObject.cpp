//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "DOMObject.h"

#include "com/quickoffice/common/utils/UnmappedObjects.h"
#include "com/quickoffice/common/formats/SerialIdConstants.h"
#include "com/quickoffice/ood/formats/Namespace.h"
#include "com/quickoffice/common/Properties.h"

using namespace std;
using namespace java;
using namespace java::lang;

using java::util::List;

namespace QO
{

JInt DOMObject::m_serial_id =  (JInt)SerialIdConstants_DOM_DOMOBJECT;
obj_ptr<java::lang::String > DOMObject::ATTRIBUTE_VALUE = new String(std::wstring(L"val"));
obj_ptr<java::lang::String > DOMObject::ATTRIBUTE_NAME = new String(std::wstring(L"name"));
obj_ptr<java::lang::String > DOMObject::ATTRIBUTE_VALUE_WITH_NS = new String(std::wstring(L"w:val"));
obj_ptr<java::lang::String > DOMObject::ATTRIBUTE_NAME_WITH_NS = new String(std::wstring(L"w:name"));
obj_ptr<java::lang::String > DOMObject::ATTRIBUTE_VALUE_WITH_MATH_NS = new String(std::wstring(L"m:val"));

/* 
 * Default Generated Constructor
 */
DOMObject::DOMObject()
:	ns(),
	elementName(),
	unmappedObjects(),
	unknownAttributes(),
	unknownChildren()
{
}


void DOMObject::getValuesForKeysWithProperties(obj_ptr<Properties > properties)
{
}


void DOMObject::setValuesForKeysWithProperties(obj_ptr<Properties > properties)
{
}


/* 
 * @return the ns
 */
obj_ptr<Namespace > DOMObject::getNs()
{
	return obj_ptr<Namespace >(ns);
}


/* 
 * @param ns the ns to set
 */
void DOMObject::setNs(obj_ptr<Namespace > ns)
{
	this->ns = ns;
}


/* 
 * @param elementName the elementName to set
 */
void DOMObject::setElementName(obj_ptr<java::lang::String > elementName)
{
	this->elementName = elementName;
}


/* 
 * @return the elementName
 */
obj_ptr<java::lang::String > DOMObject::getElementName()
{
	return obj_ptr<java::lang::String >(elementName);
}


/* 
 * @return the unmappedObjects
 */
obj_ptr<UnmappedObjects > DOMObject::getUnmappedObjects()
{
	if (__NULL_VALUE == unmappedObjects)
	{
		if (__NULL_VALUE == unmappedObjects)
		{
			unmappedObjects = obj_ptr<UnmappedObjects >( new UnmappedObjects());
		}
	}
	return obj_ptr<UnmappedObjects >(unmappedObjects);
}


/* 
 * @return the unknownAttributes
 */
obj_ptr<java::lang::String > DOMObject::getUnknownAttributes()
{
	return obj_ptr<java::lang::String >(unknownAttributes);
}


/* 
 * @param unknownAttributes the unknownAttributes to set
 */
void DOMObject::setUnknownAttributes(obj_ptr<java::lang::String > unknownAttributes)
{
	this->unknownAttributes = unknownAttributes;
}


/* 
 * Sets the XMLNS attribute for this DOMObject. As of now only Relationships and Types are using this method because
 * the objects of this class are created in OODWriter and the xmlns attribute is lost. So when these objects are
 * created the xmlns attribute are set using this method. It ultimately calls the setUnknownAttributes because we
 * save the xmlns attributes as the unknownAttributes.
 * 
 * @param xmlnsAttribute - the xmlns attribute
 */
void DOMObject::setXMLNSAttribute(obj_ptr<java::lang::String > xmlnsAttribute)
{
	setUnknownAttributes(xmlnsAttribute);
}


/* 
 * @return the unknownChildren
 */
obj_ptr<java::util::List<obj_ptr<DOMObject > > > DOMObject::getUnknownChildren()
{
	return obj_ptr<java::util::List<obj_ptr<DOMObject > > >(unknownChildren);
}


/* 
 * @param unknownChildren the unknownChildren to set
 */
void DOMObject::setUnknownChildren(obj_ptr<java::util::List<obj_ptr<DOMObject > > > unknownChildren)
{
	this->unknownChildren = unknownChildren;
}


JInt DOMObject::getClassSerialId()
{
	return (m_serial_id);
}


JBool  DOMObject::isInstanceOf(JInt serialId)
{
	if (m_serial_id == serialId)
	{
		return (true);
	}
	if (DOMHelper::isInstanceOf(serialId))
	{
		return (true);
	}
	if (IKeyValueCoding::isInstanceOf(serialId))
	{
		return (true);
	}
	return (false);
}



} // QO

