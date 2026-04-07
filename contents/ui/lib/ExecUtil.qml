import QtQuick
import org.kde.plasma.plasma5support as Plasma5Support

Plasma5Support.DataSource {
    id: executable

    property var listeners: ({}) 

    signal exited(string cmd, int exitCode, int exitStatus, string stdout, string stderr)

    function exec(cmd, callback) {
        if (typeof callback === 'function') {
            if (listeners[cmd]) {
                exited.disconnect(listeners[cmd]);
                delete listeners[cmd];
            }
            var listener = (c, code, status, out, err) => {
                if (c === cmd) {
                    delete listeners[cmd];
                    callback(c, code, status, out, err);
                }
            };
            listeners[cmd] = listener;
            exited.connect(listener);
        }
        connectSource(cmd);
    }

    engine: "executable"
    connectedSources: []
    onNewData: (sourceName, data) => {
        var cmd = sourceName;
        var exitCode = data["exit code"];
        var exitStatus = data["exit status"];
        var stdout = data["stdout"];
        var stderr = data["stderr"];
        
        exited(cmd, exitCode, exitStatus, stdout, stderr);
        disconnectSource(sourceName);
    }
}
