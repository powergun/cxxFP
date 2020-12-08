//
// Created by weining on 9/5/20.
//

#ifndef C_PERFORMANCE_AUTO_TIMER_H
#define C_PERFORMANCE_AUTO_TIMER_H

#include <string>
#include <iostream>
#include <chrono>
#include <utility>
#include <iomanip>

struct AutoTimer
{
    std::string label{};
    std::chrono::time_point< std::chrono::high_resolution_clock >
        begin{};
    std::ostream &os;
    std::size_t *p_out{ nullptr };
    std::size_t target{};

    explicit AutoTimer( std::string s, std::ostream &os_ = std::cout )
        : label{ std::move( s ) }, os{ os_ }
    {
        begin = std::chrono::high_resolution_clock::now();
    }

    explicit AutoTimer( std::string s,
                        std::size_t *out,
                        std::size_t comparison_target = 0,
                        std::ostream &os_ = std::cout )
        : label( std::move( s ) )
        , p_out( out )
        , target{ comparison_target }
        , os{ os_ }
    {
        begin = std::chrono::high_resolution_clock::now();
    }

    ~AutoTimer()
    {
        using namespace std;
        using namespace chrono;
        auto d{ high_resolution_clock::now() - begin };
        std::size_t count =
            std::chrono::duration_cast< microseconds >( d ).count();
        if ( p_out )
        {
            *p_out = count;
        }
        std::cout.imbue( std::locale( "" ) );
        if ( !label.empty() )
        {
            os << label << " ";
        }
        if ( target )
        {
            double speed_up = static_cast< double >( target )
                              / static_cast< double >( count );
            os << count << " micro seconds, speedup: " << speed_up
               << '\n';
        }
        else
        {
            os << std::fixed << count << " micro-secs" << '\n';
        }
    }
};

#endif  // C_PERFORMANCE_AUTO_TIMER_H
