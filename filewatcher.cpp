#include "filewatcher.h"


FileWatcher::FileWatcher(ILog* log)
{
    logger = log;

    if(log == nullptr)
    {
        qWarning("FileWatcher(Ilog*): Logger not initialized");
    }
}

FileWatcher::~FileWatcher()
{
    trackedFiles.clear();
    modifiedFiles.clear();
}

FileWatcher& FileWatcher::Instance(ILog* log)
{
    static FileWatcher fileWatcher(log);
    return fileWatcher;
}

void FileWatcher::AddToModifiedFiles(TrackedFile* file)
{
    modifiedFiles.push_back(file);
}

bool FileWatcher::RegisterFile(const QString& fileDir)
{
    foreach(TrackedFile* file, trackedFiles)
    {
        if(file->GetPath() == fileDir)
        {
            qWarning("The file is already being tracked");
            return false;
        }
    }
    TrackedFile* fileInfo = new(std::nothrow) TrackedFile(fileDir);
    //TrackedFile* fileInfo = nullptr;
    if(fileInfo)
    {
        trackedFiles.push_back(fileInfo);
        connect(fileInfo, &TrackedFile::fileModified, this, &FileWatcher::AddToModifiedFiles);
    }
    else
    {
        qWarning("FileWatcher::RegisterFile(const QString&): File not initialized, not enough memory");
    }

    return true;
}

void FileWatcher::RemoveFile(const QString &fileDir)
{
    for(int i = 0; i < trackedFiles.size(); i++)
    {
        if(trackedFiles[i]->GetPath() == fileDir)
        {
            trackedFiles.remove(i);
            break;
        }
    }
}

void FileWatcher::UpdateFileInfo()
{
    for(int i = 0; i < trackedFiles.size(); i++)
    {
        trackedFiles.at(i)->UpdateFileInfo();
    }

    if(!modifiedFiles.empty())
    {
        ShowFileStatus();
        modifiedFiles.clear();
    }
    return;
}

void FileWatcher::ShowFileStatus() const
{
    if(logger)
    {
        for(int i = 0; i < trackedFiles.size(); i++)
        {
            logger->Write(trackedFiles.at(i)->GetFileInfo());
        }
    }
    else
    {
        qWarning("FileWatcher::initialFileStatus(): Logger not initialized");
    }
}

int FileWatcher::GetNumberOfMonitoredFiles() const
{
    return trackedFiles.length();
}

