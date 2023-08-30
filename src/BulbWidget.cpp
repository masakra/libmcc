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
#include "BulbWidget.h"

#include <QPainter>

BulbWidget::BulbWidget( QWidget * parent/*= nullptr*/)
  : QWidget( parent )
  , m_color( Qt::gray )
{
  setMinimumSize( 24 );
}

void
BulbWidget::setColor( const QColor & color )
{
  m_color = color;
  update();
}

void
BulbWidget::setMinimumSize( int size )
{
  QWidget::setMinimumSize( size, size );
}

void
BulbWidget::setFixedSize( int size )
{
  QWidget::setFixedSize( size, size );
}

void
BulbWidget::setMaximumSize( int size )
{
  QWidget::setMaximumSize( size, size );
}

void
BulbWidget::setSizesRange( int min, int max )
{
  setMinimumSize( min );
  setMaximumSize( max );
}

void
BulbWidget::paintEvent( QPaintEvent * event ) // override final
{
  QWidget::paintEvent( event );

  QPainter painter( this );
  drawOnPainter( &painter, QRect( 0, 0, width(), height() ), m_color,
     palette().dark().color() );
}

void
BulbWidget::drawOnPainter( QPainter * painter, const QRect & rect,
    const QColor & color, const QColor & frame_color/*= Qt::black*/)
{
  painter->save();
  painter->setRenderHint( QPainter::Antialiasing );

  const int diam = qMin( rect.width(), rect.height() ) - 2,
            x = ( rect.width() - diam ) / 2 + rect.x(),
            y = ( rect.height() - diam ) / 2 + rect.y();

  painter->setPen( QPen( frame_color, 1.5 ) );
  painter->setBrush( Qt::NoBrush );
  painter->drawEllipse( x, y, diam, diam );

  QRadialGradient grad( x + diam / 2.5, y + diam / 2.5, diam / 1.3 );
  grad.setColorAt( 0, Qt::white );
  grad.setColorAt( 1, color );

  painter->setPen( Qt::NoPen );
  painter->setBrush( grad );

  painter->drawEllipse( x + 2, y + 2, diam - 4, diam - 4 );

  painter->restore();
}

