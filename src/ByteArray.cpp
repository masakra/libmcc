
#include "ByteArray.h"

ByteArray::ByteArray( const QByteArray & ba )
  : QByteArray( ba )
{
}

ByteArray::ByteArray( qsizetype size, char ch/*= '\0'*/)
  : QByteArray( size, ch )
{
}

