﻿// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include "../clock.hpp"
#include <ctime>


thread_local std::unique_ptr<FE::clock::char_type[]> FE::clock::tl_s_current_time( new FE::clock::char_type[_GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_]{(FE::clock::char_type)'\0'} );


void FE::clock::start_clock() noexcept { this->m_starting_point = std::chrono::steady_clock::now(); }

void FE::clock::end_clock() noexcept { this->m_ending_point = std::chrono::steady_clock::now(); }

FE::var::float64 FE::clock::get_delta_time() noexcept
{
    this->m_delta_time = this->m_ending_point - this->m_starting_point;
    return this->m_delta_time.count();
}

const FE::clock::char_type* FE::clock::get_current_local_time() noexcept
{
    auto l_current_time = std::chrono::system_clock::now();
    std::time_t l_current_time_t = std::chrono::system_clock::to_time_t(l_current_time);
    tm l_time;

#if _WINDOWS_64BIT_OS_
    localtime_s(&l_time, &l_current_time_t);
    std::strftime(tl_s_current_time.get(), _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "%Y-%B-%d-%A  %p %Ih.%Mm.%Ss", &l_time);

#elif _LINUX_64BIT_OS_ == 1
    std::strftime(tl_s_current_time.get(), _GET_CURRENT_LOCAL_TIME_BUFFER_SIZE_, "%Y-%B-%d-%A  %p %Ih.%Mm.%Ss", localtime_r(&l_current_time_t, &l_time));
#endif

    return tl_s_current_time.get();
}




#undef _CRT_SECURE_NO_WARNINGS