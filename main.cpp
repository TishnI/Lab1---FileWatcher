#include <QCoreApplication>

#include <thread>
#include "filewatcher.h"
#include "consolelog.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConsoleLog* logger = new ConsoleLog();

    QTextStream input(stdin);
    QTextStream out(stdout);
    int numberFiles = 0;

    out<<"Enter the number of files to track"<<Qt::endl;
    while(true)
    {
        numberFiles = input.readLine().toInt();
        if(numberFiles <= 0)
        {
            out<<"Invalid input"<<Qt::endl;
            continue;
        }
        break;
    }

    for(int i = 0; i < numberFiles; i++)
    {
        out<<"Enter file path number " + QString::number(i+1) <<Qt::endl;
        QString path = input.readLine();
        if(!FileWatcher::Instance(logger).RegisterFile(path))
        {
            i--;
            continue;
        }
    }

    FileWatcher::Instance(logger).InitialFileStatus();
    while(true)
    {
        FileWatcher::Instance(logger).UpdateFileInfo();
        std::this_thread::sleep_for( std::chrono::milliseconds(100));
    }

    delete logger;

    return a.exec();
}
