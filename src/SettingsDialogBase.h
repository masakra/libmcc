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

#include "Dialog.h"

#include <functional>

/** Чтобы не включать заголовочный файл Settings.h в
 * заголовочные файлы потомков SettingsDialogBase,
 * в которых, как правило, задефайнены имена параметров.
 */
#include "Settings.h"
#include "SettingsKey.h"

#include "libmcc_global.h"

class QListWidget;
class QStackedWidget;

/** Базовый диалог настроек.
 *
 * Удаляется при закрытии.
 *
 * Что бы не блокировал основной цикл обработки сообщений:
 * \code
 * DialogSettings * d = new DialogSettings;
 * d->show();
 *	     //	   или
 * ( new DialogSettings )->show();
 * \endcode
 */
class LIBMCC_EXPORT SettingsDialogBase : public Dialog
{
	Q_OBJECT

	public:
		explicit SettingsDialogBase( QWidget * parent );

		explicit SettingsDialogBase( const QList< SettingsKey > & watch, QWidget * parent );

		explicit SettingsDialogBase( const QList< SettingsKey > & watch,
				const QObject * receiver, const char * slot, QWidget * parent );

		explicit SettingsDialogBase( const QList< SettingsKey > & watch,
				std::function< void( const SettingsKey &, const QVariant & ) > func, QWidget * parent );

		~SettingsDialogBase();

	public Q_SLOTS:
		/**	Отображает диалог и делает активную вкладку с индексом \a tab
		 *
		 * Если \a tab == -1 то активной становится вкладка которая была активна
		 * при закрытии диалога.
		 */
		void show( int tab = -1 );

	Q_SIGNALS:
		/** Изменилось наблюдаемое значение
		 */
		void watchValueChanged( const SettingsKey & key, const QVariant & val ) const;

	protected:
    void addPage( const QIcon & icon, const QString & caption, QWidget * page );

		void showEvent( QShowEvent * event ) override final;

	private:
		void createWidgets();

		QListWidget * m_pager;

		QStackedWidget * m_stack;

		QMap< SettingsKey, QVariant > m_watch;
};

