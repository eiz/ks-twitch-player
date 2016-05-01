function loadStreams(msg) {
    msg.model.clear();

    for (var i = 0; i < msg.data.length; ++i) {
        var item = msg.data[i];

        msg.model.append({
            displayName: item.channel.display_name,
            game: item.game,
            viewers: item.viewers
        });
    }

    msg.model.sync();
}

WorkerScript.onMessage = function(msg) {
    switch (msg.type) {
    case "streams": loadStreams(msg);
    }
};
