/*
* Joseph Mills 
*/
import QtQuick 2.0

Item {
    id: basePostModel
    property string source: ""
    property string json: ""
    property int status: XMLHttpRequest.UNSENT
    property var reply
    property var message
    property ListModel model: ListModel { id: model }
    property alias count: model.count
    signal updated()
    onSourceChanged: sendMessage();
    function sendMessage() {
        var xhr = new XMLHttpRequest();
        xhr.open("POST", source);
        xhr.onreadystatechange = function() {
            status = xhr.readyState;
            if (xhr.readyState === XMLHttpRequest.DONE)
                getReply(json = xhr.responseText);
        }
        xhr.send(message);
    }

    function getReply(json) {
        if ( json !== "" ) {
            reply = JSON.parse(json)
            updateJSONModel();
        }
    }
}
