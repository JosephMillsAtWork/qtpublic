
import QtQuick 2.0
Item{
BaseModel {
     id: getTimValues
     source: url
     property variant attributes: {
         'displayName': '',
                 'coverPhoto':'',
                 'iconImage':'',
                 'occupation':'',
                 'tagline':''
     }
     function updateJSONModel() {
         var ob = JSON.parse(json)
//add a loop here
         attributes = {
             'id': ob.id,
             'coverPhoto': ob.cover.coverPhoto.url,
             'displayName': ob.displayName,
             'iconImage' :ob.image.url,
             'occupation':ob.occupation,
             'tagline':ob.tagline
         };
         updated()
     }
 }
}

