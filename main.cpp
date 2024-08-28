#include <QCoreApplication>
#include <server.h>
#include <anotherserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList arguments = a.arguments();

    Server s;


    s.portTime = 65535;

    if (arguments.size() > 1) {
        bool ok;
        quint16 parsedPort = arguments[1].toUShort(&ok);
        if (ok) {
            s.portTime = parsedPort;
        } else {
            qDebug() << "Введите желаемый номер порта. Пример ./Server 65535";
        }
    }

    return a.exec();
}
