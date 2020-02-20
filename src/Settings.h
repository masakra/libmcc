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

#include <QtCore>

#include "libmcc_global.h"

#define QSETTINGS_s QSettings s( Settings::g_format, Settings::g_scope, qApp->organizationName(), qApp->applicationName() );

/** Глобальный хэш значений параметров настроек.
 */
class LIBMCC_EXPORT Settings
{
	public:
		static QSettings::Format g_format;

		static QSettings::Scope g_scope;

	private:
		// символьный хэш
		static QHash< QString,		// group name
					  QHash< QString,		// param name (in group)
					    QVariant > > g_values;

		inline static QString fullParamName( const QString & name , const QString & group );

		/** \brief Проверяет наличие значения параметра в g_values
		 */
		static bool haveValue( const QString & name, const QString & group = QString() );

	public:
		static void setFormat( QSettings::Format format );

		static QSettings::Format format();

		static void setScope( QSettings::Scope scope );

		static QSettings::Scope scope();

		// символьные ключи
		static const QVariant & value( const QString & name, const QString & group = QString(),
				const QVariant & def_value = QVariant() );

		static void setValue( const QString & paramName, const QVariant & newValue );

    static void setValue( const QString & name, const QString & group, const QVariant & value );

		// целочисленные ключи, в теории, должно искать быстрее
		static const QVariant & value( uint paramName, uint group = 0,
				const QVariant & def_value = QVariant() );

		static void setValue( uint paramName, const QVariant & newValue, uint group = 0 );
};

