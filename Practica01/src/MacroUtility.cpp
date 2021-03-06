#include "MacroUtility.h"
#include <stdio.h>
#include <string>
#include <stdarg.h>

void _dbgprint(const char* _sMode, const char* _sFilename, int _iLine, const char* _sLevel, const char* _sFormat, ...)
{
  if (strcmp(_sFormat, "") == 0)
    return;

  unsigned int uSize = strlen(_sFilename) + 1;
  unsigned int uIndex = uSize - 1;
  while (uIndex >= 1 && _sFilename[uIndex - 1] != '\\')
    uIndex--;
  printf("%s[%s:%d] %s: ", _sMode, _sFilename + uIndex, _iLine, _sLevel);

  va_list arglist;
  va_start(arglist, _sFormat);
  vprintf(_sFormat, arglist);
  va_end(arglist);
  printf(ANSI_COLOR_RESET "\n");
}
