import QtQuick
import QtQuick.Layouts
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.plasmoid
import org.kde.kirigami as Kirigami

PlasmoidItem {
    id: root

    // Core Plasmoid properties
    Plasmoid.title: i18n("KSnipSnip")
    Plasmoid.icon: "spectacle"
    Plasmoid.status: PlasmaCore.Types.ActiveStatus
    
    // Explicitly define represention for Taskbar/System Tray
    compactRepresentation: Kirigami.Icon {
        source: plasmoid.icon
        
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.launchHelper()
            }
        }
    }

    // Context menu actions
    Component.onCompleted: {
        plasmoid.setAction("snip", i18n("Take New Snip"), "spectacle");
    }

    function action_snip() {
        launchHelper()
    }

    import "./lib" as Lib

    function launchHelper() {
        executable.exec("ksnipsnip-helper")
    }

    Lib.ExecUtil {
        id: executable
    }
}
