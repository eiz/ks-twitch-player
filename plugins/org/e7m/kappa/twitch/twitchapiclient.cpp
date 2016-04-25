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

#include <QJsonDocument>
#include <QJsonObject>
#include <QJSEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "twitchapiclient.h"

TwitchApiClient::TwitchApiClient(QObject *parent) :
    QObject(parent)
{
}

void TwitchApiClient::getFollowing(QJSValue cb)
{

}

void TwitchApiClient::getStreams(QJSValue cb)
{
    if (!_streamsCb.isUndefined()) {
        // TODO
        return;
    }

    _streamsCb = cb;

    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QUrl url("https://api.twitch.tv/kraken/streams");
    QNetworkRequest req;

    ssl.setPeerVerifyMode(QSslSocket::VerifyNone);
    req.setSslConfiguration(ssl);
    req.setUrl(url);
    mgr->get(req);
    connect(
        mgr, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(onStreamsResult(QNetworkReply*)));
}

void TwitchApiClient::onStreamsResult(QNetworkReply *reply)
{
    QJSValue val = _streamsCb.engine()->newObject();

    if (reply->error() != QNetworkReply::NoError) {
        val.setProperty("error", reply->errorString());
    } else {
        QByteArray arr = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(arr);

        val.setProperty(
            "data", _streamsCb.engine()->toScriptValue(doc.object()));
    }

    QJSValue cb = _streamsCb;
    _streamsCb = QJSValue();
    cb.call(QJSValueList {val});
}

void TwitchApiClient::getGames(QJSValue cb)
{

}
