#ifndef WIN_H
#define WIN_H

#include <thread>
#include "filewatcher.h"
#include "consolelog.h"

class win
{
public:
    win() = default;
    void start();
    void InputFilePath(ILog *);
};

#endif // WIN_H
