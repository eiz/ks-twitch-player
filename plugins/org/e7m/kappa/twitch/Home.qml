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
    highlight: activeFocus
    TwitchApiClient { id: twitch }
    anchors.fill: parent
    delegate: SLRoundedPanel {
        id: wrapper
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        highlight: activeFocus

        Text {
            property var stream: list.model[index]
            anchors.fill: parent
            text: stream.channel.display_name + ": " + stream.game + " (" +
                  stream.viewers + " viewers)"
            color: "white"
        }
    }

    Component.onCompleted: {
        twitch.getStreams(function (result) {
            if (result.error) {
                console.log("error", result.error);
            } else {
                list.model = result.data.streams;
            }
        });
    }
}
