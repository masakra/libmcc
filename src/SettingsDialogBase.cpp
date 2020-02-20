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

#include "SettingsDialogBase.h"

#include <QtWidgets>

#include "ButtonsLine.h"

#define GROUP QStringLiteral("DialogSettings")
#define STACK_INDEX QStringLiteral("StackIndex")

SettingsDialogBase::SettingsDialogBase( QWidget * parent )
	: Dialog( parent )
{
	setWindowTitle( tr("Settings") );
	setAttribute( Qt::WA_DeleteOnClose );
	setWindowFlags( Qt::WindowStaysOnTopHint );

	createWidgets();
}

SettingsDialogBase::SettingsDialogBase( const QList< SettingsKey > & watch, QWidget * parent )
	: SettingsDialogBase( parent )
{
	foreach( const SettingsKey & key, watch )
		m_watch.insert( key, Settings::value( key.name(), key.group() ) );
}

SettingsDialogBase::SettingsDialogBase( const QList< SettingsKey > & watch,
		const QObject * receiver, const char * slot, QWidget * parent )
	: SettingsDialogBase( watch, parent )
{
	connect( this, SIGNAL( watchValueChanged( const QString & ) ),
			receiver, slot );
}

SettingsDialogBase::SettingsDialogBase( const QList< SettingsKey > & watch,
		std::function< void( const SettingsKey &, const QVariant & ) > func, QWidget * parent )
	: SettingsDialogBase( watch, parent )
{
	//connect( this, QOverload< const QString & >::of( &SettingsDialogBase::watchValueChanged ), func );
	connect( this, static_cast< void( SettingsDialogBase::* )( const SettingsKey &, const QVariant & ) const >
      ( &SettingsDialogBase::watchValueChanged ), func );
}

SettingsDialogBase::~SettingsDialogBase()
{
	auto i = m_watch.constBegin();

	while ( i != m_watch.constEnd() ) {

    const QVariant val = Settings::value( i.key().name(), i.key().group() );

		if ( i.value() != val )
			emit watchValueChanged( i.key(), val );
		++i;
	}

	Settings::setValue( STACK_INDEX, GROUP, m_pager->currentRow() );
}

void
SettingsDialogBase::createWidgets()
{
	m_pager = new QListWidget( this );
	m_pager->setViewMode( QListView::IconMode );
	m_pager->setIconSize( QSize( 64, 64 ) );
	m_pager->setMovement( QListView::Static );
	m_pager->setMaximumWidth( 128 );
	m_pager->setSpacing( 6 );
  m_pager->setItemAlignment( Qt::AlignCenter );

	m_stack = new QStackedWidget( this );

	connect( m_pager, SIGNAL( currentRowChanged( int ) ), m_stack, SLOT( setCurrentIndex( int ) ) );

	QHBoxLayout * layoutPager = new QHBoxLayout();

	layoutPager->addWidget( m_pager );
	layoutPager->addWidget( m_stack );

	QVBoxLayout * layout = new QVBoxLayout( this );

	layout->addLayout( layoutPager );
	layout->addLayout( new ButtonsLine( tr("Settings") ) );
	layout->addWidget( buttonBox() );
}

void
SettingsDialogBase::addPage( const QIcon & icon, const QString & caption, QWidget * widget )
{
	QListWidgetItem * item = new QListWidgetItem( m_pager );
	item->setIcon( icon );
	item->setText( caption );
	item->setTextAlignment( Qt::AlignHCenter );
	item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

  QGridLayout * grid = qobject_cast< QGridLayout * >( widget->layout() );
  if ( grid )
    grid->setRowStretch( grid->rowCount(), 100 );

	m_stack->addWidget( widget );
}

void
SettingsDialogBase::show( int tab )
{
	m_pager->setCurrentRow( tab != -1 ? tab : Settings::value( STACK_INDEX, GROUP ).toInt() );

	QDialog::show();
}

void
SettingsDialogBase::showEvent( QShowEvent * event )
{
	// move to desktop center
  if ( qApp->screens().isEmpty() )
    return;

	const QRect desk = qApp->screens().first()->geometry();

	move( ( desk.width() - width() ) / 2, ( desk.height() - height() ) / 2 );

	QDialog::showEvent( event );
}

