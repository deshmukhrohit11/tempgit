//
//                  Copyright Quickoffice, Inc, 2005-2010
//
// NOTICE:  The intellectual and technical concepts contained
// herein are proprietary to Quickoffice, Inc. and is protected by
// trade secret and copyright law. Dissemination of any of this
// information or reproduction of this material is strictly forbidden
// unless prior written permission is obtained from Quickoffice, Inc.
//

#include "DOMHelper.h"

#include "com/quickoffice/common/formats/SerialIdConstants.h"

using namespace std;
using namespace java;
using namespace java::lang;

using java::util::StringTokenizer;
using java::util::Date;
using java::util::NoSuchElementException;
using java::util::Calendar;

namespace QO
{
	
	JInt DOMHelper::m_serial_id =  (JInt)SerialIdConstants_DOM_DOMHELPER;
	obj_ptr<java::lang::String > DOMHelper::DOUBLE_INFINITY = new String(std::wstring(L"INF"));
	obj_ptr<java::lang::String > DOMHelper::BOOLEAN_ONE = new String(std::wstring(L"1"));
	obj_ptr<java::lang::String > DOMHelper::BOOLEAN_ZERO = new String(std::wstring(L"0"));
	obj_ptr<java::lang::String > DOMHelper::BOOLEAN_ON = new String(std::wstring(L"on"));
	obj_ptr<java::lang::String > DOMHelper::DATE_TIME_SEPARATOR = new String(std::wstring(L"T"));
	obj_ptr<java::lang::String > DOMHelper::DATE_SEPARATOR = new String(std::wstring(L"-"));
	obj_ptr<java::lang::String > DOMHelper::TIME_SEPARATOR = new String(std::wstring(L":"));
	array_ptr< JInt > DOMHelper::calendarFields = boost::assign::list_of(java::util::Calendar::YEAR)(java::util::Calendar::MONTH)(java::util::Calendar::DAY_OF_MONTH)(java::util::Calendar::HOUR_OF_DAY)(java::util::Calendar::MINUTE)(java::util::Calendar::SECOND);
	array_ptr< obj_ptr<java::lang::String > > DOMHelper::separators = boost::assign::list_of(DATE_SEPARATOR)(DATE_SEPARATOR)(DATE_TIME_SEPARATOR)(TIME_SEPARATOR)(TIME_SEPARATOR)(new String(std::wstring(L"Z")));
	array_ptr< obj_ptr<java::lang::String > > DOMHelper::units = boost::assign::list_of(new String(std::wstring(L"mm")))(new String(std::wstring(L"cm")))(new String(std::wstring(L"in")))(new String(std::wstring(L"pt")))(new String(std::wstring(L",pc")))(new String(std::wstring(L"pi")));
	obj_ptr<java::lang::String > DOMHelper::HEX_COLOR_AUTO = new String(std::wstring(L"auto"));
	JBool DOMHelper::DEFAULT_BOOLEAN_FALSE = false;
	JBool DOMHelper::DEFAULT_BOOLEAN_TRUE = true;
	JLong DOMHelper::DEFAULT_LONG_VALUE = 0L;
	JDouble DOMHelper::DEFAULT_DOUBLE_VALUE = 0L;
	JFloat DOMHelper::DEFAULT_FLOAT_VALUE = 0;
	JInt DOMHelper::DEFAULT_INT_VALUE = 0;
	JByte DOMHelper::DEFAULT_BYTE_VALUE = 0;
	JInt DOMHelper::BOOLEAN_INT_ONE = 1;
	JInt DOMHelper::BOOLEAN_INT_ZERO = 0;
	JByte DOMHelper::BYTE_ONE_VALUE = 1;
	JByte DOMHelper::BYTE_ZERO_VALUE = 0;
	JInt DOMHelper::DEFAULT_POI_FONT_SIZE = -1;
	JInt DOMHelper::VALUE_NOT_AVAILABLE = -1;
	JInt DOMHelper::COLOR_VALUE_STRING_LENGTH = 6;
	JChar DOMHelper::COLOR_VALUE_PADDING_CHAR = L'0';
	JChar DOMHelper::COLON = L':';
	JInt DOMHelper::DEFAULT_ARRAY_SIZE = 1;
	JInt DOMHelper::DEFAULT_MAX_HEXADECIMAL_DIGIT = 6;
	obj_ptr<BooleanValue > DOMHelper::DEFAULT_BOOLEAN_VALUE_FALSE = BooleanValue::falseValue;
	obj_ptr<BooleanValue > DOMHelper::DEFAULT_BOOLEAN_VALUE_TRUE = BooleanValue::trueValue;
	obj_ptr<java::lang::String > DOMHelper::FALSE_STRING = new String(std::wstring(L"false"));
	obj_ptr<java::lang::String > DOMHelper::TRUE_STRING = new String(std::wstring(L"true"));
	obj_ptr<java::lang::String > DOMHelper::BOOLEAN_T_STRING = new String(std::wstring(L"t"));
	obj_ptr<java::lang::String > DOMHelper::BOOLEAN_F_STRING = new String(std::wstring(L"f"));
	JChar DOMHelper::CHAR_HASH = L'#';
	JInt DOMHelper::hexValueToRemove = java::lang::Integer::parseInt(new String(std::wstring(L"F000")),16);
	obj_ptr<java::lang::StringBuilder > DOMHelper::unicodeStringBuilder = obj_ptr<java::lang::StringBuilder >( new java::lang::StringBuilder());
	obj_ptr<UniversalMeasure > DOMHelper::DEFAULT_UNIVERSALMEASURE = obj_ptr<UniversalMeasure >( new UniversalMeasure(new String(std::wstring(L"0"))));
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a byte, if the
	 * property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JByte DOMHelper::getBytePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return JByte(getBytePropertyValue(properties,key,(JByte)0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a byte, if the
	 * property does not exist in the properties list it returns the default value provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JByte DOMHelper::getBytePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JByte defaultValue)
	{
		JByte val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Byte::parseByte(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return JByte(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a byte, if the
	 * property does not exist in the properties list it returns the default value provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JByte DOMHelper::getHexBytePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JByte defaultValue)
	{
		JByte val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Byte::parseByte(sval,16);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return JByte(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a byte, if the
	 * property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JByte DOMHelper::getHexBytePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return JByte(getHexBytePropertyValue(properties,key,(JByte)0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a boolean, if the
	 * property does not exist in the properties list it returns the default value provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return Boolean representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Boolean > DOMHelper::getBooleanPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Boolean > defaultValue)
	{
		obj_ptr<java::lang::Boolean > val = defaultValue;
		obj_ptr<java::lang::String > sVal = __NULL_VALUE;
		if (__NULL_VALUE != properties)
		{
			sVal = properties->getProperty(key);
		}
		if (__NULL_VALUE != sVal)
		{
			JBool valueCheck = ( BOOLEAN_ONE->equals(sVal) || BOOLEAN_ON->equals(sVal) );
			if (!valueCheck)
			{
				val = java::lang::Boolean::parseBoolean(sVal);
			}
			else
			{
				val = valueCheck;
			}
		}
		return obj_ptr<java::lang::Boolean >(val);
	}
	
	
	// inline function getEnumValue
	// inline function getEnumValue
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an integer, if the
	 * property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return int representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Integer > DOMHelper::getIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<java::lang::Integer >(getIntPropertyValue(properties,key,0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an integer, if the
	 * property does not exist in the properties list it returns the default value provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return int representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Integer > DOMHelper::getIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Integer > defaultValue)
	{
		obj_ptr<java::lang::Integer > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Integer::parseInt(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<java::lang::Integer >(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and removes all spaces that occur and attempts
	 * to convert it to an integer, if the property does not exist in the properties list it returns the default value
	 * provided.
	 * 
	 * @param properties properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve
	 * @param defaultValue
	 * @return representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Integer > DOMHelper::getSpacesIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Integer > defaultValue)
	{
		obj_ptr<java::lang::Integer > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key)->replaceAll(new String(std::wstring(L" ")),new String(std::wstring(L"")));
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Integer::parseInt(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<java::lang::Integer >(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an integer from
	 * its Hex String representation, if the property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return int representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Integer > DOMHelper::getHexIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<java::lang::Integer >(getHexIntPropertyValue(properties,key,0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an integer from
	 * its Hex String representation, if the property does not exist in the properties list it returns the default value
	 * provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return int representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Integer > DOMHelper::getHexIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Integer > defaultValue)
	{
		obj_ptr<java::lang::Integer > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Integer::parseInt(sval,16);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<java::lang::Integer >(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an long from its
	 * Hex String representation, if the property does not exist in the properties list it returns the default value
	 * provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JLong DOMHelper::getHexLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong defaultValue)
	{
		JLong val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Long::parseLong(sval,16);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return JLong(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to an long from its
	 * Hex String representation, if the property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JLong DOMHelper::getHexLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return JLong(getHexLongPropertyValue(properties,key,0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a long, if the
	 * property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JLong DOMHelper::getLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return JLong(getLongPropertyValue(properties,key,0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a long, if the
	 * property does not exist in the properties list it returns the default value provided.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JLong DOMHelper::getLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong defaultValue)
	{
		JLong val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Long::parseLong(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return JLong(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a float assuming
	 * it is a percentage, if the property does not exist in the properties list it returns 0.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<Percentage > DOMHelper::getPercentagePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<Percentage >(getPercentagePropertyValue(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a float assuming
	 * it is a percentage, if the property does not exist in the properties list it returns the default value provided.
	 * It will return 56.47% as .5646. In addition it will read in positive as well as negative percentages.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return Float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<Percentage > DOMHelper::getPercentagePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<Percentage > defaultValue)
	{
		obj_ptr<Percentage > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				val = obj_ptr<Percentage >( new Percentage(sval));
			}
		}
		return obj_ptr<Percentage >(val);
	}
	
	//COMMENTED_CODE
//	/* 
//	 * This method retrieves the named property from the properties list and attempts to convert it to a int assuming it
//	 * is a TLTime, if the property does not exist in the properties list it returns 0.
//	 * 
//	 * @param properties Properties object containing key-value pairs.
//	 * @param key String representing the key of the property value to retrieve.
//	 * 
//	 * @return int representation of the value retrieved from Properties using the specified key.
//	 */
//	obj_ptr<TLTime > DOMHelper::getTLTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
//	{
//		return obj_ptr<TLTime >(getTLTimePropertyValue(properties,key,__NULL_VALUE));
//	}
//	
//	
//	/* 
//	 * This method retrieves the named property from the properties list and attempts to convert it to a int assuming it
//	 * is a percentage, if the property does not exist in the properties list it returns the default value provided.
//	 * 
//	 * @param properties Properties object containing key-value pairs.
//	 * @param key String representing the key of the property value to retrieve.
//	 * @param defaultValue The value that should be used if the property does not exist.
//	 * 
//	 * @return int representation of the value retrieved from Properties using the specified key.
//	 */
//	obj_ptr<TLTime > DOMHelper::getTLTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TLTime > defaultValue)
//	{
//		obj_ptr<TLTime > val = defaultValue;
//		if (__NULL_VALUE != properties)
//		{
//			obj_ptr<java::lang::String > sval = properties->getProperty(key);
//			if (__NULL_VALUE != sval)
//			{
//				val = obj_ptr<TLTime >( new TLTime(sval));
//			}
//		}
//		return obj_ptr<TLTime >(val);
//	}
//	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a double.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JDouble DOMHelper::getDoublePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return JDouble(getDoublePropertyValue(properties,key,0));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a double.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JDouble DOMHelper::getDoublePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JDouble defaultValue)
	{
		JDouble val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Double::parseDouble(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (0 == sval->compareToIgnoreCase(DOUBLE_INFINITY))
					{
						val = java::lang::Double::POSITIVE_INFINITY;
					}
					else
					{
						if (QOConstants::ASSERTS)
						{
							if ( !(false) )
							{
								__X_THROW(new java::lang::AssertionError());
							}
						}
					}
				}
			}
		}
		return JDouble(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a Date.
	 * <p>
	 * Note that this function expects datetime in the format 2005-01-01T10:00:00Z.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return Date representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::util::Date > DOMHelper::getDatePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<java::util::Date >(getDatePropertyValue(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a Date.
	 * <p>
	 * Note that this function expects datetime in the format 2005-01-01T10:00:00Z.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * @return Date representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::util::Date > DOMHelper::getDatePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::util::Date > defaultValue)
	{
		obj_ptr<java::util::Date > dateVal = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sVal = properties->getProperty(key);
			if (__NULL_VALUE != sVal)
			{
				dateVal = parseDateString(sVal);
			}
		}
		return obj_ptr<java::util::Date >(dateVal);
	}
	
	
	/* 
	 * This method parses date string to a Date.
	 * <p>
	 * Note that this function expects datetime in the format 2005-01-01T10:00:00Z.
	 * 
	 * @param dateString
	 * @return Date representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::util::Date > DOMHelper::parseDateString(obj_ptr<java::lang::String > dateString)
	{
		obj_ptr<java::util::Date > dateVal = __NULL_VALUE;
		obj_ptr<java::util::Calendar > calendar = java::util::Calendar::getInstance();
		obj_ptr<java::util::StringTokenizer > dateTimeTokenizer = obj_ptr<java::util::StringTokenizer >( new java::util::StringTokenizer(dateString,DATE_TIME_SEPARATOR));
		try
		{
			obj_ptr<java::lang::String > dateTokens = dateTimeTokenizer->nextToken();
			obj_ptr<java::lang::String > timeTokens = dateTimeTokenizer->nextToken();
			obj_ptr<java::util::StringTokenizer > dateTokenizer = obj_ptr<java::util::StringTokenizer >( new java::util::StringTokenizer(dateTokens,DATE_SEPARATOR));
			JInt year = java::lang::Integer::parseInt(dateTokenizer->nextToken());
			JInt month = java::lang::Integer::parseInt(dateTokenizer->nextToken());
			JInt day = java::lang::Integer::parseInt(dateTokenizer->nextToken());
			obj_ptr<java::util::StringTokenizer > timeTokenizer = obj_ptr<java::util::StringTokenizer >( new java::util::StringTokenizer(timeTokens,TIME_SEPARATOR));
			JInt hours = java::lang::Integer::parseInt(timeTokenizer->nextToken());
			JInt minutes = java::lang::Integer::parseInt(timeTokenizer->nextToken());
			obj_ptr<java::lang::String > sSeconds = timeTokenizer->nextToken()->substring(0,2);
			JInt seconds = java::lang::Integer::parseInt(sSeconds);
			calendar->set(java::util::Calendar::YEAR,year);
			calendar->set(java::util::Calendar::MONTH,month - 1);
			calendar->set(java::util::Calendar::DAY_OF_MONTH,day);
			calendar->set(java::util::Calendar::HOUR_OF_DAY,hours);
			calendar->set(java::util::Calendar::MINUTE,minutes);
			calendar->set(java::util::Calendar::SECOND,seconds);
			dateVal = calendar->getTime();
		}
		catch (obj_ptr<java::util::NoSuchElementException > nse)
		{
			if (QOConstants::ASSERTS)
			{
				if ( !(false) )
				{
					__X_THROW(new java::lang::AssertionError());
				}
			}
		}
		catch (obj_ptr<NumberFormatException > nfe)
		{
			if (QOConstants::ASSERTS)
			{
				if ( !(false) )
				{
					__X_THROW(new java::lang::AssertionError());
				}
			}
		}
		return obj_ptr<java::util::Date >(dateVal);
	}
	
	
	/* 
	 * FIXME: (vj) I know i need a better way to parse the data. This is just a raw implementation to get things working.
	 * 
	 * This method retrieves the named property from the properties list and attempts to convert it to a TwipsMeasure.
	 * <p>
	 * Note that this function expects the data in the format in the format [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return TwipsMeasure representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<TwipsMeasure > DOMHelper::getTwipMeasure(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<TwipsMeasure >(getTwipMeasure(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * FIXME: (vj) I know i need a better way to parse the data. This is just a raw implementation to get things working.
	 * 
	 * This method retrieves the named property from the properties list and attempts to convert it to a TwipsMeasure.
	 * <p>
	 * Note that this function expects the data in the format in the format [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * @return TwipsMeasure representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<TwipsMeasure > DOMHelper::getTwipMeasure(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TwipsMeasure > defaultValue)
	{
		obj_ptr<TwipsMeasure > twipMeasureVal = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sVal = properties->getProperty(key);
			if (__NULL_VALUE != sVal)
			{
				try
				{
					JInt unitIndex = -1;
					for (JInt i = 0; ( i < units->length ) && ( unitIndex == -1 ); i++)
					{
						unitIndex = sVal->indexOf(units[i]);
					}
					obj_ptr<java::lang::Double > measure = DEFAULT_DOUBLE_VALUE;
					obj_ptr<TwipsMeasureUnit > unit = TwipsMeasureUnit::none;
					if (-1 != unitIndex)
					{
						unit = TwipsMeasureUnit::valueOf(sVal->substring(unitIndex));
						measure = java::lang::Double::valueOf(sVal->substring(0,unitIndex));
					}
					else
					{
						measure = java::lang::Double::valueOf(sVal);
					}
					twipMeasureVal = obj_ptr<TwipsMeasure >( new TwipsMeasure(measure,unit));
				}
				catch (obj_ptr<NumberFormatException > nfe)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
				catch (obj_ptr<java::lang::IllegalArgumentException > iae)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<TwipsMeasure >(twipMeasureVal);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a ColorValueType.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return ColorValueType representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<ColorValueType > DOMHelper::getColorValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<ColorValueType >(getColorValue(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a ColorValueType.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * @return ColorValueType representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<ColorValueType > DOMHelper::getColorValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ColorValueType > defaultValue)
	{
		obj_ptr<ColorValueType > colorValue = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sVal = properties->getProperty(key);
			if (__NULL_VALUE != sVal)
			{
				sVal = sVal->trim();
				if (CHAR_HASH == sVal->charAt(0))
				{
					sVal = sVal->substring(1);
				}
				try
				{
					JBool l_auto = sVal->equals(HEX_COLOR_AUTO);
					JInt color = -1;
					if (!l_auto)
					{
						color = java::lang::Integer::parseInt(sVal,16);
					}
					colorValue = obj_ptr<ColorValueType >( new ColorValueType(color,l_auto));
				}
				catch (obj_ptr<NumberFormatException > nfe)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<ColorValueType >(colorValue);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a long assuming it
	 * is a Universal Measure or Unqualified Coordinate, if the property does not exist in the properties list it returns
	 * 0.
	 * 
	 * Note that this function expects the data either in [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)format or as long datatype
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * 
	 * @return float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<UniversalMeasure > DOMHelper::getUniversalMeasurePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<UniversalMeasure >(getUniversalMeasurePropertyValue(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a long assuming it
	 * is a Universal Measure or Unqualified Coordinate, if the property does not exist in the properties list it returns
	 * the default value provided. It will calculate EMU value for Universal Measurements. In addition it will read in
	 * positive as well as negative Measures.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * 
	 * @return Float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<UniversalMeasure > DOMHelper::getUniversalMeasurePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<UniversalMeasure > defaultValue)
	{
		obj_ptr<UniversalMeasure > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				val = obj_ptr<UniversalMeasure >( new UniversalMeasure(sval));
			}
		}
		return obj_ptr<UniversalMeasure >(val);
	}
	
	
	/* 
	 * This method stores the named property into the properties list.
	 * 
	 * @param properties Properties object to receive the key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JByte value)
	{
		return JBool(setBytePropertyValue(properties,key,value,(JByte)0,true));
	}
	
	
	/* 
	 * This method stores the named property into the properties list <strong>only</strong> if it differs from the
	 * default value.
	 * 
	 * @param properties Properties object to receive the key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store.
	 * @param defaultValue The value to compare with the value argument to determine if the value should be written
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JByte value, JByte defaultValue)
	{
		return JBool(setBytePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method stores the named property into the properties list <strong>only</strong>if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to receive the key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store.
	 * @param defaultValue The value to compare with the value argument to determine if the value should be written
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return byte representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setBytePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JByte value, JByte defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			properties->setProperty(key,java::lang::Byte::toString(value));
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property into the properties list.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Boolean > value)
	{
		return JBool(setBooleanPropertyValue(properties,key,value,DEFAULT_BOOLEAN_FALSE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Boolean > value, obj_ptr<java::lang::Boolean > defaultValue)
	{
		return JBool(setBooleanPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setBooleanPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Boolean > value, obj_ptr<java::lang::Boolean > defaultValue, JBool force)
	{
		JBool set = false;
		if (( __NULL_VALUE != value ) && ( force || ( value != defaultValue ) ))
		{
			properties->setProperty(key,CONDITIONAL_EXPRESSION((value->booleanValue()) , BOOLEAN_ONE , BOOLEAN_ZERO));
			set = true;
		}
		return JBool(set);
	}
	
	
	// inline function setEnumPropertyValue
	// inline function setEnumPropertyValue
	// inline function setEnumPropertyValue
	/* 
	 * This method sets the named property to the specified value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value)
	{
		return JBool(setIntPropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value, JInt defaultValue)
	{
		return JBool(setIntPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value, JInt defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			properties->setProperty(key,java::lang::Integer::toString(value));
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation, even if it is same
	 * as default value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryHexPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value)
	{
		return JBool(setHexIntPropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalHexPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value, JInt defaultValue)
	{
		return JBool(setHexIntPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setHexIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value, JInt defaultValue, JBool force)
	{
		return JBool(setHexIntPropertyValue(properties,key,value,defaultValue,force,DEFAULT_MAX_HEXADECIMAL_DIGIT));
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * @param maxLength total number of hexadecimal characters(digits).
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setHexIntPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JInt value, JInt defaultValue, JBool force, JInt maxLength)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			obj_ptr<java::lang::String > val = getPaddedString(java::lang::Integer::toString(value,16)->toUpperCase(),maxLength,L'0',false);
			properties->setProperty(key,val);
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * @param maxLength total number of hexadecimal characters(digits).
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setHexLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value, JLong defaultValue, JBool force, JInt maxLength)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			obj_ptr<java::lang::String > val = getPaddedString(java::lang::Long::toString(value,16)->toUpperCase(),maxLength,L'0',false);
			properties->setProperty(key,val);
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setHexLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value, JLong defaultValue, JBool force)
	{
		return JBool(setHexLongPropertyValue(properties,key,value,defaultValue,force,DEFAULT_MAX_HEXADECIMAL_DIGIT));
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation, even if it is same
	 * as default value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryHexPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value)
	{
		return JBool(setHexLongPropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method sets the named property to the specified value, using a HEX string representation,
	 * <strong>only</strong> if it differs from the default value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalHexPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value, JLong defaultValue)
	{
		return JBool(setHexLongPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method stores the named property into the properties list.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value)
	{
		return JBool(setLongPropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value, JLong defaultValue)
	{
		return JBool(setLongPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue or if
	 * force is set to True.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return long representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setLongPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JLong value, JLong defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			properties->setProperty(key,java::lang::Long::toString(value));
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method stores the named property into the properties list.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * 
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JFloat value)
	{
		return JBool(setFloatPropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JFloat value, JFloat defaultValue)
	{
		return JBool(setFloatPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue or if
	 * force is set to True.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return boolean if property set was successful or not.
	 */
	JBool DOMHelper::setFloatPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JFloat value, JFloat defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			if (java::lang::Float::POSITIVE_INFINITY == value)
			{
				properties->setProperty(key,DOUBLE_INFINITY);
			}
			else
			{
				properties->setProperty(key,java::lang::Float::toString(value));
			}
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method stores the named property into the properties list.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * 
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JDouble value)
	{
		return JBool(setDoublePropertyValue(properties,key,value,0,true));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return double representation of the value retrieved from Properties using the specified key.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JDouble value, JDouble defaultValue)
	{
		return JBool(setDoublePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method stores the named property into the properties list if the value differs from the defaultValue or if
	 * force is set to True.
	 * 
	 * @param properties Properties object to receive the key-value pair.
	 * @param key String representing the key of the property value to set.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return boolean if property set was successful or not.
	 */
	JBool DOMHelper::setDoublePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, JDouble value, JDouble defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( value != defaultValue ))
		{
			if (java::lang::Double::POSITIVE_INFINITY == value)
			{
				properties->setProperty(key,DOUBLE_INFINITY);
			}
			else
			{
				properties->setProperty(key,java::lang::Double::toString(value));
			}
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property to the specified value in percentage format.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * 
	 * @see OOD Section 22.9.2.11 (ST_PositivePercentage) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
	 *      Reference"
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<Percentage > value)
	{
		return JBool(setPercentagePropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @see OOD Section 22.9.2.11 (ST_PositivePercentage) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
	 *      Reference"
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<Percentage > value, obj_ptr<Percentage > defaultValue)
	{
		return JBool(setPercentagePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property to the specified value if the float value, to be interpreted as a percentage,
	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @see OOD Section 22.9.2.11 (ST_PositivePercentage) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
	 *      Reference"
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setPercentagePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<Percentage > value, obj_ptr<Percentage > defaultValue, JBool force)
	{
		JBool set = false;
		obj_ptr<java::lang::String > valueToWrite = CONDITIONAL_EXPRESSION((__NULL_VALUE != value) , value->getValue() , __NULL_VALUE);
		obj_ptr<java::lang::String > defValue = CONDITIONAL_EXPRESSION((__NULL_VALUE != defaultValue) , defaultValue->getValue() , __NULL_VALUE);
		if (__NULL_VALUE != valueToWrite)
		{
			if (force || ( !force && !valueToWrite->equals(defValue) ))
			{
				properties->setProperty(key,valueToWrite);
				set = true;
			}
		}
		return JBool(set);
	}
// COMMENTED_CODE	
//	
//	/* 
//	 * This method sets the named property to the specified value in TLTime format.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * 
//	 * @see OOD Section 19.7.38 ST_TLTime (Time) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
//	 *      Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TLTime > value)
//	{
//		return JBool(setTLTimePropertyValue(properties,key,value,__NULL_VALUE,true));
//	}
//	
//	
//	/* 
//	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
//	 * value.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
//	 * 
//	 * @see OOD Section 19.7.38 ST_TLTime (Time) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
//	 *      Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TLTime > value, obj_ptr<TLTime > defaultValue)
//	{
//		return JBool(setTLTimePropertyValue(properties,key,value,defaultValue,false));
//	}
//	
//	
//	/* 
//	 * This method sets the named property to the specified value if the float value, to be interpreted as a TLTime,
//	 * <strong>only</strong> if it differs from the default value or if the force argument is set to True.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
//	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
//	 * 
//	 * @see OOD Section 19.7.38 ST_TLTime (Time) in "EMCA-376, 2nd Ed, Part 1 - Fundamentals And Markup Language
//	 *      Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setTLTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TLTime > value, obj_ptr<TLTime > defaultValue, JBool force)
//	{
//		JBool set = false;
//		obj_ptr<java::lang::String > valueToWrite = CONDITIONAL_EXPRESSION((__NULL_VALUE != value) , value->getStringValue() , __NULL_VALUE);
//		obj_ptr<java::lang::String > defValue = CONDITIONAL_EXPRESSION((__NULL_VALUE != defaultValue) , defaultValue->getStringValue() , __NULL_VALUE);
//		if (__NULL_VALUE != valueToWrite)
//		{
//			if (force || ( !force && !valueToWrite->equals(defValue) ))
//			{
//				properties->setProperty(key,valueToWrite);
//				set = true;
//			}
//		}
//		return JBool(set);
//	}
//	
//	
	/* 
	 * This method sets the named property into the properties list.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::String > value)
	{
		return JBool(setString(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::String > value, obj_ptr<java::lang::String > defaultValue)
	{
		return JBool(setString(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setString(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::String > value, obj_ptr<java::lang::String > defaultValue, JBool force)
	{
		JBool set = false;
		if (( __NULL_VALUE != value ) && ( force || ( !force && !value->equals(defaultValue) ) ))
		{
			properties->setProperty(key,value);
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the date in the format: 2009-11-19T18:22:00Z
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::util::Date > value)
	{
		return JBool(setDatePropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the date in the format: 2009-11-19T18:22:00Z
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::util::Date > value, obj_ptr<java::util::Date > defaultValue)
	{
		return JBool(setDatePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the date in the format: 2009-11-19T18:22:00Z
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setDatePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::util::Date > value, obj_ptr<java::util::Date > defaultValue, JBool force)
	{
		JBool set = false;
		if (( __NULL_VALUE != value ) && ( force || ( !value->equals(defaultValue) ) ))
		{
			obj_ptr<java::lang::StringBuilder > sDate = obj_ptr<java::lang::StringBuilder >( new java::lang::StringBuilder());
			obj_ptr<java::util::Calendar > calendar = java::util::Calendar::getInstance();
			calendar->setTime(value);
			JInt i = 0;
			for (obj_ptr<java::util::Iterator<JInt > > __i = calendarFields->iterator(); __i->hasNext();  )
			{
				{
					JInt calendarField = __i->next();
					JInt fieldValue = calendar->get(calendarField);
					if (fieldValue < 10)
					{
						sDate->append(L'0');
					}
					if (java::util::Calendar::MONTH == calendarField)
					{
						fieldValue++;
					}
					sDate->append(fieldValue);
					sDate->append(separators[i++]);
				}
			}
			properties->setProperty(key,sDate->toString());
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the TwipMeasure in the format: [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TwipsMeasure > value)
	{
		return JBool(setTwipMeasurePropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the TwipMeasure in the format: [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TwipsMeasure > value, obj_ptr<TwipsMeasure > defaultValue)
	{
		return JBool(setTwipMeasurePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * We want to store the TwipMeasure in the format: [0-9]+(\.[0-9]+)?(mm|cm|in|pt|pc|pi)
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setTwipMeasurePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<TwipsMeasure > value, obj_ptr<TwipsMeasure > defaultValue, JBool force)
	{
		JBool set = false;
		if (( __NULL_VALUE != value ) && ( force || ( !value->equals(defaultValue) ) ))
		{
			obj_ptr<java::lang::StringBuilder > sTwipMeasure = obj_ptr<java::lang::StringBuilder >( new java::lang::StringBuilder());
			sTwipMeasure->append(value->getMeasurement());
			if (TwipsMeasureUnit::none != value->getUnit())
			{
				sTwipMeasure->append(value->getUnit()->toString());
			}
			properties->setProperty(key,sTwipMeasure->toString());
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ColorValueType > value)
	{
		return JBool(setColorPropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ColorValueType > value, obj_ptr<ColorValueType > defaultValue)
	{
		return JBool(setColorPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setColorPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ColorValueType > value, obj_ptr<ColorValueType > defaultValue, JBool force)
	{
		JBool set = false;
		if (force || ( !value->equals(defaultValue) ))
		{
			if (value->isAuto())
			{
				properties->setProperty(key,HEX_COLOR_AUTO);
			}
			else
			{
				properties->setProperty(key,getPaddedString(java::lang::Integer::toHexString(value->getColor()),COLOR_VALUE_STRING_LENGTH,COLOR_VALUE_PADDING_CHAR,false));
			}
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method pads passed string as per provided padding character and expected length of String.
	 * 
	 * @param toPad
	 * @param totalLength
	 * @param paddingChar
	 * @param isSuffixChar
	 * @return the padded String.
	 */
	obj_ptr<java::lang::String > DOMHelper::getPaddedString(obj_ptr<java::lang::String > toPad, JInt totalLength, JChar paddingChar, JBool isSuffixChar)
	{
		obj_ptr<java::lang::StringBuffer > paddedString = obj_ptr<java::lang::StringBuffer >( new java::lang::StringBuffer(totalLength));
		if (isSuffixChar)
		{
			paddedString->append(toPad);
			for (JInt index = 0; index < ( totalLength - toPad->length() ); index++)
			{
				paddedString->append(paddingChar);
			}
		}
		else
		{
			for (JInt index = 0; index < ( totalLength - toPad->length() ); index++)
			{
				paddedString->append(paddingChar);
			}
			paddedString->append(toPad);
		}
		return obj_ptr<java::lang::String >(paddedString->toString());
	}
	
	
	/* 
	 * This method extracts Unicode Category Co. (java.lang.Character.PRIVATE_USE) characters.<br>
	 * If we get hex value of character as F045, then character value can be obtained by removing F000 from the hex
	 * value.
	 * 
	 * @param domTextRun
	 * @return extracted String.
	 */
	obj_ptr<java::lang::String > DOMHelper::convertUnicodeCharactersFromTextRun(obj_ptr<java::lang::String > textString)
	{
		//COMMENTED_CODE
		//JBool isDecodingDone = false;
		//	obj_ptr<java::lang::String > newTextString = __NULL_VALUE;
		//	if (__NULL_VALUE != textString)
		//	{
		//		for (obj_ptr<java::util::Iterator<JChar > > __i = textString->toCharArray()->iterator(); __i->hasNext();  )
		//		{
		//			{
		//				JChar ch = __i->next();
		//				if (java::lang::Character::getType(ch) == java::lang::Character::PRIVATE_USE)
		//				{
		//					JInt charValue = java::lang::Integer::parseInt(java::lang::Integer::toHexString(ch),16) - hexValueToRemove;
		//					unicodeStringBuilder->append((JChar)charValue);
		//					isDecodingDone = true;
		//				}
		//			}
		//		}
		//		if (isDecodingDone)
		//		{
		//			newTextString = unicodeStringBuilder->toString();
		//			unicodeStringBuilder->__delete(0,newTextString->length());
		//			isDecodingDone = false;
		//		}
		//	}
		//	return obj_ptr<java::lang::String >(newTextString);
		return textString;
	}
	
	
	/* 
	 * This method extracts string value from BooleanValue. This function handles BooleanValue ({@link BooleanValue})
	 * because some of the boolean values are same as keywords in JAVA.
	 * 
	 * @param booleanValue
	 * @return extracted String.
	 */
	obj_ptr<java::lang::String > DOMHelper::getBooleanValueString(obj_ptr<BooleanValue > booleanValue)
	{
		if (__NULL_VALUE != booleanValue)
		{
			if (booleanValue->equals(BooleanValue::falseValue))
			{
				return obj_ptr<java::lang::String >(FALSE_STRING);
			}
			else
			{
				if (booleanValue->equals(BooleanValue::trueValue))
				{
					return obj_ptr<java::lang::String >(TRUE_STRING);
				}
				else
				{
					if (booleanValue->equals(BooleanValue::t))
					{
						return obj_ptr<java::lang::String >(BOOLEAN_T_STRING);
					}
					else
					{
						if (booleanValue->equals(BooleanValue::f))
						{
							return obj_ptr<java::lang::String >(BOOLEAN_F_STRING);
						}
					}
				}
			}
		}
		return obj_ptr<java::lang::String >(__NULL_VALUE);
	}
	
	
	/* 
	 * This method extracts BooleanValue from property string. This function handles BooleanValue ({@link BooleanValue})
	 * because some of the boolean values are same as keywords in JAVA.
	 * 
	 * @param propertyString
	 * @return booleanValue.
	 */
	obj_ptr<BooleanValue > DOMHelper::getBooleanValue(obj_ptr<java::lang::String > propertyString)
	{
		if (__NULL_VALUE != propertyString)
		{
			if (propertyString->equals(FALSE_STRING))
			{
				return obj_ptr<BooleanValue >(BooleanValue::falseValue);
			}
			else
			{
				if (propertyString->equals(TRUE_STRING))
				{
					return obj_ptr<BooleanValue >(BooleanValue::trueValue);
				}
				else
				{
					if (propertyString->equals(BOOLEAN_T_STRING))
					{
						return obj_ptr<BooleanValue >(BooleanValue::t);
					}
					else
					{
						if (propertyString->equals(BOOLEAN_F_STRING))
						{
							return obj_ptr<BooleanValue >(BooleanValue::f);
						}
					}
				}
			}
		}
		return obj_ptr<BooleanValue >(__NULL_VALUE);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a ThemeColorType.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return ThemeColorType representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<ThemeColorType > DOMHelper::getThemeColorValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<ThemeColorType >(getThemeColorValue(properties,key,__NULL_VALUE));
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a ThemeColorType.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param defaultValue The value that should be used if the property does not exist.
	 * @return ThemeColorType representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<ThemeColorType > DOMHelper::getThemeColorValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ThemeColorType > defaultValue)
	{
		obj_ptr<ThemeColorType > themeColorValue = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sVal = properties->getProperty(key);
			if (__NULL_VALUE != sVal)
			{
				sVal = sVal->trim();
				JBool hexVal = true;
				obj_ptr<ThemeColorTypeEnum > colorTypeEnum = __NULL_VALUE;
				for (obj_ptr<java::util::Iterator<obj_ptr<ThemeColorTypeEnum > > > __i = ThemeColorTypeEnum::values()->iterator(); __i->hasNext();  )
				{
					{
						obj_ptr<ThemeColorTypeEnum > enumObj = __i->next();
						if (enumObj->name()->equals(sVal))
						{
							hexVal = false;
							colorTypeEnum = enumObj;
							break;
						}
					}
				}
				JInt color = -1;
				try
				{
					if (hexVal)
					{
						color = java::lang::Integer::parseInt(sVal,16);
					}
					themeColorValue = obj_ptr<ThemeColorType >( new ThemeColorType(color,colorTypeEnum,hexVal));
				}
				catch (obj_ptr<NumberFormatException > nfe)
				{
					if (QOConstants::ASSERTS)
					{
						if ( !(false) )
						{
							__X_THROW(new java::lang::AssertionError());
						}
					}
				}
			}
		}
		return obj_ptr<ThemeColorType >(themeColorValue);
	}
	
	
	/* 
	 * This method sets the named property into the properties list.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryThemeColorPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ThemeColorType > value)
	{
		return JBool(setThemeColorPropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalThemeColorPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ThemeColorType > value, obj_ptr<ThemeColorType > defaultValue)
	{
		return JBool(setThemeColorPropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property into the properties list <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setThemeColorPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<ThemeColorType > value, obj_ptr<ThemeColorType > defaultValue, JBool force)
	{
		JBool set = false;
		if (( __NULL_VALUE != value ) && ( force || ( !value->equals(defaultValue) ) ))
		{
			if (value->isHexVal())
			{
				properties->setProperty(key,getPaddedString(java::lang::Integer::toHexString(value->getColor()),COLOR_VALUE_STRING_LENGTH,COLOR_VALUE_PADDING_CHAR,false));
			}
			else
			{
				properties->setProperty(key,value->getEnumVal()->name());
			}
			set = true;
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
	 * value.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<UniversalMeasure > value, obj_ptr<UniversalMeasure > defaultValue)
	{
		return JBool(setUniversalMeasurePropertyValue(properties,key,value,defaultValue,false));
	}
	
	
	/* 
	 * This method sets the named property to the specified value in Universal Measures.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<UniversalMeasure > value)
	{
		return JBool(setUniversalMeasurePropertyValue(properties,key,value,__NULL_VALUE,true));
	}
	
	
	/* 
	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
	 * value or if the force argument is set to True.
	 * 
	 * @param properties Properties object to contain the key-value pair.
	 * @param key The key to associate with the specified value.
	 * @param value The value to store for the specified key.
	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
	 * 
	 * @return True if the value was stored, False if the value was not stored due to it being the default.
	 */
	JBool DOMHelper::setUniversalMeasurePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<UniversalMeasure > value, obj_ptr<UniversalMeasure > defaultValue, JBool force)
	{
		JBool set = false;
		obj_ptr<java::lang::String > valueToWrite = CONDITIONAL_EXPRESSION((( __NULL_VALUE != value )) , value->getValue() , __NULL_VALUE);
		obj_ptr<java::lang::String > defValue = CONDITIONAL_EXPRESSION((( __NULL_VALUE != defaultValue )) , defaultValue->getValue() , __NULL_VALUE);
		if (__NULL_VALUE != valueToWrite)
		{
			if (force || ( !force && !valueToWrite->equals(defValue) ))
			{
				properties->setProperty(key,valueToWrite);
				set = true;
			}
		}
		return JBool(set);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a float.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @param Float The value that should be used if the property does not exist.
	 * @return Float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Float > DOMHelper::getFloatPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<java::lang::Float > defaultValue)
	{
		obj_ptr<java::lang::Float > val = defaultValue;
		if (__NULL_VALUE != properties)
		{
			obj_ptr<java::lang::String > sval = properties->getProperty(key);
			if (__NULL_VALUE != sval)
			{
				try
				{
					val = java::lang::Float::parseFloat(sval);
				}
				catch (obj_ptr<NumberFormatException > e)
				{
					if (0 == sval->compareToIgnoreCase(DOUBLE_INFINITY))
					{
						val = java::lang::Float::POSITIVE_INFINITY;
					}
					else
					{
						if (QOConstants::ASSERTS)
						{
							if ( !(false) )
							{
								__X_THROW(new java::lang::AssertionError());
							}
						}
					}
				}
			}
		}
		return obj_ptr<java::lang::Float >(val);
	}
	
	
	/* 
	 * This method retrieves the named property from the properties list and attempts to convert it to a float.
	 * 
	 * @param properties Properties object containing key-value pairs.
	 * @param key String representing the key of the property value to retrieve.
	 * @return Float representation of the value retrieved from Properties using the specified key.
	 */
	obj_ptr<java::lang::Float > DOMHelper::getFloatPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
	{
		return obj_ptr<java::lang::Float >(getFloatPropertyValue(properties,key,(JFloat)0));
	}
	
//	
//	/* 
//	 * This method sets the named property to the specified value <strong>only</strong> if it differs from the default
//	 * value.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
//	 * 
//	 * @see OOD Section 19.7.39 ST_TLTimeAnimateValueTime (Animation Time) in "ECMA-376, 2nd Ed, Part 1 - Fundamentals
//	 *      And Markup Language Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setOptionalPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<AnimationTime > value, obj_ptr<AnimationTime > defaultValue)
//	{
//		return JBool(setAnimationTimePropertyValue(properties,key,value,defaultValue,false));
//	}
//	
//	
//	/* 
//	 * This method sets the named property to the specified value in AnimationTime format.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * 
//	 * @see OOD 19.7.39 ST_TLTimeAnimateValueTime (Animation Time) in "ECMA-376, 2nd Ed, Part 1 - Fundamentals And Markup
//	 *      Language Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setMandatoryPropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<AnimationTime > value)
//	{
//		return JBool(setAnimationTimePropertyValue(properties,key,value,__NULL_VALUE,true));
//	}
//	
//	
//	/* 
//	 * This method sets the named property to the specified value if the Percentage value, to be interpreted as a
//	 * AnimationTime, <strong>only</strong> if it differs from the default value or if the force argument is set to True.
//	 * 
//	 * @param properties Properties object to contain the key-value pair.
//	 * @param key The key to associate with the specified value.
//	 * @param value The value to store for the specified key.
//	 * @param defaultValue The default value that determines if the key-value pair will be stored or ignored.
//	 * @param force True if the value should be stored regardless if the defaultValue is equivalent to the value.
//	 * 
//	 * @see OOD Section 19.7.39 ST_TLTimeAnimateValueTime (Animation Time) in "ECMA-376, 2nd Ed, Part 1 - Fundamentals
//	 *      And Markup Language Reference"
//	 * 
//	 * @return True if the value was stored, False if the value was not stored due to it being the default.
//	 */
//	JBool DOMHelper::setAnimationTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<AnimationTime > value, obj_ptr<AnimationTime > defaultValue, JBool force)
//	{
//		JBool set = false;
//		obj_ptr<java::lang::String > valueToWrite = CONDITIONAL_EXPRESSION((__NULL_VALUE != value) , value->getStringValue() , __NULL_VALUE);
//		obj_ptr<java::lang::String > defValue = CONDITIONAL_EXPRESSION((__NULL_VALUE != defaultValue) , defaultValue->getStringValue() , __NULL_VALUE);
//		if (__NULL_VALUE != valueToWrite)
//		{
//			if (force || ( !force && !valueToWrite->equals(defValue) ))
//			{
//				properties->setProperty(key,valueToWrite);
//				set = true;
//			}
//		}
//		return JBool(set);
//	}
//	
//	
//	/* 
//	 * This method retrieves the named property from the properties list and attempts to convert it to a String assuming
//	 * it is a AnimationTime, if the property does not exist in the properties list it returns 0.
//	 * 
//	 * @param properties Properties object containing key-value pairs.
//	 * @param key String representing the key of the property value to retrieve.
//	 * 
//	 * @return String representation of the value retrieved from Properties using the specified key.
//	 */
//	obj_ptr<AnimationTime > DOMHelper::getAnimationTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key)
//	{
//		return obj_ptr<AnimationTime >(getAnimationTimePropertyValue(properties,key,__NULL_VALUE));
//	}
//	
//	
//	/* 
//	 * This method retrieves the named property from the properties list and attempts to convert it to a String assuming
//	 * it is a percentage, if the property does not exist in the properties list it returns the default value provided.
//	 * 
//	 * @param properties Properties object containing key-value pairs.
//	 * @param key String representing the key of the property value to retrieve.
//	 * @param defaultValue The value that should be used if the property does not exist.
//	 * 
//	 * @return String representation of the value retrieved from Properties using the specified key.
//	 */
//	obj_ptr<AnimationTime > DOMHelper::getAnimationTimePropertyValue(obj_ptr<Properties > properties, obj_ptr<java::lang::String > key, obj_ptr<AnimationTime > defaultValue)
//	{
//		obj_ptr<AnimationTime > val = defaultValue;
//		if (__NULL_VALUE != properties)
//		{
//			obj_ptr<java::lang::String > sval = properties->getProperty(key);
//			if (__NULL_VALUE != sval)
//			{
//				val = obj_ptr<AnimationTime >( new AnimationTime(sval));
//			}
//		}
//		return obj_ptr<AnimationTime >(val);
//	}
//	
//	
	JInt DOMHelper::getClassSerialId()
	{
		return (m_serial_id);
	}
	
	
	JBool  DOMHelper::isInstanceOf(JInt serialId)
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

