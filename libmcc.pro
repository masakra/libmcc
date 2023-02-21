#┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
#┃                             ________________                                ┃
#┃ _______ ________________    ___  /__(_)__  /______________ ____________  __ ┃
#┃ __  __ `__ \  ___/  ___/    __  /__  /__  __ \_  ___/  __ `/_  ___/_  / / / ┃
#┃ _  / / / / / /__ / /__      _  / _  / _  /_/ /  /   / /_/ /_  /   _  /_/ /  ┃
#┃ /_/ /_/ /_/\___/ \___/      /_/  /_/  /_.___//_/    \__,_/ /_/    _\__, /   ┃
#┃                                                                   /____/    ┃
#┠─────────────────────────────────────────────────────────────────────────────┨
#┃ Copyright © 2016, Sergey N Chursanov (masakra@mail.ru)                      ┃
#┃ All rights reserved.                                                        ┃
#┃                                 BSD license                                 ┃
#┃                                                                             ┃
#┃ Redistribution and use in source and binary forms, with or without          ┃
#┃ modification, are permitted provided that the following conditions are met: ┃
#┃                                                                             ┃
#┃ 1. Redistributions of source code must retain the above copyright notice,   ┃
#┃ this list of conditions and the following disclaimer.                       ┃
#┃                                                                             ┃
#┃ 2. Redistributions in binary form must reproduce the above copyright        ┃
#┃ notice, this list of conditions and the following disclaimer in the         ┃
#┃ documentation and/or other materials provided with the distribution.        ┃
#┃                                                                             ┃
#┃ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" ┃
#┃ AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   ┃
#┃ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  ┃
#┃ ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   ┃
#┃ LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         ┃
#┃ CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        ┃
#┃ SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    ┃
#┃ INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     ┃
#┃ CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     ┃
#┃ ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  ┃
#┃ POSSIBILITY OF SUCH DAMAGE.                                                 ┃
#┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

TEMPLATE = lib
TARGET = mcc
QT += widgets sql
DEFINES += LIBMCC_LIBRARY

HEADERS += \
  src/BulbWidget.h \
  src/ByteArray.h \
  src/ByteVal.h \
  src/ColorDisplay.h \
  src/ColorPicker.h \
  src/ComboBox.h \
  src/Dialog.h \
  src/DoubleSpinBox.h \
  src/FSDialog.h \
  src/Frame.h \
  src/GridLayout.h \
  src/Label.h \
  src/Pair.h \
  src/Range.h \
  src/RangeEdit.h \
  src/Settings.h \
  src/SettingsDialogBase.h \
  src/SettingsKey.h \
  src/SpinBox.h \
  src/Splitter.h \
  src/TextLineY.h \
  src/UnderlineWidget.h \
  src/Version.h \
  src/libmcc_export.h \
  src/mcc.h \
  src/sreal.h

SOURCES += \
  src/BulbWidget.cpp \
  src/ByteArray.cpp \
  src/ColorDisplay.cpp \
  src/ColorPicker.cpp \
  src/ComboBox.cpp \
  src/Dialog.cpp \
  src/DoubleSpinBox.cpp \
  src/FSDialog.cpp \
  src/Frame.cpp \
  src/GridLayout.cpp \
  src/Label.cpp \
  src/RangeEdit.cpp \
  src/Settings.cpp \
  src/SettingsDialogBase.cpp \
  src/SettingsKey.cpp \
  src/SpinBox.cpp \
  src/Splitter.cpp \
  src/TextLineY.cpp \
  src/UnderlineWidget.cpp \
  src/Version.cpp \
  src/mcc.cpp \
  src/sreal.cpp

include( ../auto-qm-lib.pri )

