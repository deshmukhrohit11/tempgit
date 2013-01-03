//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "SerialIdConstants.h"


using namespace std;
using namespace java;
using namespace java::lang;


namespace QO
{

JInt SerialIdConstants::m_serial_id = 2000000000;

JInt SerialIdConstants::getClassSerialId()
{
	return (m_serial_id);
}


JBool  SerialIdConstants::isInstanceOf(JInt serialId)
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

