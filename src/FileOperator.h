#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include "commonHeaders.h"
#include <QTextStream>

bool isFile(const QString& pathName);
bool createFile(const QString& fileName);

#endif // FILEOPERATOR_H
