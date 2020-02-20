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

#include "Info.h"

#include <QtWidgets>

QTextEdit * Info::m_widget = nullptr;		// static

QMutex Info::m_mutex;	// static

QString Info::g_date_format = "dd.MM.yyyy",
		Info::g_time_format = "hh:mm:ss",
		Info::g_date_time_suffix = ": ";

QTextEdit *
Info::widget()		// static
{
	if ( ! m_widget ) {
		m_widget = new QTextEdit();
		m_widget->setReadOnly( true );
	}

	return m_widget;
}

void
Info::message( const QString & text, Options options )		// static
{
	m_mutex.lock();

	QString l_text = text;

    if ( ! ( options & IgnoreLtGt ) )
		l_text.replace("<", "&lt;").replace(">", "&gt;");

	if ( options & Date && options & Time )
		l_text.prepend( QString("%1 %2%3")
				.arg( QDate::currentDate().toString( g_date_format ) )
				.arg( QTime::currentTime().toString( g_time_format ) )
				.arg( g_date_time_suffix ) );
	else if ( options & Date )
		l_text.prepend( QDate::currentDate().toString( g_date_format + g_date_time_suffix ) );
	else if ( options & Time )
		l_text.prepend( QTime::currentTime().toString( g_time_format + g_date_time_suffix ) );

	if ( options & Warning )
		l_text.prepend( QObject::tr("WARNING: ") );

	if ( options & Error )
		l_text.prepend( QObject::tr("ERROR: ") );

	if ( m_widget ) {

		if ( options & Warning )
			l_text.prepend("<font color='mediumorchid'>").append("</font>");

		if ( options & Error )
			l_text.prepend("<font color='red'>").append("</font>");

		if ( options & Indent )
			m_widget->append("");

		if ( options & ContinueLastLine ) {
			QTextCursor cursor( m_widget->document() );
			cursor.movePosition( QTextCursor::End );
			cursor.insertText( l_text );
		} else
			m_widget->append( l_text );

    } else if ( ! ( options & Console ) )
		printf("Info::message: %s\n", qPrintable( l_text ) );

	if ( options & Console )
		printf("%s\n", qPrintable( l_text ) );

	m_mutex.unlock();
}

void
Info::clear()	// static
{
	m_mutex.lock();

	if ( m_widget )
		m_widget->clear();
	else
		printf("Info::clear: object missing");

	m_mutex.unlock();
}

void
Info::setDateFormat( const QString & format )	// static
{
	g_date_format = format;
}

void
Info::setTimeFormat( const QString & format )	// static
{
	g_time_format = format;
}

void
Info::setDateTimeSuffix( const QString & suffix )	// static
{
	g_date_time_suffix = suffix;
}

