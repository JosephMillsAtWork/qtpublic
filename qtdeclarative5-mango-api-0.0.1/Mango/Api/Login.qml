import QtQuick 2.0
Item{
    property string url
    property string passwd
    property string username:
        PostModel {
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
