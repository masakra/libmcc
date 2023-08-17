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
#include "mcc.h"

#include <QObject>
#include <QString>
#include <QPen>

QString
mcc::secsToString( int secs )
{
  constexpr int secs_in_min = 60,                // Секунд в минуте
                secs_in_hour = secs_in_min * 60, // Секунд в часе: 60 * 60
                secs_in_day = secs_in_hour * 24; // Секунд в дне: 60 * 60 * 24
  const int days = secs / secs_in_day;
  if ( days )
    secs %= secs_in_day;

  const int hours = secs / secs_in_hour;
  if ( hours )
    secs %= secs_in_hour;

  const int mins = secs / secs_in_min;
  if ( mins )
    secs %= secs_in_min;

  auto toStr = []( int val, const QString & suf, bool force = false ) -> QString
  {
    return val || force ? QString("%1 %2 ").arg( val ).arg( suf ) : QString();
  };

  return QObject::tr("%1%2%3%4 s").arg( toStr( days, QObject::tr("d") ),
                                  toStr( hours, QObject::tr("h") ),
                                  toStr( mins, QObject::tr("m") ) )
                              .arg( secs );
}

QString
mcc::msecsToString( int msecs )
{
  constexpr int msecs_in_sec = 1000,              // Миллисекунд в секунде
                msecs_in_min = msecs_in_sec * 60, // Миллисекунд в минуте
                msecs_in_hour = msecs_in_min * 60, // Миллисекунд в часе
                msecs_in_day = msecs_in_hour * 24; // Миллисекунд в дне
  const int days = msecs / msecs_in_day;
  if ( days )
    msecs %= msecs_in_day;

  const int hours = msecs / msecs_in_hour;
  if ( hours )
    msecs %= msecs_in_hour;

  const int mins = msecs / msecs_in_min;
  if ( mins )
    msecs %= msecs_in_min;

  const int secs = msecs / msecs_in_sec;
  if ( secs )
    msecs %= msecs_in_sec;

  auto toStr = []( int val, const QString & suf ) -> QString
  {
    return val ? QString("%1 %2 ").arg( val ).arg( suf ) : QString();
  };

  return QObject::tr("%1%2%3%4.%5 s").arg( toStr( days, QObject::tr("d") ),
                                       toStr( hours, QObject::tr("h") ),
                                       toStr( mins, QObject::tr("m") ) )
                                 .arg( secs )
                                 .arg( msecs, 3, 10, QLatin1Char('0') );
}

QPen LIBMCC_EXPORT
mcc::dashDotPen()
{
  QPen pen( QColor("#60404040"), .0 );
  pen.setDashPattern({ 60., 4., 2., 4. });
  pen.setCapStyle( Qt::FlatCap );

  return pen;
}

