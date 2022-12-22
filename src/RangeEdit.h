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

#include <QFrame>

#include <QHBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QStyle>

#include "Range.h"
#include "libmcc_export.h"

#define RANGE_DELIM QStringLiteral(" ... ")

class QStyleOptionViewItem;

/** Для отрисовки диапазона в делегатах
  */
extern LIBMCC_EXPORT void drawRange( QPainter * painter,
    const QStyleOptionViewItem & option, const QString & min,
    const QString & max );

template< typename T, class E >
class RangeEdit : public QFrame
{
  public:
    explicit RangeEdit( QWidget * parent = nullptr )
      : QFrame( parent )
    {
      setFrameShape( QFrame::StyledPanel );
      setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
      createWidgets();
    }

    Range< T > value() const
    {
      return Range< T >( m_min_spin->value(), m_max_spin->value() );
    };

    void setValue( T min, T max )
    {
      m_min_spin->setValue( min );
      m_max_spin->setValue( max );
    };

    void setValue( const Range< T > & range )
    {
      setValue( range.min(), range.max() );
    };

    void setBoundingRange( T min, T max )
    {
      m_min_spin->setRange( min, max );
      m_max_spin->setRange( min, max );
    };

    void setSingleStep( T val )
    {
      m_min_spin->setSingleStep( val );
      m_max_spin->setSingleStep( val );
    };

  protected:
    E * m_min_spin,
      * m_max_spin;

  private:
    void createWidgets()
    {
      const auto fw = style()->pixelMetric( QStyle::PM_SpinBoxFrameWidth );

      QHBoxLayout * layout = new QHBoxLayout( this );
      layout->setContentsMargins( fw, fw, fw, fw );
      layout->setSpacing( 0 );

      layout->addWidget( m_min_spin = new E );
      m_min_spin->setFrame( false );
      m_min_spin->setAlignment( Qt::AlignRight | Qt::AlignVCenter );

      layout->addWidget( new QLabel( RANGE_DELIM ) );

      layout->addWidget( m_max_spin = new E );
      m_max_spin->setFrame( false );

      layout->setStretch( 0, 10 );
      layout->setStretch( 2, 10 );
    }

    void paintEvent( QPaintEvent * event ) override final
    {
      QPainter painter( this );
      painter.fillRect( event->rect(), palette().base().color() );

      QFrame::paintEvent( event );
    }
};

