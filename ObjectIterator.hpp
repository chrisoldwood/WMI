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

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The iterator type used for collections of WBEM Class Objects.

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
	ObjectIterator(IEnumWbemClassObjectPtr enumerator);

	//! Destructor.
	~ObjectIterator();
	
	//
	// Operators.
	//

	//! Dereference operator.
	Object operator*() const;

	//! Advance the iterator.
	void operator++();

	//
	// Methods.
	//

	//! Compare to another iterator for equivalence.
	bool equals(const ObjectIterator& rhs) const;

private:
	//
	// Members.
	//
	IEnumWbemClassObjectPtr	m_enumerator;	//!< The underlyng WMI iterator.
	IWbemClassObjectPtr		m_value;		//!< The current iterator value.

	//
	// Internal methods.
	//

	//! Move the iterator forward.
	void increment();

	//! Move the iterator to the End.
	void reset();
};

////////////////////////////////////////////////////////////////////////////////
//! Dereference operator.

inline Object ObjectIterator::operator*() const
{
	ASSERT(m_value.get() != nullptr);

	return m_value;
}

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
