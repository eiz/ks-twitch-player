#ifndef KS_TWITCH_PLAYER_PLUGIN_H
#define KS_TWITCH_PLAYER_PLUGIN_H

#include <QQmlExtensionPlugin>

class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // KS_TWITCH_PLAYER_PLUGIN_H

