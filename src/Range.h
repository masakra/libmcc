/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃                             ________________                                ┃
 ┃ _______ ________________    ___  /__(_)__  /______________ ____________  __ ┃
 ┃ __  __ `__ \  ___/  ___/    __  /__  /__  __ \_  ___/  __ `/_  ___/_  / / / ┃
 ┃ _  / / / / / /__ / /__      _  / _  / _  /_/ /  /   / /_/ /_  /   _  /_/ /  ┃
 ┃ /_/ /_/ /_/\___/ \___/      /_/  /_/  /_.___//_/    \__,_/ /_/    _\__, /   ┃
 ┃                                                                   /____/    ┃
 ┠─────────────────────────────────────────────────────────────────────────────┨
 ┃ Copyright © 2016, Sergey N Chursanov (masakra@mail.ru)                      ┃
 ┃ All rights reserved.                                                        ┃
 ┃                                 BSD license                                 ┃
 ┃                                                                             ┃
 ┃ Redistribution and use in source and binary forms, with or without          ┃
 ┃ modification, are permitted provided that the following conditions are met: ┃
 ┃                                                                             ┃
 ┃ 1. Redistributions of source code must retain the above copyright notice,   ┃
 ┃ this list of conditions and the following disclaimer.                       ┃
 ┃                                                                             ┃
 ┃ 2. Redistributions in binary form must reproduce the above copyright        ┃
 ┃ notice, this list of conditions and the following disclaimer in the         ┃
 ┃ documentation and/or other materials provided with the distribution.        ┃
 ┃                                                                             ┃
 ┃ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" ┃
 ┃ AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   ┃
 ┃ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  ┃
 ┃ ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   ┃
 ┃ LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         ┃
 ┃ CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        ┃
 ┃ SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    ┃
 ┃ INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     ┃
 ┃ CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     ┃
 ┃ ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  ┃
 ┃ POSSIBILITY OF SUCH DAMAGE.                                                 ┃
 ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
#pragma once

#include <initializer_list>
#include <iterator>
#include <limits>

#include <QString>

template < class T >
class Range
{
  public:
    explicit Range()
      : m_min( std::numeric_limits< T >::max() )
      , m_max( std::numeric_limits< T >::lowest() )
    {}

    explicit Range( T min, T max )
      : m_min( min )
      , m_max( max )
    {}

    explicit Range( T length )
      : m_min( length / -2. )
      , m_max( -m_min )
    {
      if ( m_min > m_max )
        std::swap( m_min, m_max );
    }

    Range( std::initializer_list< T > init_list )
      : m_min( *std::begin( init_list ) )
      , m_max( *std::next( std::begin( init_list ) ) )
    {}

    T min() const
    {
      return m_min;
    }

    T max() const
    {
      return m_max;
    }

    bool contains( T v ) const
    {
      return m_min <= v &&
                 v <= m_max;
    }
    /** Расширить диапазон если \a v выходит за рамки диапазона
      */
    void expand( T v )
    {
      if ( m_min > v )
        m_min = v;
      if ( m_max < v )
        m_max = v;
    }

    Range< T > & operator << ( T v )
    {
      expand( v );
      return *this;
    }

    bool operator < ( const Range< T > & other ) const
    {
      return length() < other.length();
    }

    /*
    Range< T > & operator = ( const Range< T > & other )
    {
      m_min = other.m_min;
      m_max = other.m_max;
      return *this;
    }
    */

    void expand( const Range< T > & range )
    {
      if ( range.isValid() ) {
        expand( range.min() );
        expand( range.max() );
      }
    }

    bool isNull() const
    {
      return m_min == m_max;
    }

    bool isValid() const
    {
      return m_min <= m_max;
    }

    T length() const
    {
      return m_max - m_min;
    }

    virtual QString toString() const
    {
      return QString("%1 - %2")
        .arg( m_min )
        .arg( m_max );
    };

  private:
    T m_min,
      m_max;
};

