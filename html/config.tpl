<html><head><title>System Configuration</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>

<h1>System Configuration</h1>
 

<div class="jumbotron">  
    <h2>Wireless AP</h2>
 
      <form id=wifiap method="post" action="config.cgi" onSubmit="if(!confirm('Change WIFI settings?')){return false;}">
      
    <table> 
    <tr><td>SSID: </td><td><input id=SSID  type="text" name="SSID" value="%SSID%"></td></tr>
    <tr><td>Key:</td><td><input id=password  type="text" name="password" value="%password%"></td></tr>
    <tr><td>Channel:</td><td><input id=channel   type="text" name="channel" value="%channel%"></td></tr>
    <tr><td>Authmode:</td><td>
        <select  id=authmode   name="authmode" >
            <option value="0">0 OPEN</option>
            <option value="1">1 WEP</option>
            <option value="2">2 WPA_PSK</option>
            <option value="3">3 WPA2_PSK</option>
            <option value="4">4 WPA_WPA2_PSK</option>
        </select><b>%authmode%</b>
    </td></tr>
    <tr><td>SSID Hidden:</td><td><input id=ssid_hidden   type="text" name="ssid_hidden" value="%ssid_hidden%"></td></tr>
    <tr><td>Max connections:</td><td><input id=max_connection  type="text" name="max_connection" value="%max_connection%"></td></tr>
    <tr><td></td><td></td></tr>
    </table> 
    <button type="button" class="btn  btn-primary " role="button" onclick=" $( '#wifiap' ).submit();">  Apply </button> 
        </form> 
</div>


<div class="jumbotron">  
    <h2>Serial port</h2>
    <table> 
    <tr><td>boud rate: </td><td><input id=time  type="text" name="time" value="115200,n,8,1"></td></tr> 
    </table> 
    <pre>
/user/stdout.c
//Set baud rate and other serial parameters to 115200,n,8,1
uart_div_modify(0, UART_CLK_FREQ/BIT_RATE_115200);
void uart_div_modify(int no, unsigned int freq);

    <pre>
</div>


<div class="jumbotron">  
    <h2>info</h2>
    <pre>
 
    <pre>
    
</div>




<center> 
 <a href=/wifi>Config WIFI</a>&nbsp;&nbsp; | &nbsp;&nbsp;<a href=/>go back Home</a>
</center> 


 <script src="jquery.min.js"></script>   
</body></html>

