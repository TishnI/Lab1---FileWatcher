#include "consolelog.h"

ConsoleLog::ConsoleLog() {}

void ConsoleLog::Write(const QString& str)
{
    QTextStream out(stdout);
    out<<str<<Qt::endl;
}
