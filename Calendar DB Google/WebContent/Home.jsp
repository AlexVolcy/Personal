<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<link rel="stylesheet" type="text/css" href="SignIn.css" />
<title>Home</title>
</head>
<body>

<header>
<h3>Garbage</h3>
</header>

    
    <p><a class="one" href="Profile.html" target="_blank">Profile</a></p>
	<p><a class="two" href="Home.jsp" target="_blank">Home</a></p>
	<p><a class="three" href="Home.jsp" target="_blank">Sycamore Calendar</a></p>
	
	<h2>Home</h2>
	<div class="tableForm">
		<table id="homeTable">
		<tr>
			<th><input placeholder ="Event Title" id="eventTitle" name = "eventTitle" type="text" value =${param.eventTitle!=null? param.eventTitle : ''}><br /></th>
		</tr>
		<tr>
			<th><input placeholder="Start Date" type ="text" id="startDate" onfocus="(this.type='date')"name = "startDate" value =${param.startDate!=null? param.startDate : ''}><br/></th>
			<th><input placeholder ="End Date" type ="text" id="endDate" onfocus="(this.type='date')"name = "endDate" value =${param.endDate!=null? param.endDate : ''}><br/></th>
		</tr>
		<tr>
			<th><input placeholder="Start Time" type="text" id="startTime" onfocus="(this.type='time')" name = "startTime" value =${param.endDate!=null? param.endDate : ''}><br/></th>
			<th><input placeholder="End Time" type ="text" id="endTime" onfocus="(this.type='time')" name = "endTime" value =${param.endTime!=null? param.endTime : ''}><br/></th>
		</tr>
		</table>
	</div>
	<div class="eventButton">
		<button onclick="addEvent()">Add Event</button>
	</div>		
    <div class="pic2Pos">
   		<img id="profile2Picture">
    </div>
    <div class="name2Pos">
        <p id="new2Name"></p>
    </div>
		
	<p id="demo"></p>
	<p id="demo2"></p>
	<p id="demo3"></p>
	<p id="demo4"></p>
	<p id="demo5"></p>
    <script type="text/javascript">
    
	function addEvent()
	{
		
		var eventTitle = document.getElementById("eventTitle").value;
		var startDate = document.getElementById("startDate").value;
		var startTime = document.getElementById("startTime").value;
		var endDate = document.getElementById("endDate").value;
		var endTime = document.getElementById("endTime").value;
		var startDateTime = document.getElementById("startDate").value + "T" + document.getElementById("startTime").value + ":00-07:00";
		var endDateTime = document.getElementById("endDate").value + "T" + document.getElementById("endTime").value + ":00-07:00";
		
		if (!eventTitle) document.getElementById("demo").innerHTML = "Error, need correct event title";
		if (!startDate) document.getElementById("demo2").innerHTML = "Error, need correct start date";
		if (!startTime) document.getElementById("demo3").innerHTML = "Error, need correct start time";
		if (!endDate) document.getElementById("demo4").innerHTML = "Error, need correct end date";
		if (!endTime) document.getElementById("demo5").innerHTML = "Error, need correct end time";
		
				
		var event = {
				  'summary': eventTitle,
				  'start': {
				    'dateTime': startDateTime, //html getdateinput, gettimeinput date object can convert it
				    'timeZone': 'America/Los_Angeles'
				  },
				  'end': {
				    'dateTime': endDateTime,
				    'timeZone': 'America/Los_Angeles'
				  },
				};

				var request = gapi.client.calendar.events.insert({
				  'calendarId': 'primary',
				  'resource': event
				});

				request.execute(function(event) {
				  appendPre('Event created: ' + event.htmlLink);
				  console.log("eventAdded");
				});				
		};
	
	var request = gapi.client.calendar.events.insert({
		  'calendarId': 'primary',
		  'resource': event
		});

		request.execute(function(event) {
		  appendPre('Event created: ' + event.htmlLink);
		});
	</script>
	

<footer>
	<h3>Cities</h3>
</footer>

</body>
	<script>
	var profileImageURL = sessionStorage.getItem("profileImage");
	var userName = sessionStorage.getItem("Name");
	document.getElementById("profile2Picture").src = profileImageURL;
	document.getElementById("new2Name").innerHTML = userName;
	</script>
</html>