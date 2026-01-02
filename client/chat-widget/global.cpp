#include "global.hpp"

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish = [](QWidget* widget) {
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
};
