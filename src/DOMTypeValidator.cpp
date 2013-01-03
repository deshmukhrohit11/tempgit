//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "DOMTypeValidator.h"

#include "com/quickoffice/common/formats/SerialIdConstants.h"

using namespace std;
using namespace java;
using namespace java::lang;


namespace QO
{

JInt DOMTypeValidator::m_serial_id =  (JInt)SerialIdConstants_DOM_DOMTYPEVALIDATOR;

DOMTypeValidator::DOMTypeValidator()
{
}


JInt DOMTypeValidator::getClassSerialId()
{
	return (m_serial_id);
}


JBool  DOMTypeValidator::isInstanceOf(JInt serialId)
{
	if (m_serial_id == serialId)
	{
		return (true);
	}
	if (java::lang::Object::isInstanceOf(serialId))
	{
		return (true);
	}
	return (false);
}



} // QO

