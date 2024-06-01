#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QObject>
#include <QVector>

#include "trackedfile.h"
#include "ilog.h"


class FileWatcher: public QObject
{
    Q_OBJECT
public:
    static FileWatcher& Instance(ILog*);

    bool RegisterFile(const QString& fileDir);
    void RemoveFile(const QString& fileDir);
    void UpdateFileInfo();
    void InitialFileStatus() const;
    int GetNumberOfMonitoredFiles() const;

public slots:
    void AddToModifiedFiles(TrackedFile*);

private:
    FileWatcher(ILog*);
    ~FileWatcher();
    FileWatcher(FileWatcher const&) = delete;
    FileWatcher& operator = (FileWatcher const&) = delete;

private:
    ILog* logger;
    QVector<TrackedFile*> trackedFiles;
    QVector<TrackedFile*> modifiedFiles;
};

#endif // FILEWATCHER_H
