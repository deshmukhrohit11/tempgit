//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "DOMRootObject.h"

#include "com/quickoffice/common/formats/SerialIdConstants.h"
#include "com/quickoffice/common/Properties.h"

using namespace std;
using namespace java;
using namespace java::lang;


namespace QO
{

JInt DOMRootObject::m_serial_id =  (JInt)SerialIdConstants_DOM_DOMROOTOBJECT;
obj_ptr<java::lang::String > DOMRootObject::ATTRIBUTE_IGNORABLE = new String(std::wstring(L"mc:Ignorable"));
obj_ptr<java::lang::String > DOMRootObject::ATTRIBUTE_PRESERVE_ATTRIBUTES = new String(std::wstring(L"mc:PreserveAttributes"));

/* 
 * Default Generated Constructor
 */
DOMRootObject::DOMRootObject()
:	ignorable(),
	preserveAttributes()
{
}


void DOMRootObject::getValuesForKeysWithProperties(obj_ptr<Properties > properties)
{
	setMandatoryPropertyValue(properties,ATTRIBUTE_IGNORABLE,getIgnorable());
	setMandatoryPropertyValue(properties,ATTRIBUTE_PRESERVE_ATTRIBUTES,getPreserveAttributes());
}


void DOMRootObject::setValuesForKeysWithProperties(obj_ptr<Properties > properties)
{
	if (__NULL_VALUE != properties)
	{
		setIgnorable(properties->getProperty(ATTRIBUTE_IGNORABLE));
		setPreserveAttributes(properties->getProperty(ATTRIBUTE_PRESERVE_ATTRIBUTES));
	}
}


/* 
 * @return the ignorable
 */
obj_ptr<java::lang::String > DOMRootObject::getIgnorable()
{
	return obj_ptr<java::lang::String >(ignorable);
}


/* 
 * @param ignorable the ignorable to set
 */
void DOMRootObject::setIgnorable(obj_ptr<java::lang::String > ignorable)
{
	this->ignorable = ignorable;
}


/* 
 * @return the preserveAttributes
 */
obj_ptr<java::lang::String > DOMRootObject::getPreserveAttributes()
{
	return obj_ptr<java::lang::String >(preserveAttributes);
}


/* 
 * @param preserveAttributes the preserveAttributes to set
 */
void DOMRootObject::setPreserveAttributes(obj_ptr<java::lang::String > preserveAttributes)
{
	this->preserveAttributes = preserveAttributes;
}


JInt DOMRootObject::getClassSerialId()
{
	return (m_serial_id);
}


JBool  DOMRootObject::isInstanceOf(JInt serialId)
{
	if (m_serial_id == serialId)
	{
		return (true);
	}
	if (DOMObject::isInstanceOf(serialId))
	{
		return (true);
	}
	return (false);
}



} // QO

