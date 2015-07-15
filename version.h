#ifndef VERSION_H
#define VERSION_H

#include <QJSEngine>

static QJSValue appVersionSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)

    QJSValue appInfo = scriptEngine->newObject();
    appInfo.setProperty("SmallVersion", APP_SMALL_VERSION);
    appInfo.setProperty("FullVersion", APP_FULL_VERSION);
    return appInfo;
}

#endif // VERSION_H

