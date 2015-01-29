////////////////////////////////////////////////////////////////////////////////
//! \file   TypedObject.hpp
//! \brief  The TypedObject class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_TYPEDOBJECT_HPP
#define WMI_TYPEDOBJECT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Object.hpp"
#include <Core/BadLogicException.hpp>
#include <Core/StringUtils.hpp>
#include "TypedObjectIterator.hpp"
#include "Connection.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for all type-specfic WMI objects.
//! \note The derived class must have a constant defined called WMI_CLASS_NAME
//! that this class can use to very the WMI object type and use in queries.

template <typename T>
class TypedObject : protected Object
{
public:
	//! A iterator for the derived type.
	typedef TypedObjectIterator<T> Iterator;

public:
	//! Construction from the underlying COM object and connection.
	TypedObject(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~TypedObject();
	
	//
	// Methods.
	//

	//! Select all objects of the derived type.
	static Iterator select(Connection& connection);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object and connection.

template <typename T>
inline TypedObject<T>::TypedObject(IWbemClassObjectPtr object, const Connection& connection)
	: Object(object, connection)
{
	tstring      actualClassName = getProperty<tstring>(TXT("__CLASS"));
	const tchar* expectedClassName = T::WMI_CLASS_NAME;

	if (actualClassName != expectedClassName)
	{
		throw Core::BadLogicException(Core::fmt(TXT("Invalid WMI class '%s', expected '%s'"),
					actualClassName.c_str(), expectedClassName));
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline TypedObject<T>::~TypedObject()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Select all objects of the derived type.

template <typename T>
inline typename TypedObject<T>::Iterator TypedObject<T>::select(Connection& connection)
{
	tstring query = Core::fmt(TXT("SELECT * FROM %s"), T::WMI_CLASS_NAME);

	return connection.execQuery(query.c_str());
}

//namespace WMI
}

#endif // WMI_TYPEDOBJECT_HPP
