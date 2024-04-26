#ifndef ILOG_H
#define ILOG_H

#include <QString>
#include <QTextStream>

class ILog
{
public:
    virtual void Write(const QString& str) = 0;
    virtual ~ILog() = default;
};

#endif // ILOG_H
