#include <spdlog/spdlog.h>
#include <sqlite3.h>

int main(int argc, char const *argv[])
{
    SPDLOG_INFO("sqlite3: {}", sqlite3_libversion());

    int ret;

    sqlite3 *db;
    ret = sqlite3_open("students.db", &db);
    if (ret != 0)
        return ret;

    SPDLOG_INFO("open database success");

    char** result;
    int nRow, nCol;
    char* err;

    // 创建表
    const char* sql1 = "CREATE TABLE IF NOT EXISTS `students`(`id` INTEGER, `name` STRING);";
    ret = sqlite3_get_table(db, sql1, &result, &nRow, &nCol, &err);
    if (ret != 0) {
        SPDLOG_ERROR("err: {}", err);
        return ret;
    }
    SPDLOG_INFO("create table success");

    //插入数据
    const char* sql2 = "INSERT INTO `students` VALUES (1, 'zhangsan'), (2, 'lisi');";
    ret = sqlite3_get_table(db, sql2, &result, &nRow, &nCol, &err);
    if (ret != 0) {
        SPDLOG_ERROR("err: {}", err);
        return ret;
    }
    SPDLOG_INFO("insert table success");

    // 查询表
    const char* sql3 = "SELECT * FROM `students`;";
    ret = sqlite3_get_table(db, sql3, &result, &nRow, &nCol, &err);
    if (ret != 0) {
        SPDLOG_ERROR("err: {}", err);
        return ret;
    }

    SPDLOG_INFO("|{:10}|{:10}|", result[0], result[1]);
    for (int i = 1; i <= nRow; i++) {
        SPDLOG_INFO("|{:10}|{:10}|", result[i * nCol], result[i * nCol + 1]);
    }

    sqlite3_free_table(result);

    ret = sqlite3_close(db);
    if (ret != 0)
        return ret;

    return 0;
}
