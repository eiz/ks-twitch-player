// ks-twitch-player
// Copyright (C) 2016 Mackenzie Straight
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ks-twitch-player.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TWITCHAPICLIENT_H
#define TWITCHAPICLIENT_H

#include <QJSValue>
#include <QNetworkReply>
#include <QObject>

class TwitchApiClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString clientId READ clientId WRITE setClientId)

public:
    explicit TwitchApiClient(QObject *parent = 0);

    QString clientId() { return _clientId; }
    void setClientId(QString value) { _clientId = value; }
    Q_INVOKABLE void getFollowing(QJSValue opts, QJSValue cb);
    Q_INVOKABLE void getStreams(QJSValue opts, QJSValue cb);
    Q_INVOKABLE void getGames(QJSValue opts, QJSValue cb);

private:
    QNetworkRequest apiRequest(QJSValue opts, QString resource);

    QString _clientId;
    QNetworkAccessManager *_network;
    QSslConfiguration _ssl;
};

#endif // TWITCHAPICLIENT_H
