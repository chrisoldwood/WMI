////////////////////////////////////////////////////////////////////////////////
//! \file   Object.cpp
//! \brief  The Object class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Object.hpp"
#include "Exception.hpp"
#include <WCL/VariantVector.hpp>
#include <Core/StringUtils.hpp>
#include <iterator>
#include <algorithm>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Object::Object()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object and connection.

Object::Object(IWbemClassObjectPtr object, const Connection& connection)
	: m_object(object)
	, m_connection(connection)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Object::~Object()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the object has the named property.

bool Object::hasProperty(const tstring& name) const
{
	ASSERT(m_object.get() != nullptr);

	// Request the property names from the underlying object.
	SAFEARRAY* array = nullptr;

	HRESULT result = m_object->GetNames(nullptr, ALL_PROPERTIES, nullptr, &array);

	if (FAILED(result))
		throw Exception(result, m_object, TXT("Failed to retrieve the objects' property names"));

	// Copy the property names to the output buffer.
	WCL::VariantVector<BSTR> strings(array, VT_BSTR);	

	return (std::find(strings.begin(), strings.end(), name) != strings.end());
}

////////////////////////////////////////////////////////////////////////////////
//! Get the names of the supported properties.

size_t Object::getPropertyNames(PropertyNames& names, PropertyTypes types) const
{
	ASSERT(m_object.get() != nullptr);

	// Request the property names from the underlying object.
	SAFEARRAY* array = nullptr;

	HRESULT result = m_object->GetNames(nullptr, types, nullptr, &array);

	if (FAILED(result))
		throw Exception(result, m_object, TXT("Failed to retrieve the objects' property names"));

	// Copy the property names to the output buffer.
	WCL::VariantVector<BSTR> strings(array, VT_BSTR);	

	std::copy(strings.begin(), strings.end(), std::insert_iterator<PropertyNames>(names, names.end()));

	return names.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the value for a property. This is the generic method used to access a
//! property when the return value type is unknown.

void Object::getProperty(const tstring& name, WCL::Variant& value) const
{
	HRESULT result = m_object->Get(WCL::ComStr(name).Get(), 0, &value, nullptr, nullptr);

	if (FAILED(result))
		throw Exception(result, m_object, TXT("Failed to retrieve an objects' property value"));
}

////////////////////////////////////////////////////////////////////////////////
//! Create the object used to pass arguments to a method.

IWbemClassObjectPtr Object::createArgumentsObject(const tstring& className, const tstring& methodName) const
{
	IWbemServicesPtr    connection = m_connection.get();
	WCL::ComStr         comClassName(className);
	IWbemClassObjectPtr objectClass;

	HRESULT result = connection->GetObject(comClassName.Get(), 0, nullptr, AttachTo(objectClass), nullptr);

	if (FAILED(result))
	{
		const tstring message = Core::fmt(TXT("Failed to get WMI class definition for '%s'"), className.c_str());
		throw Exception(result, connection, message.c_str());
	}

	WCL::ComStr         comMethodName(methodName);
	IWbemClassObjectPtr arguments;

	result = objectClass->GetMethod(comMethodName.Get(), 0, AttachTo(arguments), nullptr);

	if (FAILED(result))
	{
		const tstring message = Core::fmt(TXT("Failed to create WMI arguments object for method '%s'"), methodName.c_str());
		throw Exception(result, connection, message.c_str());
	}

	return arguments;
}

////////////////////////////////////////////////////////////////////////////////
//! Execute a method on the object.

void Object::execMethod(const tchar* method, WCL::Variant& returnValue)
{
	ASSERT(m_connection.isOpen());

	Connection::execMethod(m_connection.get(), get(), relativePath().c_str(), method, returnValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Execute a method on the object.

void Object::execMethod(const tchar* method, IWbemClassObjectPtr arguments, WCL::Variant& returnValue)
{
	ASSERT(m_connection.isOpen());

	Connection::execMethod(m_connection.get(), get(), relativePath().c_str(), method, arguments, returnValue);
}

////////////////////////////////////////////////////////////////////////////////
//! Set an argument's value.

void Object::setArgument(IWbemClassObjectPtr arguments, const tstring& name, const WCL::Variant& value)
{
	WCL::ComStr comName(name);

	HRESULT result = arguments->Put(comName.Get(), 0, const_cast<WCL::Variant*>(&value), 0);

	if (FAILED(result))
	{
		const tstring message = Core::fmt(TXT("Failed to set '%s' argument"), name.c_str());
		throw Exception(result, arguments, message.c_str());
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Refresh the state of the object.

void Object::refresh()
{
	m_object = m_connection.getObject(relativePath()).get();
}

//namespace WMI
}
