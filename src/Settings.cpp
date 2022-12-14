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
#include "Settings.h"

QSettings::Format Settings::g_format = QSettings::NativeFormat;

QSettings::Scope Settings::g_scope = QSettings::UserScope;

QHash< QString,		// group name
	QHash< QString,		// param name (in group)
		QVariant > > Settings::g_values;

QString
Settings::fullParamName( const QString & name, const QString & group )
  // static inline
{
	return group.isEmpty() ? name : ( group + "/" + name );
}

void
Settings::setFormat( QSettings::Format format )	// static
{
	g_format = format;
}

QSettings::Format
Settings::format() // static
{
	return g_format;
}

void
Settings::setScope( QSettings::Scope scope ) // static
{
	g_scope = scope;
}

QSettings::Scope
Settings::scope()	// static
{
	return g_scope;
}

bool
Settings::haveValue( const QString & name, const QString & group/*= QString()*/)
  // private static
{
	return g_values.contains( group ) && g_values.value( group ).contains( name );
}

const QVariant &
Settings::value( const QString & name, const QString & group, const QVariant &
    def_value )	// static
{
	if ( ! haveValue( name, group ) ||
        ! g_values.value( group ).value( name ).isValid() ) {
		QSETTINGS_s
    const QVariant saved_value = s.value( fullParamName( name, group ) );

    if ( saved_value.isValid() )
      g_values[ group ][ name ] = saved_value;
    else if ( def_value.isValid() ) {
      g_values[ group ][ name ] = def_value;
      s.setValue( fullParamName( name, group ), def_value );
    }
    else
      g_values[ group ][ name ] = QVariant();
  }

	return g_values[ group ][ name ];
}

void
Settings::setValue( const QString & name, const QVariant & value ) // static
{
  static const QString group;

	if ( haveValue( name ) &&
			g_values[ group ][ name ] == value )
		return;

	QSETTINGS_s

	s.setValue( fullParamName( name, group ), value );
	g_values[ group ][ name ] = value;
}

void
Settings::setValue( const QString & name, const QString & group,
    const QVariant & value ) // static
{
  if ( haveValue( name, group ) &&
        g_values[ group ][ name ] == value )
    return;

  QSETTINGS_s

  s.setValue( fullParamName( name, group ), value );
  g_values[ group ][ name ] = value;
}

