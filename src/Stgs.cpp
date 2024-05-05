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
#include "Stgs.h"

#include <QSettings>

/*
\\          Stgs
*/

Stgs::Stgs()
{
  m_pending_timer.setSingleShot( true );
  m_pending_timer.setInterval( 500 );
  m_pending_timer.callOnTimeout([ this ]
    {
      for ( auto & group : m_pending_set ) {
        auto iter = m_group_map.find( group );
        if ( iter != m_group_map.end() )
          for ( auto func : iter.value() )
            func();
      }
    });
}


QSettings &
Stgs::settings() // protected
{
  if ( m_settings.isNull() )
    m_settings.reset( new QSettings );

  return *m_settings;
}

const QSettings &
Stgs::settings() const // protected
{
  return const_cast< Stgs * >( this )->settings();
}

QString
Stgs::fullName() const // protected
{
  if ( m_group_name.isEmpty() )
    return m_param_name;

  return QStringLiteral("%1/%2")
                          .arg( m_group_name )
                          .arg( m_param_name );
}

StgsGroup &
Stgs::operator [] ( const QString & group_name )
{
  m_group_name = group_name;
  return *static_cast< StgsGroup * >( this );
}

/*
\\          StgsGroup
*/

StgsValue &
StgsGroup::operator () ( const QString & param_name )
{
  m_param_name = param_name;
  return *static_cast< StgsValue * >( this );
}

void
StgsGroup::onChanged( groupFunc func )
{
  auto iter = m_group_map.find( m_group_name );

  if ( iter != m_group_map.end() )
    iter.value().append( func );
  else
    m_group_map.insert( m_group_name, { func });
}

/*
\\          StgsValue
*/

QVariant
StgsValue::operator = ( const QVariant & val )
{
  if ( m_group_map.contains( m_group_name ) ) {
    m_pending_set << m_group_name;
    m_pending_timer.start();
  }

  const auto full_name = fullName();

  auto iter = m_value_map.find( full_name );
  if ( iter != m_value_map.end() &&
        iter.value().value != val ) {
    for ( auto func : iter.value().func_list )
      func( val, iter.value().value );

    iter.value().value = val;
  }

  settings().setValue( full_name, val );
  return val;
}

QVariant
StgsValue::value() const
{
  return settings().value( fullName() );
}

StgsValue::operator int() const
{
  return value().toInt();
}

StgsValue::operator QString() const
{
  return value().toString();
}

StgsValue::operator bool() const
{
  return value().toBool();
}

StgsValue::operator double() const
{
  return value().toDouble();
}

void
StgsValue::onChanged( valueFunc func )
{
  const auto full_name = fullName();

  auto iter = m_value_map.find( full_name );

  if ( iter != m_value_map.end() )
    iter.value().func_list.append( func );
  else
    m_value_map.insert( full_name, Watcher( value(), { func }) );
}

