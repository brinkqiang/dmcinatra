
#ifndef __DMPOLICY_H_INCLUDE__
#define __DMPOLICY_H_INCLUDE__

#include <locale>
#include <streambuf>
#include "dmstrtk.hpp"
#include "dmstl.h"
#include "dmformat.h"
#include "dmerrordata.h"

#include "dmcsv_parser.hpp"
#include "dmcsv_writer.hpp"

#include "pugixml.hpp"
#include "dmxlsx.h"

#include "google/protobuf/util/json_util.h"

class CLocalGuard
{
public:
    CLocalGuard()
    {
#ifdef WIN32
        m_oLocale = std::locale::global(std::locale(""));
#endif
    }

    ~CLocalGuard()
    {
#ifdef WIN32
        std::locale::global(m_oLocale);
#endif
    }

private:
#ifdef WIN32
    std::locale m_oLocale;
#endif
};

#define LOCAL_GUARD(x)  do{ CLocalGuard oLocalGuard; x;}while(0)

#ifdef WIN32
#define CONFIG_PATH_DELIMITER '\\'
#else
#define CONFIG_PATH_DELIMITER '/'
#endif

#ifndef CONFIG_FILE_NOTEXIST
#define CONFIG_FILE_NOTEXIST 1
#else
#define CONFIG_FILE_NOTEXIST 0
#endif

#ifndef CONFIG_CREATEFILE_NOTEXIST
#define CONFIG_CREATEFILE_NOTEXIST 1
#else
#define CONFIG_CREATEFILE_NOTEXIST 0
#endif

#ifndef CONFIG_CSV_DELIM
#define CONFIG_CSV_DELIM ","
#endif

#ifndef CONFIG_MD_DELIM
#define CONFIG_MD_DELIM "|"
#endif

#ifndef DM_INDENT
#define DM_INDENT "\t"
#endif

#ifndef DM_FLAG
#define DM_FLAG (pugi::format_raw | pugi::format_no_declaration)
#endif

#ifndef DM_ENCODING
#define DM_ENCODING pugi::encoding_auto
#endif

#ifndef DM_SKIP_CSV_FIRST_COW
#define DM_SKIP_CSV_FIRST_COW 1
#endif

#ifndef DM_SKIP_XLSX_FIRST_COW
#define DM_SKIP_XLSX_FIRST_COW 1
#endif

#endif // __DMPOLICY_H_INCLUDE__
