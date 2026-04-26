#include "SqliteAddon.hpp"
#include <sqlite3.h>
#include <iostream>

SqliteTool::SqliteTool(void)
{


	const char* sql = 
	"CREATE TABLE IF NOT EXISTS tracks ("
	"id INTEGER PRIMARY KEY,"
	"title TEXT,"
	"artist TEXT,"
	"album TEXT,"
	"path TEXT);";

	char* errMsg = 0;
	sqlite3_exec(db, sql, 0, 0, &errMsg);


	const char* insert = 
	"INSERT INTO tracks (title, artist, album, path) "
	"VALUES ('One More Time', 'Daft Punk', 'Discovery', '/music/file.mp3');";

	sqlite3_exec(db, insert, 0, 0, 0);


    //sqlite3_value_text(sqlite3_value *)


	// int callback(void* data, int argc, char** argv, char** colNames)
	// {
	// 	for (int i = 0; i < argc; i++)
	// 		printf("%s = %s\n", colNames[i], argv[i]);

	// 	printf("\n");
	// 	return 0;
	// }

	// const char* query = "SELECT * FROM tracks;";
	// sqlite3_exec(db, query, callback, 0, 0);
}
SqliteTool::~SqliteTool(void)
{
    if (db)
    {
        sqlite3_close(db);
    }
}


void SqliteTool::SetDB(const std::string& _path)
{
    if (sqlite3_open(_path.c_str(), &db))
	{
		std::cerr << "Erreur ouverture DB\n";
	}
}



void SqliteTool::GetColumn(const std::string& _command, std::vector<std::string>& _return)
{
    sqlite3_stmt* stmt;
    
    if (!db)
    {
        std::cerr << "[CRITICAL ERROR] : DB isnt loaded";
        return;
    }

    if (sqlite3_prepare_v2(db, _command.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Erreur prepare\n";
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char* text = sqlite3_column_text(stmt, 0);

        if (text)
        {
            _return.emplace_back((const char*)text);
        }
    }

    sqlite3_finalize(stmt);
}

void SqliteTool::Insert(const char* _command)
{
	if (sqlite3_exec(db, _command, 0, 0, 0) != SQLITE_OK)
	{
		std::cerr << "Error on insert data: " << sqlite3_errmsg(db) << std::endl;
	}	
}

unsigned long SqliteTool::GetCount(const std::string& _command)
{
    sqlite3_stmt* stmt = nullptr;
    long long result = 0;

    if (!db)
    {
        std::cerr << "[CRITICAL ERROR] : DB isnt loaded";
        return 0;
    }

    if (sqlite3_prepare_v2(db, _command.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error prepare: " << sqlite3_errmsg(db) << '\n';
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result = sqlite3_column_int64(stmt, 0);
    }
    else
    {
        // pas de ligne ou erreur
        if (sqlite3_errcode(db) != SQLITE_DONE)
        {
            std::cerr << "Error on step : " << sqlite3_errmsg(db) << '\n';
        }
    }

    sqlite3_finalize(stmt);
    return result;
}