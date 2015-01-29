////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectIterator.cpp
//! \brief  The ObjectIterator class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ObjectIterator.hpp"
#include "Exception.hpp"
#include <Core/BadLogicException.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor for the End iterator.

ObjectIterator::ObjectIterator()
	: m_enumerator()
	, m_connection()
	, m_value()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor for the Begin iterator.

ObjectIterator::ObjectIterator(IEnumWbemClassObjectPtr enumerator, const Connection& connection)
	: m_enumerator(enumerator)
	, m_connection(connection)
	, m_value()
{
	increment();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ObjectIterator::~ObjectIterator()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Dereference operator.

const Object& ObjectIterator::operator*() const
{
	if (m_value.get() == nullptr)
		throw Core::BadLogicException(TXT("Attempted to dereference end iterator"));

	return *m_value;
}

////////////////////////////////////////////////////////////////////////////////
//! Pointer-to-member operator.

const Object* ObjectIterator::operator->() const
{
	if (m_value.get() == nullptr)
		throw Core::BadLogicException(TXT("Attempted to dereference end iterator"));

	return m_value.get();
}

////////////////////////////////////////////////////////////////////////////////
//! Compare to another iterator for equivalence.

bool ObjectIterator::equals(const ObjectIterator& rhs) const
{
	// Comparing End iterators?
	if (m_enumerator.get() == nullptr)
		return (rhs.m_enumerator.get() == nullptr);

	return (m_enumerator.get() == rhs.m_enumerator.get());
}

////////////////////////////////////////////////////////////////////////////////
//! Move the iterator forward.

void ObjectIterator::increment()
{
	ASSERT(m_enumerator.get() != nullptr);

	// Request the next item.
	IWbemClassObjectPtr	value;
	ULONG				avail = 0;

	HRESULT result = m_enumerator->Next(WBEM_INFINITE, 1, AttachTo(value), &avail);

	if (FAILED(result))
		throw Exception(result, m_enumerator, TXT("Failed to advance the WMI object enumerator"));

	// Continued enumeration?
	if (avail != 0)
	{
		ASSERT(avail == 1);

		m_value.reset(new Object(value, m_connection));
	}
	// End reached.
	else
	{
		ASSERT(result == S_FALSE);

		reset();
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Move the iterator to the End.

void ObjectIterator::reset()
{
	m_value.reset();
	m_enumerator.Release();
}

//namespace WMI
}
