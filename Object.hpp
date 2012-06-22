////////////////////////////////////////////////////////////////////////////////
//! \file   Object.hpp
//! \brief  The Object class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_OBJECT_HPP
#define WMI_OBJECT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ComPtr.hpp>
#include <wbemidl.h>
#include <set>
#include <WCL/Variant.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! An instance of a WMI Class.

class Object
{
public:
	//! The underlying COM type.
	typedef WCL::ComPtr<IWbemClassObject> IWbemClassObjectPtr;
	//! A set of property names.
	typedef std::set<tstring> PropertyNames;

	//! The property type query flags.
	enum PropertyTypes
	{
		ALL_PROPERTIES			= 0,
		NONSYSTEM_PROPERTIES	= WBEM_FLAG_NONSYSTEM_ONLY,
		LOCAL_PROPERTIES		= WBEM_FLAG_LOCAL_ONLY,
		PROPAGATED_PROPERTIES	= WBEM_FLAG_PROPAGATED_ONLY,
		SYSTEM_PROPERTIES		= WBEM_FLAG_SYSTEM_ONLY,
	};

public:
	//! Default constructor.
	Object();

	//! Construction from the underlying COM object.
	Object(IWbemClassObjectPtr object);

	//! Destructor.
	virtual ~Object();
	
	//
	// Object properties.
	//

	//! Get the names of the supported properties.
	size_t getPropertyNames(PropertyNames& names, PropertyTypes types = NONSYSTEM_PROPERTIES) const; // throw(WMI::Exception)

	//! Get the value for a property.
	void getProperty(const tstring& name, WCL::Variant& value) const; // throw(WMI::Exception)

	//! Get the property value for an object as a typed value.
	template<typename T>
	T getProperty(const tstring& name) const; // throw(WMI::Exception, ComException)

	//! Get the underlying COM object.
	IWbemClassObjectPtr get() const;

	//
	// Object methods.
	//

private:
	//
	// Members.
	// NB: mutable as COM interfaces are always non-const.
	//
	mutable IWbemClassObjectPtr	m_object;	//! The underlying COM object.
};

////////////////////////////////////////////////////////////////////////////////
//! Get the property value for an object as a typed value.

template<typename T>
inline T Object::getProperty(const tstring& name) const
{
	WCL::Variant value;

	getProperty(name, value);

	return WCL::getValue<T>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the underlying COM object.

inline Object::IWbemClassObjectPtr Object::get() const
{
	return m_object;
}

//namespace WMI
}

#endif // WMI_OBJECT_HPP
