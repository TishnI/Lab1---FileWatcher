#ifndef TRACKEDFILE_H
#define TRACKEDFILE_H

#include <QObject>
#include <QFileInfo>
#include <QString>
#include <QDebug>

class TrackedFile: public QObject
{
    Q_OBJECT
public:
    TrackedFile(const QString& file);
    ~TrackedFile();

public:
    void UpdateFileInfo();
    QString GetFileInfo() const;
    QString GetPath() const;

signals:
    void fileModified(TrackedFile*);

private:
    QString path;
    bool existed;
    qint64 size;
    bool changed = false;
};

#endif // TRACKEDFILE_H
