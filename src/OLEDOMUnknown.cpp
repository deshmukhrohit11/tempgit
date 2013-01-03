//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "OLEDOMUnknown.h"

#include "com/quickoffice/common/formats/SerialIdConstants.h"
#include "com/quickoffice/dom/DOMObject.h"

using namespace std;
using namespace java;
using namespace java::lang;


namespace QO
{

JInt OLEDOMUnknown::m_serial_id =  (JInt)SerialIdConstants_DOM_OLEDOMUNKNOWN;

/* 
 * Default constructor used to construct OLEDOMUnknow object.
 * 
 * @param elementName
 * @param uri
 */
OLEDOMUnknown::OLEDOMUnknown(obj_ptr<java::lang::String > uri, obj_ptr<java::lang::String > elementName)
:	DOMUnknown(uri, elementName),
	oleObject()
{
}


/* 
 * @return the oleObject
 */
obj_ptr<java::lang::Object > OLEDOMUnknown::getOleObject()
{
	return obj_ptr<java::lang::Object >(oleObject);
}


/* 
 * @param oleObject the oleObject to set
 */
void OLEDOMUnknown::setOleObject(obj_ptr<java::lang::Object > oleObject)
{
	this->oleObject = oleObject;
}


/* 
 * Add child element for OLEDOMUnknown.
 * 
 * @param domObject
 */
void OLEDOMUnknown::add(obj_ptr<DOMObject > domObject)
{
	children->add(domObject);
}


JInt OLEDOMUnknown::getClassSerialId()
{
	return (m_serial_id);
}


JBool  OLEDOMUnknown::isInstanceOf(JInt serialId)
{
	if (m_serial_id == serialId)
	{
		return (true);
	}
	if (DOMUnknown::isInstanceOf(serialId))
	{
		return (true);
	}
	return (false);
}



} // QO

