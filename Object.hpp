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

#include "Types.hpp"
#include <set>
#include <WCL/Variant.hpp>
#include "Connection.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! An instance of a WMI Class.

class Object
{
public:
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

	//! Construction from the underlying COM object and connection.
	Object(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~Object();

	//
	// Properties.
	//

	//! Get the underlying COM object.
	IWbemClassObjectPtr get() const;

	//! Get the underlying COM connection.
	const Connection& connection() const;

	//
	// WMI Object properties.
	//

	//! Query if the object has the named property.
	bool hasProperty(const tstring& name) const; // throw(WMI::Exception)

	//! Get the names of the supported properties.
	size_t getPropertyNames(PropertyNames& names, PropertyTypes types = NONSYSTEM_PROPERTIES) const; // throw(WMI::Exception)

	//! Get the value for a property.
	void getProperty(const tstring& name, WCL::Variant& value) const; // throw(WMI::Exception)

	//! Get the property value for an object as a typed value.
	template<typename T>
	T getProperty(const tstring& name) const; // throw(WMI::Exception, ComException)

	//
	// WMI Object property short-hands.
	//

	//! Full path to the class or instance - including server and namespace.
	tstring absolutePath() const;

	//! Relative path to the class or instance.
	tstring relativePath() const;

	//
	// WMI Object methods.
	//

	//! Create the object used to pass arguments to a method.
	IWbemClassObjectPtr createArgumentsObject(const tstring& className, const tstring& methodName) const; // throw(WMI::Exception)

	//! Execute a method on the object.
	void execMethod(const tchar* method, WCL::Variant& returnValue); // throw(WMI::Exception)

	//! Execute a method on the object.
	void execMethod(const tchar* method, IWbemClassObjectPtr arguments, WCL::Variant& returnValue); // throw(WMI::Exception)

	//! Set an argument's value.
	static void setArgument(IWbemClassObjectPtr arguments, const tstring& name, const WCL::Variant& value);

	//
	// Methods.
	//

	//! Refresh the state of the object.
	void refresh();

private:
	//
	// Members.
	// NB: mutable as COM interfaces are always non-const.
	//
	mutable IWbemClassObjectPtr	m_object;		//! The underlying COM object.
	Connection					m_connection;	//! The object's connection.
};

////////////////////////////////////////////////////////////////////////////////
//! Get the underlying COM object.

inline IWbemClassObjectPtr Object::get() const
{
	return m_object;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the underlying COM connection.

inline const Connection& Object::connection() const
{
	return m_connection;
}

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
//! Full path to the class or instance - including server and namespace.

inline tstring Object::absolutePath() const
{
	return getProperty<tstring>(TXT("__Path"));
}

////////////////////////////////////////////////////////////////////////////////
//! Relative path to the class or instance.

inline tstring Object::relativePath() const
{
	return getProperty<tstring>(TXT("__RelPath"));
}

//namespace WMI
}

#endif // WMI_OBJECT_HPP
