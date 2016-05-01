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

import QtQuick 2.0
import org.e7m.kappa.twitch 1.0
import org.e7m.kappa.core.ui 1.0

SLListView {
    id: list
    focus: true
    TwitchApiClient {
        id: twitch
        clientId: "40hx9adcjrbka93knh3uy93invyebr3"
    }
    anchors.fill: parent

    model: ListModel {
        id: listModel
    }

    delegate: SLRoundedPanel {
        id: wrapper
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        highlight: activeFocus

        Text {
            anchors.fill: parent
            text: displayName + ": " + game + " (" + viewers + " viewers)"
            color: "white"
        }
    }

    WorkerScript {
        id: worker
        source: "listloader.js"
    }

    Component.onCompleted: {
        twitch.getStreams({limit: 100}, function (result) {
            if (result.error) {
                console.log("error", result.error);
            } else {
                worker.sendMessage({
                    model: listModel,
                    data: result.data.streams,
                    type: "streams"
                });
            }
        });
    }
}
