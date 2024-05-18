#include "filewatcher.h"


FileWatcher::FileWatcher(ILog* log)
{
    logger = log;
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
    TrackedFile* fileInfo = new TrackedFile(fileDir);
    trackedFiles.push_back(fileInfo);
    connect(fileInfo, &TrackedFile::fileModified, this, &FileWatcher::AddToModifiedFiles);
    return true;
}

void FileWatcher::UpdateFileInfo()
{
    for(int i = 0; i < trackedFiles.size(); i++)
    {
        trackedFiles.at(i)->UpdateFileInfo();
    }

    if(!modifiedFiles.empty())
    {
        for(int i = 0; i < modifiedFiles.size(); i++)
        {
            logger->Write(modifiedFiles.at(i)->GetFileInfo());
        }
        modifiedFiles.clear();
    }
    return;
}

void FileWatcher::InitialFileStatus() const
{
    for(int i = 0; i < trackedFiles.size(); i++)
    {
        logger->Write(trackedFiles.at(i)->GetFileInfo());
    }
}
