#include "validation.h"

bool checkRequest(QString str)
{
    QRegularExpression regex(R"(\b([0-9]|1[0-5])\b,\s*\b([0-2])\b,\s*\b([0-6][0-4]|[0-9]|[1-5][0-9])\b)");
    QRegularExpressionMatch match = regex.match(str);

    return  match.hasMatch();
}
