<html><head><title>WiFi PhoT0</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<center>
<h1>WiFi PhoT0</h1>

<div class="jumbotron"> 
<script>  
var isTimerOn=%isTimerOn%;

    function updateBtsState(str) {
       
                if(isTimerOn==true){
                    $("#btTimer").text('Stop');
                    $("#time").prop('disabled', true);
                }else{ 
                    $("#btTimer").text('Start Timer');
                   $("#time").prop('disabled', false);
                }
    }
    
    function isBlank(str) {
        return (!str || /^\s*$/.test(str));
    }
    
    function doShutter (str){
        $.post("timer.cgi", {
            shutter:str
        } );
    }
    function doTimer (str){
        $.post("timer.cgi", {
            timer:str
        } ).done(function() {
            if (isTimerOn==true){
                isTimerOn=false;
            }else{
                isTimerOn=true;
            }    
            updateBtsState(isTimerOn);
          });
    }  
        
    function doCMD (cc, str){
        $.post("timer.cgi", {
            cc:str
        },
        function(data,status){
        
            $('#errorMSG').html("<b>Data:</b><br> " + data + "<br><br><b>POST Status:</b> " + status);
            if(!isBlank(data)){  
                $('#errorMSG1').show();
            }else{ 
                $('#errorMSG1').hide();                        
            }  
        }).done(function() {
            alert( "second success" );
          }).fail(function() {
            alert( "error" );
          });
    }     
     
</script>
<center>   
    <button type="button" class="btn  btn-primary   btn-lg" role="button" onclick="doShutter('now');">  Shutter  </button>
</center> 
<center>
    <br><b>Time: </b> 
    <input id=time class="in" type="text" name="time" value="%timerInterval%">sec<br>
    <button id=btTimer type="button" class="btn  btn-primary   btn-lg" role="button" onclick="doTimer($('#time').val());">  Start Timer </button> 
</center>  
</div>
<div id=errorMSG1>
    <div id=errorMSG>
Timer triggered <b>%timerCounter%</b> times<br>
Last trigger was <b>%triggerLastTime%</b> seconds ago
</div>
</div>


<!--
    <p>If there's a LED connected to GPIO2, it's now %ledstate%.</p>
    <form method="post" action="led.cgi">
        <input type="submit" name="led" value="1">
        <input type="submit" name="led" value="0">
    </form> 
    --> 
    <input type="checkbox" value="1" name="doUpdate" id="doUpdate" checked="checked" />auto update this info
   <br><br>
   <a href=config.tpl>System Config</a>
    
    </center>
     
    <script src="jquery.min.js"></script>
    <script> 
    updateBtsState(isTimerOn);
    
    var myVar=setInterval(function () {myTimer()}, 5000);

function myTimer() {
    if($("#doUpdate").is(':checked')){
         $.post("timer.cgi", {
                status:'info'
            } ,
            function(data,status){
            
                $('#errorMSG').html(data + "<br>");
             
            });
        }
}
    
    
    </script>
    
</body></html>
