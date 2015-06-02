import QtQuick 2.0
Item{
    //    http://localhost:8080/rest/v1/logout/admin.json
    property string url
    property string username:
        PostModel {
        id: personModel
        source: url
        property variant attributes: {
            'username': '',
                    'email':'',
                    'password':'',
                    'homeUrl':'',
                    'disabled':'',
                    'receiveAlarmEmails' :'',
                    'muted':'',
                    'timezone':''
        }
        function updateJSONModel() {
            var ob = JSON.parse(json)
            attributes = {
                'username': ob.username,
                'email': ob.email,
                'password': ob.password,
                'homeUrl' :ob.homeUrl,
                'disabled':ob.disabled,
                'receiveAlarmEmails':ob.receiveAlarmEmails,
                'muted':ob.muted,
                'timezone':ob.timezone
            };
            updated()
        }
    }
}
