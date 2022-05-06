#include "FileOperator.h"
#include "commonHeaders.h"

bool isFile(const QString& pathName)
{
    // File do not exist or FileName is Empty
    if (pathName.isEmpty() || !QDir().exists(pathName))
    {
        qDebug()<<"isEmpty OR do not exist => "<< pathName;
        return false;
    }

    QFileInfo FileInfo(pathName);

    if(FileInfo.isFile())
    {
        qDebug()<<"File Exist"<<" => "<< pathName;
        return true;
    }

    qDebug()<<"is not File"<<" => "<< pathName;
    return false;
}


bool createFile(const QString& fileName)
{
    QFile qfile(fileName);
    if(qfile.open(QIODevice::ReadWrite))
    {
        qDebug()<<"Create File Success => "<<fileName;
        qfile.close();
        return true;
    }
    qfile.close();
    return false;
}


