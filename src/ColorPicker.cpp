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

#include "ColorPicker.h"

#include <QtWidgets>

#include "ColorDisplay.h"

/*
ColorPicker::ColorPicker( QWidget * parent )
	: QWidget( parent ), m_linkedColor( nullptr )
{
}
*/

ColorPicker::ColorPicker( QWidget * parent, int index )
	: QWidget( parent ), m_index( index )
{
	createWidgets();
}

void
ColorPicker::createWidgets()
{
	m_colorDisplay = new ColorDisplay( this );

	connect( m_colorDisplay, &ColorDisplay::colorChanged, this, &ColorPicker::setColor );

	m_sliderAlpha = new QSlider( Qt::Horizontal, this );
	m_sliderAlpha->setRange( 0, 255 );

	connect( m_sliderAlpha, &QSlider::valueChanged, m_colorDisplay, &ColorDisplay::setAlpha );

	QHBoxLayout * layout = new QHBoxLayout( this );
	layout->setMargin( 1 );

	layout->addWidget( m_colorDisplay );
	layout->addWidget( m_sliderAlpha );
}

const QColor &
ColorPicker::color() const
{
	return m_colorDisplay->color();
}

void
ColorPicker::setColor( const QColor & c )		// slot
{
	if ( ! m_oldColor.isValid() )
		m_oldColor = c;

	m_colorDisplay->setColor( c );
	m_sliderAlpha->setValue( c.alpha() );

	emit colorChanged( c, m_index );
}

/*
void
ColorPicker::setLinkedColor( QColor * linkedColor )
{
	// сохранить цвет для отката
	m_oldLinkedColor = *linkedColor;

	m_linkedColor = linkedColor;

	setColor( *linkedColor );
}
*/

void
ColorPicker::rollback()		// slot Откатить цвет в linkedColor
{
	setColor( m_oldColor );
}

