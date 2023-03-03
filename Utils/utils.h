#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QSqlDatabase>
#include <QJsonDocument>
#include <QJsonParseError>

class Utils
{
public:
    static QString exec(const QString &cmd, QByteArray data = QByteArray());
    static QString sudo(const QString &cmd, QByteArray data = QByteArray());
    static QString writeFile(const QString &filePath, const QString &text);
    static QString writeSystemFile(const QString &filePath, const QString &text);
    static QString readFile(const QString &filePath);
    static QString awk(const QString &F,const QString &col);
    static bool isFileExist(const QString &filePath);
    static void initDB(QSqlDatabase &db);                      // 数据库初始化函数
    static QString formatSize(qint64 imgSize);            // 通过字节大小转换成其他单位
    static QJsonDocument loadJsonData(const QByteArray data);   // 读取QByteArray数据
};

#endif // UTILS_H
