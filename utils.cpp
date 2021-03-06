#include "utils.h"
#include <QDebug>

static QString DESTRUCTOR_MSG = QStringLiteral("Running the %1 destructor");

void Utils::DestructorMsg(const QString value) {
  qDebug() << DESTRUCTOR_MSG.arg(value);
}

void Utils::DestructorMsg(const QObject *object) {
  DestructorMsg(object->metaObject()->className());
}
