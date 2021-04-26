#ifndef UTILS_H
#define UTILS_H

#include <QWidget>

class Utils
{
public:
    Utils();
    static void DestructorMsg(const QString value);
    static void DestructorMsg(const QObject *object);
};

#endif // UTILS_H
