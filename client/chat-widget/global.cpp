#include "global.hpp"

std::function<void(QWidget*)> repolish = [](QWidget* widget) {
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
};
