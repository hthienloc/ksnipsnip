import QtQuick
import QtQuick.Layouts
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.plasmoid
import org.kde.kirigami as Kirigami

PlasmoidItem {
    id: root

    preferredRepresentation: iconRepresentation
    
    // Header for the widget
    Plasmoid.title: i18n("KSnipSnip")
    Plasmoid.icon: "ksnip"
    
    // Define an action that shows up in the context menu and can be triggered
    Component.onCompleted: {
        plasmoid.setAction("snip", i18n("Take New Snip"), "ksnip");
    }

    function action_snip() {
        launchHelper();
    }

    iconRepresentation: Kirigami.Icon {
        source: plasmoid.icon
        
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.launchHelper()
            }
        }
    }

    import "./lib" as Lib

    function launchHelper() {
        executable.exec("ksnipsnip-helper");
    }

    Lib.ExecUtil {
        id: executable
    }
}
