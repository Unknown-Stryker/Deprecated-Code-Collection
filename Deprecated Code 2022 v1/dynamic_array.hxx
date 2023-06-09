﻿#pragma once
#ifndef _DYNAMIC_ARRAY_HXX_
#define _DYNAMIC_ARRAY_HXX_
// UNKNOWN STRYKER and Hojin Joey Lee are the same person
// Copyright © 2022 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2022 Hojin Joey Lee. All Rights Reserved
#include "common_definitions.h"
#include"typeinfo.h"
using FFF::compare_data_types;
using FFF::GET_type_name;
using FFE::TYPE_COMPARISON_RESULT;

#include "element.hxx"
using FTS::element;
using FFC::mstring;

const index AUTO_INSERTION_FAILURE = 18446744073709551615;


FROGMAN_TEMPLATE_CLASS_LIBRARY
{
	template <typename T>
	frogman_fundamental_class dynamic_array
	{
	private_member_variables:
		element<T>* m_array_pointer;

		length m_array_size;
		length m_capacity;

		length m_divider;

		index m_emplace_back_idx;
		index m_iterate_idx;

		T m_null;

	constructors:
		dynamic_array(length initial_length_param = 10);
		dynamic_array(length initial_length_param, T initial_val_param);

	destructor:
		~dynamic_array();

	GETTERS:
		length GET_total_length()  const;
		length GET_capacity()  const;
		length GET_number_of_elements() const;
		mstring GET_tag(index Index_param)  const;
		
	SETTERS:
		void SET_capacity_by_percent(length Percent_Param = 50);

	public_operators:
		T& operator[](index Index_param);
		T& operator[](mstring Tag_param);

	public_methods:
		void extend();
		void resize(length Size_param);

		void shrink_to_fit();

		void insert(index Index_param, T Data_param);
		void insert(index Index_param, T Data_param, mstring Tag_param);
		void insert(index Index_param, mstring Tag_param);

		void emplace_back(T Data_param);
		void emplace_back(T Data_param, mstring Tag_param);

		T& iterate();

		friend void swap(dynamic_array& A, dynamic_array& B);

		T* copy_primitive_array();
		element<T>* copy_array();
	};


	template<typename T>
	inline dynamic_array<T>::dynamic_array(length initial_length_param)
		: m_array_pointer(nullptr), m_array_size(initial_length_param), m_capacity(initial_length_param), m_divider(2), m_emplace_back_idx(0), m_iterate_idx(0), m_null()
	{
		if (initial_length_param < 10) { initial_length_param = 10; }
		this->m_array_pointer = new element<T>[initial_length_param + 1];
	}

	template<typename T>
	inline dynamic_array<T>::dynamic_array(length initial_length_param, T initial_val_param)
		: m_array_pointer(nullptr), m_array_size(initial_length_param), m_capacity(initial_length_param), m_divider(2), m_emplace_back_idx(0), m_iterate_idx(0), m_null()
	{
		if (initial_length_param < 10) { initial_length_param = 10; }
		this->m_array_pointer = new element[initial_length_param + 1] { initial_val_param };
	}

	template<typename T>
	inline dynamic_array<T>::~dynamic_array() 
	{ 
		if ( this->m_array_pointer == nullptr ) { return; }
		delete[] this->m_array_pointer; 
	}

	template<typename T>
	inline length dynamic_array<T>::GET_total_length() const { this->m_array_size; }

	template<typename T>
	inline length dynamic_array<T>::GET_capacity()  const { return this->m_capacity; }

	template<typename T>
	inline void dynamic_array<T>::SET_capacity_by_percent(length Percent_Param)
	{
		this->m_divider = 100 / Percent_Param;
		this->m_capacity = this->m_array_size / this->m_divider;
	}

	template<typename T>
	inline length dynamic_array<T>::GET_number_of_elements() const { return this->m_emplace_back_idx; }

	template<typename T>
	inline mstring dynamic_array<T>::GET_tag(index Index_param)  const { return this->m_array_pointer[Index_param].m_tag; }

	template<typename T>
	inline void dynamic_array<T>::extend()
	{
		if (this->m_array_pointer == nullptr) { return; }

		element<T>* l_allocator = new element<T>[this->m_array_size + this->m_capacity + 1];

		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			l_allocator[idx] = this->m_array_pointer[idx];
		}

		delete[] this->m_array_pointer;

		this->m_array_pointer = l_allocator;

		this->m_array_size = this->m_array_size + this->m_capacity;

		this->m_capacity = this->m_array_size / this->m_divider;
	}

	template<typename T>
	inline void dynamic_array<T>::resize(length Size_param)
	{
		if (this->m_array_pointer == nullptr) { return; }

		element<T>* l_allocator = new element<T>[Size_param + 1];

		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			l_allocator[idx] = this->m_array_pointer[idx];
		}

		delete[] this->m_array_pointer;

		this->m_array_pointer = l_allocator;

		this->m_array_size = Size_param;

		this->m_capacity = this->m_array_size / this->m_divider;
	}

	template<typename T>
	inline void dynamic_array<T>::shrink_to_fit()
	{
		if (this->m_array_pointer == nullptr) { return; }
		if (FFF::Is_it__ptr(this->m_array_pointer[0].m_data) == false) { return; }

		bool* l_Is_it_valid = nullptr;
		length l_is_it_new = 0;
		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			if (this->m_array_pointer[idx].m_data == nullptr)
			{
				++l_is_it_new;
			}
		}

		if (l_is_it_new == this->m_array_size) { return; }
		else if (l_is_it_new == 0) { return; }

		// Allocate Authenticator
		this->m_Is_it_valid = new bool[this->m_array_size + 1];

		// Mark Valid Pointers
		length l_valid_elements = 0;
		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			if (this->m_array_pointer[idx].m_data != nullptr)
			{
				this->m_Is_it_valid[idx] = true;
				++l_valid_elements;
			}
		}

		// Allocate New dynamic_array
		element<T>* l_allocator = new element<T>[l_valid_elements + 1];
		index alloctr_idx = 0;
	
		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			if (this->m_Is_it_valid[idx] == true)
			{
				l_allocator[alloctr_idx].m_data = this->m_array_pointer[idx].m_data;
				++alloctr_idx;
			}
		}

		delete[] this->m_array_pointer;
		this->m_array_pointer = this->m_allocator;
		this->m_array_size = l_valid_elements;
		delete[] this->m_Is_it_valid;
		this->m_Is_it_valid = nullptr;
	}


	template<typename T>
	inline void dynamic_array<T>::insert(index Index_param, T Data_param)
	{
		if (this->m_array_pointer == nullptr) { return; }

		if (Index_param < this->m_array_size)
		{
			this->m_array_pointer[Index_param].m_data = Data_param;
			return;
		}

		for (; this->m_array_size <= Index_param; this->extend()) {}

		if (this->m_array_size > Index_param)
		{
			this->insert(Index_param, Data_param);
		}
	}

	template<typename T>
	inline void dynamic_array<T>::insert(index Index_param, T Data_param, mstring Tag_param)
	{
		if (this->m_array_pointer == nullptr) { return; }

		if (Index_param < this->m_array_size)
		{
			this->m_array_pointer[Index_param].m_data = Data_param;
			this->m_array_pointer[Index_param].m_tag = Tag_param;
			return;
		}

		for (; this->m_array_size <= Index_param; this->extend()) {}

		if (this->m_array_size > Index_param)
		{
			this->insert(Index_param, Data_param, Tag_param);
		}
	}

	template<typename T>
	inline void dynamic_array<T>::insert(index Index_param, mstring Tag_param)
	{
		if (this->m_array_pointer == nullptr) { return; }

		if (Index_param < this->m_array_size)
		{
			this->m_array_pointer[Index_param].m_tag = Tag_param;
			return;
		}

		for (; this->m_array_size <= Index_param; this->extend()) {}

		if (this->m_array_size > Index_param)
		{
			this->insert(Index_param, Tag_param);
		}
	}


	template<typename T>
	inline void dynamic_array<T>::emplace_back(T Data_param)
	{
		if (this->m_array_pointer == nullptr) { return; }
	
		if (this->m_emplace_back_idx >= this->m_array_size)
		{
			this->insert(this->m_emplace_back_idx, Data_param);
			++this->m_emplace_back_idx;
			return;
		}
	
		this->m_array_pointer[this->m_emplace_back_idx].m_data = Data_param;
	
		++this->m_emplace_back_idx;

	}

	template<typename T>
	inline void dynamic_array<T>::emplace_back(T Data_param, mstring Tag_param)
	{
		if (this->m_array_pointer == nullptr) { return; }

		if (this->m_emplace_back_idx >= this->m_array_size)
		{
			this->insert(this->m_emplace_back_idx, Data_param, Tag_param);
			++this->m_emplace_back_idx;
			return;
		}

		this->m_array_pointer[this->m_emplace_back_idx].m_data = Data_param;
		this->m_array_pointer[this->m_emplace_back_idx].m_tag = Tag_param;
	
		++this->m_emplace_back_idx;
	}
	
	template<typename T>
	inline T& dynamic_array<T>::iterate()
	{
		if (this->m_array_pointer == nullptr) { return; }
	
		if (this->m_iterate_idx >= this->m_array_size)
		{
			this->m_iterate_idx = 0;
		}
	
		++this->m_iterate_idx;
		return this->m_array_pointer[this->m_iterate_idx - 1].m_data;
	}
	
	
	template<typename T>
	inline T& dynamic_array<T>::operator[](index Index_param)
	{
		if (this->m_array_pointer == nullptr) { return m_null; }
	
		return this->m_array_pointer[Index_param].m_data;
	}
	
	template<typename T>
	inline T& dynamic_array<T>::operator[](mstring Tag_param)
	{
		if (this->m_array_pointer == nullptr) { return m_null; }
	
		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			if (this->m_array_pointer[idx].m_tag == Tag_param)
			{
				return this->m_array_pointer[idx].m_data;
			}
		}
	
		return this->m_null;
	}
	
	template<typename T>
	inline void swap(dynamic_array<T>& A, dynamic_array<T>& B)
	{
		dynamic_array& Temporary = A;
	
		A = B;
	
		B = Temporary;
	}
	
	template<typename T>
	inline T* dynamic_array<T>::copy_primitive_array()
	{
		if (this->m_array_pointer == nullptr) { return nullptr; }
	
		T* new_array = new T[this->m_array_size + 1];

		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			new_array[idx] = this->m_array_pointer[idx].m_data;
		}
	
		return new_array;
	}
	
	template<typename T>
	inline element<T>* dynamic_array<T>::copy_array()
	{
		if (this->m_array_pointer == nullptr) { return nullptr; }
	
		element<T>* new_array = new element<T>[this->m_array_size + 1];
	
		for (index idx = 0; idx < this->m_array_size; ++idx)
		{
			new_array[idx] = this->m_array_pointer[idx];
		}
	
		return new_array;
	}
	
}
	
#endif
