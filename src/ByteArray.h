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

#include <QByteArray>

#include <QtEndian>

#include "libmcc_export.h"

class sreal;

class LIBMCC_EXPORT ByteArray : public QByteArray
{
  private:
    static QSysInfo::Endian s_endian;

  public:
    using QByteArray::QByteArray;
    ByteArray( const QByteArray & ba );
    explicit ByteArray( qsizetype size, char ch = '\0');

    /** Устанавливает \a endian по-умолчанию для всех опеаций
      */
    static void setDefaultEndian( QSysInfo::Endian endian );

    template< class T >
    T valueAt( qsizetype offset, QSysInfo::Endian endian = s_endian ) const
    {
      return endian == QSysInfo::BigEndian ?
                                  qFromBigEndian< T >( data() + offset ) :
                                  qFromLittleEndian< T >( data() + offset );
    }

    template< class T >
    void setValueAt( T val, qsizetype offset, QSysInfo::Endian endian =
        s_endian )
    {
      endian == QSysInfo::BigEndian ?
                                  qToBigEndian< T >( val, data() + offset ) :
                                  qToLittleEndian< T >( val, data() + offset );
    }

    bool bitAt( qsizetype offset ) const;

    short shortAt( qsizetype offset, QSysInfo::Endian endian = s_endian ) const;

    void setShortAt( short value, qsizetype offset, QSysInfo::Endian endian =
        s_endian );

    sreal srealAt( qsizetype offset, QSysInfo::Endian endian = s_endian ) const;

    void setSrealAt( sreal value, qsizetype offset, QSysInfo::Endian endian =
        s_endian );

    ByteArray toHex( char separator = '.') const;
};

