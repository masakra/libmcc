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
#include "sreal.h"

#include <QtGlobal>
#include <QJsonValue>

#include <QtDebug>

QDebug
operator << ( QDebug debug, sreal val )
{
  debug.noquote() << QString::number( val, 'f', 1 );

  return debug;
}

sreal::sreal()
  : m_value( 0 )
{
}

sreal::sreal( double val )
  : m_value( qRound( val * 10 ) )
{
}

sreal::operator double() const
{
  return m_value / 10.;
}

sreal::operator QVariant() const
{
  return QVariant( operator double() );
}

sreal::operator QJsonValue() const
{
  return QJsonValue( operator double() );
}

bool
sreal::operator == ( sreal other ) const
{
  return m_value == other.m_value;
}

bool sreal::operator != ( sreal other ) const
{
  return m_value != other.m_value;
}

bool
sreal::operator < ( sreal other ) const
{
  return m_value < other.m_value;
}

bool
sreal::operator < ( qreal val ) const
{
  return operator qreal() < val;
}

bool
sreal::operator <= ( sreal other ) const
{
  return m_value <= other.m_value;
}

bool
sreal::operator <= ( qreal other ) const
{
  return operator double() <= other;
}

bool
sreal::operator <= ( int other ) const
{
  return operator double() <= other;
}

bool
sreal::operator > ( sreal other ) const
{
  return m_value > other.m_value;
}

bool
sreal::operator > ( qreal other ) const
{
  return operator double() > other;
}

bool
sreal::operator >= ( sreal other ) const
{
  return m_value >= other.m_value;
}

sreal
sreal::operator -= ( qreal val )
{
  m_value -= qRound( val * 10. );
  return *this;
}

sreal
sreal::operator += ( qreal val )
{
  m_value += qRound( val * 10. );
  return *this;
}

sreal
sreal::operator -= ( sreal other )
{
  m_value -= other.m_value;
  return *this;
}

sreal
sreal::operator += ( sreal other )
{
  m_value += other.m_value;
  return *this;
}

