//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "DOMUnknown.h"

#include "com/quickoffice/ood/formats/shared/SharedVisitor.h"
#include "com/quickoffice/dom/shared/Relationship.h"
#include "com/quickoffice/common/formats/SerialIdConstants.h"
#include "com/quickoffice/common/utils/QOConstants.h"
#include "com/quickoffice/common/formats/BaseReader.h"
#include "com/quickoffice/common/Properties.h"

using namespace std;
using namespace java;
using namespace java::lang;

using org::xml::sax::Attributes;
using java::util::Map;
using java::util::HashMap;
using org::xml::sax::Locator;
using java::util::ArrayList;
using java::util::List;




namespace QO
{

JInt DOMUnknown::m_serial_id =  (JInt)SerialIdConstants_DOM_DOMUNKNOWN;

/* 
 * Default constructor with no arguments. It initializes all the members.
 */
DOMUnknown::DOMUnknown()
:	uri(),
	localName(),
	qName(),
	column(JInt(0)),
	row(JInt(0)),
	publicId(),
	systemId(),
	attributeProperties(new Properties()),//PATCHING
	children(),
	characterData(),
	unknownAttributes(),
	relationships(),
	contentTypes()
{
	clear();
}


/* 
 * Default constructor used to create a DOM object which will be treated as a black box until it can be converted
 * into a more specific document element or stored for round tripping purposes.
 * 
 * @param uri The Namespace URI, or the empty string if the element has no Namespace URI or if Namespace processing
 *           is not being performed.
 * @param localName The local name (without prefix), or the empty string if Namespace processing is not being
 *           performed.
 * @param qName The qualified name (with prefix), or the empty string if qualified names are not available.
 * @param attributes The attributes attached to the element. If there are no attributes, it shall be null.
 * @param locator An object that can return the location of the SAX document event for this start of this object.
 */
DOMUnknown::DOMUnknown(obj_ptr<java::lang::String > uri, obj_ptr<java::lang::String > localName, obj_ptr<java::lang::String > qName, obj_ptr<org::xml::sax::Attributes > attributes, obj_ptr<org::xml::sax::Locator > locator)
:	uri(),
	localName(),
	qName(),
	column(JInt(0)),
	row(JInt(0)),
	publicId(),
	systemId(),
	attributeProperties(QOConstants::EMPTY_PROPERTIES),
	children(),
	characterData(),
	unknownAttributes(),
	relationships(),
	contentTypes()
{
	initialize(uri,localName,qName,attributes,locator);
}


/* 
 * Default constructor used to create a DOM object which will be treated as a black box until it can be converted
 * into a more specific document element or stored for round tripping purposes.
 * 
 * @param uri The Namespace URI, or the empty string if the element has no Namespace URI or if Namespace processing
 *           is not being performed.
 * @param localName The local name (without prefix), or the empty string if Namespace processing is not being
 *           performed.
 */
DOMUnknown::DOMUnknown(obj_ptr<java::lang::String > uri, obj_ptr<java::lang::String > localName)
:	uri(),
	localName(),
	qName(),
	column(JInt(0)),
	row(JInt(0)),
	publicId(),
	systemId(),
	attributeProperties(QOConstants::EMPTY_PROPERTIES),
	children(),
	characterData(),
	unknownAttributes(),
	relationships(),
	contentTypes()
{
	initialize(uri,localName,__NULL_VALUE,__NULL_VALUE,__NULL_VALUE);
}


/* 
 * Create a DOM object which will be treated as a black box until it can be converted into a more specific document
 * element or stored for round tripping purposes.
 * 
 * @param uri The Namespace URI, or the empty string if the element has no Namespace URI or if Namespace processing
 *           is not being performed.
 * @param localName The local name (without prefix), or the empty string if Namespace processing is not being
 *           performed.
 * @param qName The qualified name (with prefix), or the empty string if qualified names are not available.
 * @param attributes The attributes attached to the element. If there are no attributes, it shall be null.
 * @param locator An object that can return the location of the SAX document event for this start of this object.
 */
void DOMUnknown::initialize(obj_ptr<java::lang::String > uri, obj_ptr<java::lang::String > localName, obj_ptr<java::lang::String > qName, obj_ptr<org::xml::sax::Attributes > attributes, obj_ptr<org::xml::sax::Locator > locator)
{
	this->uri = uri;
	this->localName = localName;
	this->qName = qName;
	attributeProperties = BaseReader::convertAttributes(attributes,attributeProperties,this);
	if (__NULL_VALUE != locator)
	{
		column = locator->getColumnNumber();
		row = locator->getLineNumber();
		publicId = locator->getPublicId();
		systemId = locator->getSystemId();
	}
}


/* 
 * Clear the object variables.
 */
void DOMUnknown::clear()
{
	qName = __NULL_VALUE;
	attributeProperties->clear();
	if (__NULL_VALUE != unknownAttributes)
	{
		unknownAttributes->__delete(0,unknownAttributes->length());
	}
	column = 0;
	row = 0;
	publicId = __NULL_VALUE;
	systemId = __NULL_VALUE;
	children = __NULL_VALUE;
}


obj_ptr<java::lang::Object > DOMUnknown::visit(obj_ptr<SharedVisitor > visitor, obj_ptr<java::lang::Object > arg1)
{
	return obj_ptr<java::lang::Object >(visitor->visit(this,arg1));
}


void DOMUnknown::getValuesForKeysWithProperties(obj_ptr<Properties > properties)
{
	DOMObject::getValuesForKeysWithProperties(properties);
	if (__NULL_VALUE != attributeProperties)
	{
		properties->putAll(attributeProperties);
	}
}


/* 
 * @return the uri
 */
obj_ptr<java::lang::String > DOMUnknown::getURI()
{
	return obj_ptr<java::lang::String >(uri);
}


/* 
 * @return the localName
 */
obj_ptr<java::lang::String > DOMUnknown::getLocalName()
{
	return obj_ptr<java::lang::String >(localName);
}


/* 
 * @return the qName
 */
obj_ptr<java::lang::String > DOMUnknown::getQName()
{
	return obj_ptr<java::lang::String >(qName);
}


/* 
 * @return the column
 */
JInt DOMUnknown::getColumn()
{
	return JInt(column);
}


/* 
 * @return the row
 */
JInt DOMUnknown::getRow()
{
	return JInt(row);
}


/* 
 * @return the publicId
 */
obj_ptr<java::lang::String > DOMUnknown::getPublicId()
{
	return obj_ptr<java::lang::String >(publicId);
}


/* 
 * @return the systemId
 */
obj_ptr<java::lang::String > DOMUnknown::getSystemId()
{
	return obj_ptr<java::lang::String >(systemId);
}


/* 
 * @return the attributes
 */
obj_ptr<Properties > DOMUnknown::getAttributes()
{
	return obj_ptr<Properties >(attributeProperties);
}


/* 
 * Return the value for the attribute specified by the key, or null if no such attribute exists.
 * 
 * @param key Name of the attribute to be retrieved.
 * 
 * @return String representation of the attribute value.
 */
obj_ptr<java::lang::String > DOMUnknown::getAttribute(obj_ptr<java::lang::String > key)
{
	return obj_ptr<java::lang::String >(attributeProperties->getProperty(key));
}


/* 
 * Add an attribute into a DOMUnknown object. This should be used rarely.
 * 
 * @param key Name of the attribute to store.
 * @param value String representation of the value to store.
 * 
 * @return String of the value that was previously stored for the object, or null if the attribute was not previously
 *         stored.
 */
obj_ptr<java::lang::String > DOMUnknown::addAttribute(obj_ptr<java::lang::String > key, obj_ptr<java::lang::String > value)
{
	if (QOConstants::EMPTY_PROPERTIES == attributeProperties)
	{
		attributeProperties = obj_ptr<Properties >( new Properties());
	}
	attributeProperties->setProperty(key,value);
	return obj_ptr<java::lang::String >(value);
}


/* 
 * @return the children
 */
obj_ptr<java::util::List<obj_ptr<DOMObject > > > DOMUnknown::getChildren()
{
	return obj_ptr<java::util::List<obj_ptr<DOMObject > > >(children);
}


/* 
 * @param children the children to set
 */
void DOMUnknown::setChildren(obj_ptr<java::util::List<obj_ptr<DOMObject > > > children)
{
	if (this->children != children)
	{
		if (( __NULL_VALUE != children ) && !children->isEmpty())
		{
			this->children = obj_ptr<java::util::ArrayList<obj_ptr<DOMObject > > >( new java::util::ArrayList<obj_ptr<DOMObject > >(children));
		}
		else
		{
			this->children = __NULL_VALUE;
		}
	}
}


/* 
 * @return the characterData
 */
obj_ptr<java::lang::String > DOMUnknown::getCharacterData()
{
	return obj_ptr<java::lang::String >(characterData);
}


/* 
 * @param characterData the characterData to set
 */
void DOMUnknown::setCharacterData(obj_ptr<java::lang::String > characterData)
{
	this->characterData = characterData;
}


/* 
 * Helper method which adds the unknown attribute to the unknownAttributes StringBuilder. The unknown attributes are
 * saved with the prefixes. For example the unknown attribute paraId with prefix w14 is saved as
 * w14:paraId="66451279".
 * 
 * @param attributes - the attributes of the element currently in process.
 * @param index - the current attribute index.
 * @param unknownAttributes 0- the String builder which stores the unknownAttributes.
 */
void DOMUnknown::addUnknownAttribute(obj_ptr<org::xml::sax::Attributes > attributes, JInt index)
{
	if (__NULL_VALUE == unknownAttributes)
	{
		unknownAttributes = obj_ptr<java::lang::StringBuilder >( new java::lang::StringBuilder());
	}
	unknownAttributes->append(attributes->getQName(index));
	unknownAttributes->append(new String(std::wstring(L"=\"")));
	unknownAttributes->append(attributes->getValue(index));
	unknownAttributes->append(new String(std::wstring(L"\" ")));
}


/* 
 * Gets the unknown attribute string for the element currently being processed.
 * 
 * @return unknown attribute string for the element. Returns null if the element doesn't have unknown attributes.
 */
obj_ptr<java::lang::String > DOMUnknown::getUnknownAttributesString()
{
	if (__NULL_VALUE != unknownAttributes)
	{
		return obj_ptr<java::lang::String >(unknownAttributes->toString());
	}
	return obj_ptr<java::lang::String >(__NULL_VALUE);
}


/* 
 * @return the relationships
 */
obj_ptr<java::util::Map<obj_ptr<java::lang::String >, obj_ptr<Relationship > > > DOMUnknown::getRelationships()
{
	return obj_ptr<java::util::Map<obj_ptr<java::lang::String >, obj_ptr<Relationship > > >(relationships);
}


/* 
 * @param relationship the relationship to add
 */
void DOMUnknown::addRelationships(obj_ptr<java::lang::String > relAttrbiute, obj_ptr<Relationship > relationship)
{
	if (__NULL_VALUE == relationships)
	{
		relationships = obj_ptr<java::util::HashMap<obj_ptr<java::lang::String >, obj_ptr<Relationship > > >( new java::util::HashMap<obj_ptr<java::lang::String >, obj_ptr<Relationship > >(1));
	}
	relationships->put(relAttrbiute,relationship);
}


/* 
 * @return the contentType if valid content-type is found otherwise returns null
 */
obj_ptr<java::lang::String > DOMUnknown::getContentTypes(obj_ptr<java::lang::String > key)
{
	if (( __NULL_VALUE != contentTypes ) && !( contentTypes->isEmpty() ))
	{
		return obj_ptr<java::lang::String >(contentTypes->get(key));
	}
	return obj_ptr<java::lang::String >(__NULL_VALUE);
}


/* 
 * @param contentTypes the contentTypes to set
 */
void DOMUnknown::addContentTypes(obj_ptr<java::lang::String > relAttrbiute, obj_ptr<java::lang::String > contentType)
{
	if (__NULL_VALUE == contentTypes)
	{
		contentTypes = obj_ptr<java::util::HashMap<obj_ptr<java::lang::String >, obj_ptr<java::lang::String > > >( new java::util::HashMap<obj_ptr<java::lang::String >, obj_ptr<java::lang::String > >(1));
	}
	contentTypes->put(relAttrbiute,contentType);
}


JInt DOMUnknown::getClassSerialId()
{
	return (m_serial_id);
}


JBool  DOMUnknown::isInstanceOf(JInt serialId)
{
	if (m_serial_id == serialId)
	{
		return (true);
	}
	if (DOMObject::isInstanceOf(serialId))
	{
		return (true);
	}
	if (ISharedVisitable::isInstanceOf(serialId))
	{
		return (true);
	}
	return (false);
}



} // QO

