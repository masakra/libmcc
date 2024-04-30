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
#include "ByteArray.h"

#include "sreal.h"

QSysInfo::Endian
ByteArray::s_endian{ QSysInfo::BigEndian };

ByteArray::ByteArray( const QByteArray & ba )
  : QByteArray( ba )
{
}

ByteArray::ByteArray( qsizetype size, char ch/*= '\0'*/)
  : QByteArray( size, ch )
{
}

void
ByteArray::setDefaultEndian( QSysInfo::Endian endian ) // static
{
  s_endian = endian;
}

bool
ByteArray::bitAt( qsizetype offset ) const
{
  const qsizetype byte = offset >> 3;   /// делить на 8
  const int mask = 1 << ( offset & 7 ); /// сдвинуть на остаток от деления на 8

  return at( byte ) & mask;
}

short
ByteArray::shortAt( qsizetype offset, QSysInfo::Endian endian/*= s_endian*/)
  const
{
  return valueAt< short >( offset, endian );
}

void
ByteArray::setShortAt( short value, qsizetype offset, QSysInfo::Endian endian/*=
  s_endian*/)
{
  setValueAt< short >( value, offset, endian );
}

sreal
ByteArray::srealAt( qsizetype offset, QSysInfo::Endian endian/*= s_endian*/)
  const
{
  return shortAt( offset, endian ) / 10.;
}

void
ByteArray::setSrealAt( sreal value, qsizetype offset, QSysInfo::Endian endian/*=
  s_endian*/)
{
  setValueAt< short >( qRound( value * 10 ), offset, endian );
}


ByteArray
ByteArray::toHex( char separator/*= '.'*/)const
{
  return QByteArray::toHex( separator );
}

