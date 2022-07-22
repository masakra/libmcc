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
#include "GridLayout.h"

#include "Label.h"

GridLayout::GridLayout( QWidget * parent/*= nullptr*/)
  : QGridLayout( parent )
{
}

int
GridLayout::realRow( int row ) const
{
  return row == Last ? lastRow() : row == Next ? nextRow() : row;
}

int
GridLayout::realColumn( int col ) const
{
  return col == Last ? lastColumn() : col == Next ? nextColumn() : col;
}

void
GridLayout::addWidget( const QString & text, QWidget * widget,
    int row/*= Next*/, int col/*= 0*/, int row_span/*= 1*/, int col_span/*= 1*/,
    Qt::Alignment al/*= Qt::AlignRight*/)
{
  const int r = realRow( row ),
            c = realColumn( col );

  QGridLayout::addWidget( new Label( text, widget ), r, c, al );
  QGridLayout::addWidget( widget, r, c + 1, row_span, col_span );
}

void
GridLayout::addWidget( QWidget * widget, int row, int col,
    Qt::Alignment al/*= Qt::Alignment()*/)
{
  const int r = realRow( row ),
            c = realColumn( col );

  QGridLayout::addWidget( widget, r, c, al );
}


void
GridLayout::addWidget( QWidget * widget, int row, int col, int row_span,
    int col_span, Qt::Alignment al/*= Qt::Alignment()*/)
{
  const int r = realRow( row ),
            c = realColumn( col );

  QGridLayout::addWidget( widget, r, c, row_span, col_span, al );
}

int
GridLayout::lastRow() const
{
  return rowCount() - 1;
}

int
GridLayout::nextRow() const
{
  return rowCount();
}

int
GridLayout::lastColumn() const
{
  return columnCount() - 1;
}

int
GridLayout::nextColumn() const
{
  return columnCount();
}

