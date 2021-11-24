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

#include "ColorDisplay.h"

#include <QtWidgets>

ColorDisplay::ColorDisplay( QWidget * parent )
	: QWidget( parent )
{
	setMinimumSize( 17, 10 );
	setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
}

QSize
ColorDisplay::sizeHint() const	// override
{
	return QSize( 68, 42 );
}

const QColor &
ColorDisplay::color() const
{
	return m_color;
}

void
ColorDisplay::setColor( const QColor & c )
{
	if ( m_color == c )
		return;

	m_color = c;
	setToolTip();
	update();

	emit colorChanged( m_color );
}

void
ColorDisplay::setAlpha( int alpha )
{
	if ( m_color.alpha() == alpha )
		return;

	m_color.setAlpha( alpha );
	setToolTip();
	update();

	emit colorChanged( m_color );
}

void
ColorDisplay::paintEvent( QPaintEvent * event )
{
	QPainter painter( this );

	const qreal half_width = width() / 2.;
	const QRectF opacityRect = QRectF( .0, .0, half_width, height() ),
				 transparentRect = QRectF( half_width, 0, half_width, height() );

	if ( opacityRect.intersects( event->rect() ) ) {
		QColor opacityColor = m_color;
		opacityColor.setAlpha( 255 );
		painter.fillRect( opacityRect, opacityColor );
	}

	if ( transparentRect.intersects( event->rect() ) ) {
		painter.fillRect( transparentRect, QBrush( QImage(":/trans_bg.png") ) );
		painter.fillRect( transparentRect, m_color );
	}
}

void
ColorDisplay::mousePressEvent( QMouseEvent * event )
{
	if ( event->button() == Qt::LeftButton ) {

		QColor color = QColorDialog::getColor( m_color, parentWidget() );

		if ( color.isValid() ) {
			color.setAlpha( m_color.alpha() );
			setColor( color );
		}

		event->accept();
	}
  else if ( event->button() == Qt::RightButton ) {
#if QT_VERSION >= 0x060000
		if ( contextMenu( event->globalPosition().toPoint() ) )
#else
		if ( contextMenu( event->globalPos() ) )
#endif
			event->accept();
	}
  else
		QWidget::mousePressEvent( event );
}

bool
ColorDisplay::contextMenu( const QPoint & pos )
{
	QMenu menu;

	menu.addAction( QIcon::fromTheme("edit-copy"), tr("Copy color"),
      this, SLOT( copyColorToClipboard() ) );

	const QString colorName = qApp->clipboard()->text();

	if ( QColor::isValidColor( colorName ) ) {
		const QColor color( colorName );
		QPixmap pixmap( 22, 22 );
		pixmap.fill( color );

		menu.addAction( QIcon( pixmap ), tr("Paste color <%1>").arg( colorName ),
        this, SLOT( pasteColorFromClipboard() ) );
	}

	return menu.exec( pos );
}

void
ColorDisplay::copyColorToClipboard() const	// private slot
{
	qApp->clipboard()->setText( m_color.name( QColor::HexArgb ) );
}

void
ColorDisplay::pasteColorFromClipboard()	// private slot
{
	const QString colorName = qApp->clipboard()->text();

	if ( QColor::isValidColor( colorName ) ) {
		m_color = QColor( colorName );
		update();
	}
}

void
ColorDisplay::setToolTip()
{
	QWidget::setToolTip( m_color.name( QColor::HexArgb ) );
}

