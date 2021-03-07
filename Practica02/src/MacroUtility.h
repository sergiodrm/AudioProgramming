#pragma once

#include <assert.h>

/**
*
*     Logger
*
*/
void _dbgprint(const char* _sMode, const char* _sFilename, int _iLine, const char* _sLevel, const char* _sFormat, ...);


#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#ifdef _DEBUG

#define print_log(_sFormat, ...)      _dbgprint(ANSI_COLOR_RESET, __FILE__, __LINE__, "Log", _sFormat, __VA_ARGS__)
#define print_warning(_sFormat, ...)  _dbgprint(ANSI_COLOR_YELLOW, __FILE__, __LINE__, "Warning", _sFormat, __VA_ARGS__)
#define print_error(_sFormat, ...)    _dbgprint(ANSI_COLOR_RED, __FILE__, __LINE__, "Error", _sFormat, __VA_ARGS__)
#else     
#define PRINT_LOG(_sFormat, ...)      
#define print_warning(_sFormat, ...)  
#define print_error(_sFormat, ...)
#endif


/**
 * Inheritance help
 */
#define DECLARE_BASE_CLASS(_CLASS) \
  protected: typedef _CLASS Super; private:

/**
 * OpenAL utility
 */
#define AL_INVALID_BUFFER _CRT_SIZE_MAX
#define AL_CHUNK_SIZE_FLAG 16
#define al_call(_CALL)                                                        \
  {                                                                           \
    alGetError();                                                             \
    (_CALL);                                                                  \
    ALenum alError = alGetError();                                            \
    if (alError != AL_NO_ERROR)                                               \
    {                                                                         \
      print_error("Error at OpenAL function %s (code: %d)", #_CALL, alError); \
      __debugbreak();                                                         \
    }                                                                         \
  }                                                                           \


/**
*
*     Check vars
*
*/
#ifdef _DEBUG

#define ensure_msg(_bTrueCondition, _sMsg)  \
  if (!(_bTrueCondition))                     \
  {                                           \
    print_error(_sMsg);                       \
    __debugbreak();                           \
  }                                           
#define ensure(_bTrueCondition)             \
  if (!(_bTrueCondition)) __debugbreak();

#else

#define ensure_msg(_bTrueCondition, _sMsg)
#define ensure(_bTrueCondition)

#endif