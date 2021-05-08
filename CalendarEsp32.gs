/*
Calendar connection script
*/
function doGet(){
  var now = new Date()
  var nowInMS = now.getTime(); // 1562300592245
  var add = 24 * 60 * 60 * 1000; // 43200000 = 24 hours in milliseconds
  var dday;
  var i = 0;
  finalStr = "";

  //Get next 6 days information
  for (i=0; i<6; i++){
    dday = nowInMS + (add * i)
    finalStr += GetEvents(new Date(dday));
    if(i!=5){
      finalStr += "|\n"
    }
  }
  Logger.log(finalStr);
  return ContentService.createTextOutput(finalStr);
}

//Calendar Event Info getter
// - Name
// - Location
// - Start Time
// - End Time (or date) eg. tomorrow
// - All Day?? (no times needed)
// - Invitees

function GetEvents(date){
  var _calendarName = 'CalendarEsp32' //Your Calendar Name in Google Calendar
  var Cal = CalendarApp.getCalendarsByName(_calendarName)[0];
  var Now = date;
  var events = Cal.getEventsForDay(Now);
  str = "";
  finalStr = "";
  finalStr += Now.toDateString() + "\n";
  for (var i = 0; i < events.length; i++)
  {
    var allDay;
    if(events[i].getStartTime().toLocaleTimeString().search("0:00:00") >= 0 &&
       events[i].getEndTime().toLocaleTimeString().search("0:00:00") >= 0)
    {
      allDay = "allday";
    }
    else
    {
      allDay = "notday";
    }
    var guestList = events[i].getGuestList();

    str += events[i].getTitle();
    if(events[i].getLocation() != ""){
      str += ", " + events[i].getLocation()
    }
    while(str.length < 36){
      str += ' ' ;
    }

    if(allDay != "allday"){
      str += events[i].getStartTime().toLocaleTimeString() + '-' ;
      str += events[i].getEndTime().toLocaleTimeString() ;
    }
    else{
      str += 'All day';
    }
    for (var j = 0; j < guestList.length; j++)
    {
      if(guestList[j].getName() != _calendarName)
      {
        if(guestList[j].getName() != "") {
          str += guestList[j].getName() + ":" ;
        }
        else
        {
          str += guestList[j].getEmail() + ":" ;
        }
      }
    }
    //Remove last ":" from guest lists
    finalStr += str + '\n';
    str = "";
  }
  return finalStr;
}