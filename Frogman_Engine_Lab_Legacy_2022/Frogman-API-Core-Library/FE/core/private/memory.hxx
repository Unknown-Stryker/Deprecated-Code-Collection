﻿#ifndef _MEMORY_HXX_
#define _MEMORY_HXX_
// Copyright © 2023~ UNKNOWN STRYKER. All Rights Reserved.
#include "../prerequisite_symbols.h"


BEGIN_NAMESPACE(FE)


enum struct MEMORY_ERROR_1XX : int16
{
	_NONE = 0,
	_ERROR_INVALID_SIZE = -100,
	_FATAL_ERROR_OUT_OF_RANGE = -101,
	_FATAL_ERROR_NULLPTR = -102
};

struct total_memory_utilization_data
{
	var::size_t _global_total_bytes = 0;
	var::size_t _thread_local_total_bytes = 0;

	var::size_t _global_total_bytes_by_type = 0;
	var::size_t _thread_local_total_bytes_by_type = 0;
};

struct global_memory_utilization
{
	var::size_t _global_total_bytes = 0;
	var::size_t _thread_local_total_bytes = 0;
};

struct type_memory_utilization
{
	var::size_t _global_total_bytes_by_type = 0;
	var::size_t _thread_local_total_bytes_by_type = 0;
};


END_NAMESPACE




BEGIN_NAMESPACE(FE::memory)


_MAYBE_UNUSED_ constexpr uint8 _BYTE_SIZE_ = 1;
_MAYBE_UNUSED_ constexpr uint8 _WORD_SIZE_ = 2;
_MAYBE_UNUSED_ constexpr uint8 _DWORD_SIZE_ = 4;
_MAYBE_UNUSED_ constexpr uint8 _QWORD_SIZE_ = 8;


// it is used when reserving memory of Frogman Engine API data containers.
struct reserve final
{
	var::uint64 _length = 0;
};

// it contains memory padding size.
struct align_null final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 0;
};

// it contains memory padding size.
struct align_2bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 2;
};

// it contains memory padding size.
struct align_4bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 4;
};

// it contains memory padding size.
struct align_8bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 8;
};

// it contains memory padding size.
struct align_16bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 16;
};

// it contains memory padding size.
struct align_32bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 32;
};

// it contains memory padding size.
struct align_64bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 64;
};

// it contains memory padding size.
struct align_128bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = 128;
};

// it contains memory padding size.
template<uint64 padding_size_p>
struct align_custom_bytes final
{
	_MAYBE_UNUSED_ static constexpr uint16 s_size = padding_size_p;
};


template <typename T, class padding_size = align_null>
struct alignas(padding_size::s_size) align
{
	T _content;
};


END_NAMESPACE
#endif
