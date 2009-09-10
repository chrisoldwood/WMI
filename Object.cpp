////////////////////////////////////////////////////////////////////////////////
//! \file   Object.cpp
//! \brief  The Object class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Object.hpp"
#include "Exception.hpp"
#include <WCL/VariantVector.hpp>
#include <Core/StringUtils.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Object::Object()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object.

Object::Object(IWbemClassObjectPtr object)
	: m_object(object)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Object::~Object()
{
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

//namespace WMI
}
