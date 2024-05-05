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

#include <functional>
#include <QMap>
#include <QScopedPointer>
#include <QSettings>
#include <QString>
#include <QTimer>

#include "libmcc_export.h"

class StgsGroup;
class StgsValue;

using groupFunc = std::function< void() >;
using valueFunc = std::function< void( const QVariant &, const QVariant & ) >;

/** Wrapper under QSettings
  *
  * Provides pretty syntax:
  * 1. Settings parameter in form:
  *    stgs["Group"]("Param") = 456
  * 2. Get value in form:
  *    int i = stgs["Group"]("Param")
  * 3. Assgn callback for group changed:
  *      stgs["Group"].onChanged(
  *        []()
  *        {
  *          doSomething();
  *        });
  * 4. Assign callback for parameter changed:
  *      stgs["Group"]("Param").onChanged(
  *        []( const QVariant & new_val, const QVarant & old_val )
  *        {
  *          doSomething();
  *        });
  */
class LIBMCC_EXPORT Stgs
{
  public:
    explicit Stgs();

    StgsGroup & operator [] ( const QString & group_name );

  protected:
    QSettings & settings();
    const QSettings & settings() const;

    QString m_group_name,
            m_param_name;

    QString fullName() const;

    QMap< QString, QList< groupFunc > > m_group_map;

    struct Watcher
    {
      explicit Watcher( const QVariant & value, QList< valueFunc > func_list )
        : value( value )
        , func_list( func_list )
      {}

      QVariant value;
      QList< valueFunc > func_list;
    };

    QMap< QString, Watcher > m_value_map;

    QSet< QString > m_pending_set;
    QTimer m_pending_timer;


  private:
    QScopedPointer< QSettings > m_settings;
};

class StgsGroup : public Stgs
{
  public:
    StgsValue & operator () ( const QString & name );

    void onChanged( groupFunc func );
};

class StgsValue : public StgsGroup
{
  public:
    QVariant operator = ( const QVariant & val );

    operator int() const;
    operator QString() const;
    operator bool() const;
    operator double() const;

    QVariant value() const;

    void onChanged( valueFunc func );
};

