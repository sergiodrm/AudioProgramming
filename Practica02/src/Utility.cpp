
#include "Utility.h"

namespace Utility
{
  std::string ExtractPath(const std::string& _sFilename)
  {
    std::string filenameCopy = _sFilename;
    while (filenameCopy.find("\\") != std::string::npos) 
    {
      filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
    }
    filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));
    if (filenameCopy.size() > 0) filenameCopy += "/";
    return filenameCopy;
  }
}