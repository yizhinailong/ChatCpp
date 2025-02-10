#ifndef GLOBAL_H
#define GLOBAL_H

#include <QRegularExpression>
#include <QWidget>
#include <functional>

#include "QStyle"

/* refresh qss */
extern std::function<void(QWidget*)> repolish;

#endif // GLOBAL_H
