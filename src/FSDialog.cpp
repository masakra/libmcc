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

#include "FSDialog.h"

#include <QtWidgets>

#include "Settings.h"

#define FS_GROUP "FSDialog"
#define DEF_PATH qApp->applicationDirPath()

/** \brief Строка «Все файлы» в диалогах
 */
QString s_allFiles = QObject::tr(";;All files (* *.*)");

QString
FSDialog::openFileName( QWidget * parent, const QString & caption,
		const QString & suffix, const QString & filter,
		QFileDialog::Options options )
{
	const QString param_name = "OpenFileName_" + suffix,
				  file_name = QFileDialog::getOpenFileName( parent, caption,
						  Settings::value( param_name, FS_GROUP, DEF_PATH ).toString(),
						  filter + s_allFiles, nullptr, options );

	if ( ! file_name.isEmpty() )
		Settings::setValue( param_name, QFileInfo( file_name ).path(), FS_GROUP );

	return file_name;
}

QString
FSDialog::saveFileName( QWidget * parent, const QString & caption, const QString & suffix,
		const QString & filter, const QString & fileName, QFileDialog::Options options )
{
	const QString param_name = "SaveFileName_" + suffix,
				  file_name = QFileDialog::getSaveFileName( parent, caption,
						  Settings::value( param_name, FS_GROUP, DEF_PATH ).toString() +
						  ( ! fileName.isEmpty() ? ( QDir::separator() + fileName ) : QString() ),
						  filter + s_allFiles, nullptr, options );

	if ( ! file_name.isEmpty() )
		Settings::setValue( param_name, QFileInfo( file_name ).path(), FS_GROUP );

	return file_name;
}

QString
FSDialog::directoryName( QWidget * parent, const QString & caption,
		const QString & suffix, QFileDialog::Options options )
{
	const QString param_name = "DirectoryName_" + suffix,
				  dir_name = QFileDialog::getExistingDirectory( parent, caption,
						  Settings::value( param_name, FS_GROUP, DEF_PATH ).toString(),
						  options );

	if ( ! dir_name.isEmpty() )
		Settings::setValue( param_name, dir_name, FS_GROUP );

	return dir_name;
}

