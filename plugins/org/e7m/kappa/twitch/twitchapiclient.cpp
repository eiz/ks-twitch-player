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
#include <QJSValueIterator>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include "twitchapiclient.h"

TwitchApiClient::TwitchApiClient(QObject *parent) :
    QObject(parent),
    _network(new QNetworkAccessManager(this)),
    _ssl(QSslConfiguration::defaultConfiguration())
{
    _ssl.setPeerVerifyMode(QSslSocket::VerifyNone);
}

static QString apiUrl(QString resource)
{
    return QString("https://api.twitch.tv/kraken/") + resource;
}

static QString optionsToQuery(QJSValue opts)
{
    QString result;
    bool first = true;

    if (!opts.isObject()) {
        return result;
    }

    QJSValueIterator it(opts);

    while (it.hasNext()) {
        if (!first) {
            result.append("&");
        } else {
            first = false;
        }

        it.next();
        result.append(QUrl::toPercentEncoding(it.name()));
        result.append("=");
        result.append(QUrl::toPercentEncoding(it.value().toString()));
    }

    return result;
}

static void apiCallback(QJSValue cb, QNetworkReply *reply)
{
    QJSValue val = cb.engine()->newObject();

    if (reply->error() != QNetworkReply::NoError) {
        val.setProperty("error", reply->errorString());
    } else {
        QByteArray arr = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(arr);

        val.setProperty(
            "data", cb.engine()->toScriptValue(doc.object()));
    }

    reply->deleteLater();
    cb.call(QJSValueList {val});
}

QNetworkRequest TwitchApiClient::apiRequest(QJSValue opts, QString resource)
{
    QUrl url(apiUrl(resource));
    QNetworkRequest req;

    url.setQuery(optionsToQuery(opts));
    req.setSslConfiguration(_ssl);
    req.setUrl(url);
    return req;
}

void TwitchApiClient::getFollowing(QJSValue opts, QJSValue cb)
{
    QNetworkReply *reply = _network->get(apiRequest(opts, "following"));

    connect(reply, &QNetworkReply::finished, [cb, reply]() {
        apiCallback(cb, reply);
    });
}

void TwitchApiClient::getStreams(QJSValue opts, QJSValue cb)
{
    QNetworkReply *reply = _network->get(apiRequest(opts, "streams"));

    connect(reply, &QNetworkReply::finished, [cb, reply]() {
        apiCallback(cb, reply);
    });
}

void TwitchApiClient::getGames(QJSValue opts, QJSValue cb)
{
    QNetworkReply *reply = _network->get(apiRequest(opts, "games"));

    connect(reply, &QNetworkReply::finished, [cb, reply]() {
        apiCallback(cb, reply);
    });
}
