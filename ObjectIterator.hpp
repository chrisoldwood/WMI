////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectIterator.hpp
//! \brief  The ObjectIterator class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_OBJECTITERATOR_HPP
#define WMI_OBJECTITERATOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ComPtr.hpp>
#include <wbemidl.h>
#include "Object.hpp"
#include <Core/SharedPtr.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The iterator type used for collections of WBEM Class Objects.
//! \note Although the iterator is copyable it only creates a shallow copy of
//! the underlying COM object and so cannot be independently advanced.

class ObjectIterator
{
public:
	//! The underlying WMI iterator type.
	typedef WCL::ComPtr<IEnumWbemClassObject> IEnumWbemClassObjectPtr;
	//! The iterator value type.
	typedef WCL::ComPtr<IWbemClassObject> IWbemClassObjectPtr;

public:
	//! Constructor for the End iterator.
	ObjectIterator();

	//! Constructor for the Begin iterator.
	ObjectIterator(IEnumWbemClassObjectPtr enumerator); // throw(WMI::Exception)

	//! Destructor.
	~ObjectIterator();
	
	//
	// Operators.
	//

	//! Dereference operator.
	const Object& operator*() const;

	//! Pointer-to-member operator.
	const Object* operator->() const;

	//! Advance the iterator.
	void operator++(); // throw(WMI::Exception)

	//
	// Methods.
	//

	//! Compare to another iterator for equivalence.
	bool equals(const ObjectIterator& rhs) const;

private:
	//! The value shared pointer type.
	typedef Core::SharedPtr<Object> ValuePtr;

	//
	// Members.
	//
	IEnumWbemClassObjectPtr	m_enumerator;	//!< The underlyng WMI iterator.
	ValuePtr				m_value;		//!< The current iterator value.

	//
	// Internal methods.
	//

	//! Move the iterator forward.
	void increment();

	//! Move the iterator to the End.
	void reset();
};

////////////////////////////////////////////////////////////////////////////////
//! Advance the iterator.

inline void ObjectIterator::operator++()
{
	increment();
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for equivalence.

inline bool operator==(const ObjectIterator& lhs, const ObjectIterator& rhs)
{
	return lhs.equals(rhs);
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for difference.

inline bool operator!=(const ObjectIterator& lhs, const ObjectIterator& rhs)
{
	return !lhs.equals(rhs);
}

//namespace WMI
}

#endif // WMI_OBJECTITERATOR_HPP
