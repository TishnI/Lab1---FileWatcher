#include "trackedfile.h"


TrackedFile::TrackedFile(const QString& filePath)
{
    path = filePath;
    QFileInfo fileInfo(path);
    existed = fileInfo.exists();
    size = fileInfo.size();
}

TrackedFile::~TrackedFile()
{}

void TrackedFile::UpdateFileInfo()
{
    QFileInfo fileInfo(path);
    bool exists = fileInfo.exists();
    qint64 currentSize = fileInfo.size();
    if(existed != exists)
    {
        existed = exists;
        size = currentSize;
        changed = false;
        emit fileModified(this);
    }
    else if(size != currentSize)
    {
        size = currentSize;
        changed = true;
        emit fileModified(this);
    }
}

QString TrackedFile::GetFileInfo() const
{
    QFileInfo fileInfo(path);
    QString info = "";
    if(!existed)
    {
        info = fileInfo.fileName() + " not exists";
    }
    else if(changed)
    {
        info = fileInfo.fileName() + " changed. Its size: " + QString::number(size);
    }
    else
    {
        info = fileInfo.fileName() + " exists. Its size: " + QString::number(size);
    }
    return info;
}

QString TrackedFile::GetPath() const
{
    return path;
}
