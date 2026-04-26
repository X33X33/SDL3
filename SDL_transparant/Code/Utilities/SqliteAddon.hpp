#ifndef SQL3_ADDON_HPP
#define SQL3_ADDON_HPP

#include <sqlite3.h>
#include <string>
#include <vector>

class SqliteTool
{
public:

    SqliteTool(void);
    ~SqliteTool(void);

    void SetDB(const std::string& _path);

    //Get colum from db
    void GetColumn(const std::string& _command, std::vector<std::string>& _return);
    
    void Insert(const char* _command);

    unsigned long GetCount(const std::string& _command);


    sqlite3* db;
};




#endif //!SQL3_ADDON_HPP