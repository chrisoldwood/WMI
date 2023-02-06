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
#include <WCL/VariantVector.hpp>
#include <algorithm>
#include <Core/Functor.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The base class for all type-specific WMI objects.
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
	static Iterator selectAll(Connection& connection);

	//! Select those objects of the derived type matching the predicate.
	static Iterator selectWhere(Connection& connection, const tstring& predicate);

	//! Refresh the state of the object.
	void refresh();
};

////////////////////////////////////////////////////////////////////////////////
//! Predicate for comparing wide character strings (e.g. BSTR) by value.

CORE_DEFINE_PREDICATE(WideStringComparator, const wchar_t*, value, rhs)
{
	return wcscmp(rhs, value) == 0;
}
CORE_END_PREDICATE

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
		WCL::Variant derivation;
		getProperty(TXT("__DERIVATION"), derivation);
		WCL::VariantVector<BSTR> classNames(derivation);
		if (std::find_if(classNames.begin(), classNames.end(), WideStringComparator(T2W(expectedClassName))) == classNames.end())
		{
			throw Core::BadLogicException(Core::fmt(TXT("Invalid WMI class '%s', expected '%s' or one derived from it"),
						actualClassName.c_str(), expectedClassName));
		}
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
inline typename TypedObject<T>::Iterator TypedObject<T>::selectAll(Connection& connection)
{
	tstring query = Core::fmt(TXT("SELECT * FROM %s"), T::WMI_CLASS_NAME);

	return connection.execQuery(query.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Select those objects of the derived type matching the predicate.

template <typename T>
inline typename TypedObject<T>::Iterator TypedObject<T>::selectWhere(Connection& connection, const tstring& predicate)
{
	tstring query = Core::fmt(TXT("SELECT * FROM %s WHERE %s"), T::WMI_CLASS_NAME, predicate.c_str());

	return connection.execQuery(query.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Refresh the state of the object.

template <typename T>
inline void TypedObject<T>::refresh()
{
	Object::refresh();
}

//namespace WMI
}

#endif // WMI_TYPEDOBJECT_HPP
