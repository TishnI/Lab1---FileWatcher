#ifndef CONSOLELOG_H
#define CONSOLELOG_H

#include "ilog.h"

class ConsoleLog : public ILog
{
public:
    ConsoleLog();
    virtual ~ConsoleLog() = default;
    virtual void Write(const QString& str);
};

#endif // CONSOLELOG_H
