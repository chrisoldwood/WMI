////////////////////////////////////////////////////////////////////////////////
//! \file   TypedObjectIterator.hpp
//! \brief  The TypedObjectIterator class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_TYPEDOBJECTITERATOR_HPP
#define WMI_TYPEDOBJECTITERATOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "ObjectIterator.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! A type-safe version of ObjectIterator. Internally this uses ObjectIterator
//! and relies on the Win32_* WMI classes checking that they are being
//! constructed with a WMI object of the correct class.

template<typename T>
class TypedObjectIterator
{
public:
	//! The underlying WMI iterator type.
	typedef WCL::ComPtr<IEnumWbemClassObject> IEnumWbemClassObjectPtr;
	//! The iterator value type.
	typedef WCL::ComPtr<IWbemClassObject> IWbemClassObjectPtr;

public:
	//! Constructor for the End iterator.
	TypedObjectIterator();

	//! Constructor for the Begin iterator.
	TypedObjectIterator(IEnumWbemClassObjectPtr enumerator);

	//! Constructor for the Begin iterator.
	TypedObjectIterator(ObjectIterator enumerator);

	//! Destructor.
	~TypedObjectIterator();
	
	//
	// Operators.
	//

	//! Dereference operator.
	const T& operator*() const;

	//! Pointer-to-member operator.
	const T* operator->() const;

	//! Advance the iterator.
	void operator++();

	//
	// Methods.
	//

	//! Compare to another iterator for equivalence.
	bool equals(const TypedObjectIterator<T>& rhs) const;

private:
	//! The value shared pointer type.
	typedef Core::SharedPtr<T> ValuePtr;

	//
	// Members.
	//
	ObjectIterator	m_end;			//!< The underlyng end iterator.
	ObjectIterator	m_enumerator;	//!< The underlyng iterator.
	ValuePtr		m_value;		//!< The current iterator value.

	//
	// Internal methods.
	//

	//! Move the iterator forward.
	void increment();

	//! Move the iterator to the End.
	void reset();
};

////////////////////////////////////////////////////////////////////////////////
//! Constructor for the End iterator.

template<typename T>
TypedObjectIterator<T>::TypedObjectIterator()
	: m_enumerator()
	, m_value()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor for the Begin iterator.

template<typename T>
TypedObjectIterator<T>::TypedObjectIterator(IEnumWbemClassObjectPtr enumerator)
	: m_enumerator(enumerator)
	, m_value()
{
	increment();
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor for the Begin iterator.

template<typename T>
TypedObjectIterator<T>::TypedObjectIterator(ObjectIterator enumerator)
	: m_enumerator(enumerator)
	, m_value()
{
	if (m_enumerator != m_end)
		m_value.reset(new T(m_enumerator->get(), m_enumerator->connection()));
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template<typename T>
TypedObjectIterator<T>::~TypedObjectIterator()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Dereference operator.

template<typename T>
const T& TypedObjectIterator<T>::operator*() const
{
	if (m_value.get() == nullptr)
		throw Core::BadLogicException(TXT("Attempted to dereference end iterator"));

	return *m_value;
}

////////////////////////////////////////////////////////////////////////////////
//! Pointer-to-member operator.

template<typename T>
const T* TypedObjectIterator<T>::operator->() const
{
	if (m_value.get() == nullptr)
		throw Core::BadLogicException(TXT("Attempted to dereference end iterator"));

	return m_value.get();
}

////////////////////////////////////////////////////////////////////////////////
//! Compare to another iterator for equivalence.

template<typename T>
bool TypedObjectIterator<T>::equals(const TypedObjectIterator<T>& rhs) const
{
	// Comparing End iterators?
	if (m_enumerator == m_end)
		return (rhs.m_enumerator == rhs.m_end);

	return (m_enumerator == rhs.m_enumerator);
}

////////////////////////////////////////////////////////////////////////////////
//! Move the iterator forward.

template<typename T>
void TypedObjectIterator<T>::increment()
{
	ASSERT(m_enumerator != m_end);

	++m_enumerator;

	if (m_enumerator != m_end)
		m_value.reset(new T(m_enumerator->get(), m_enumerator->connection()));
	else
		reset();
}

////////////////////////////////////////////////////////////////////////////////
//! Advance the iterator.

template<typename T>
void TypedObjectIterator<T>::operator++()
{
	increment();
}

////////////////////////////////////////////////////////////////////////////////
//! Move the iterator to the End.

template<typename T>
void TypedObjectIterator<T>::reset()
{
	m_value.reset();
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for equivalence.

template<typename T>
bool operator==(const TypedObjectIterator<T>& lhs, const TypedObjectIterator<T>& rhs)
{
	return lhs.equals(rhs);
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for difference.

template<typename T>
bool operator!=(const TypedObjectIterator<T>& lhs, const TypedObjectIterator<T>& rhs)
{
	return !lhs.equals(rhs);
}

//namespace WMI
}

#endif // WMI_TYPEDOBJECTITERATOR_HPP
