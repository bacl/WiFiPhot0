/*
Some random cgi routines. Used in the LED example and the page that returns the entire
flash as a binary. Also handles the hit counter on the main page.
*/

/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include <string.h>
#include <osapi.h>
#include "user_interface.h"
#include "mem.h"
#include "httpd.h"
#include "cgi.h"
#include "io.h"
#include "espmissingincludes.h"
#include <ip_addr.h>

//cause I can't be bothered to write an ioGetLed()
//static char currLedState=0;

//static const char *httpOKHeader="HTTP/1.0 200 OK\r\nServer: esp8266-httpd/0.1\r\nContent-Type: text/plain\r\n\r\nOk.\r\n";

static ETSTimer some_timer;  
static char timerIsOn=0;
static int  timerInterval=60;// tempo em sec
 

static void ICACHE_FLASH_ATTR  some_timerfn(void *arg) { 
	ioLed(0);  
	timerCounter++;	   
}


// send response  http
void ICACHE_FLASH_ATTR sendResponse(HttpdConnData *conn, char *msg) {
	char buff[323];
	int l;
	l=os_sprintf(buff, "HTTP/1.0 200 OK\r\nServer: esp8266-httpd/0.1\r\nContent-Type: text/plain\r\n\r\n%s\r\n", msg);
	espconn_sent(conn->conn, (uint8 *)buff, l);
}

int ICACHE_FLASH_ATTR cgiTimer(HttpdConnData *connData) { 
	char buff[1024];
    char msg[223];
    msg[0]='X';
    msg[1]='X';
    msg[2]='\0';
	
	if (connData->conn==NULL) {
		//Connection aborted. Clean up.
		return HTTPD_CGI_DONE;
	}

    ///////////////////////////////////////////////////////////////////
    /// Shutter
	if (httpdFindArg(connData->postBuff, "shutter", buff, sizeof(buff))>0) {
		 // currLedState=atoi(buff);
 	    ioLed(0);    
		    
		    
		    
	}else 
    ///////////////////////////////////////////////////////////////////
    /// Timer 
    if (httpdFindArg(connData->postBuff, "timer", buff, sizeof(buff))>0) {

	    if (timerIsOn==0){ 
	        timerInterval=atoi(buff);
	        int timerIntervalmls=timerInterval*1000;
	        os_printf("TIMER: set interval time: %dms\n",timerIntervalmls);
	        
	        timerIsOn=1;
	        timerCounter=1;	   
	        // primeiro trigger se nao so passado xx sec é q dispara
	        ioLed(0);     
	        // Arm timer
	        os_timer_disarm(&some_timer);  
	        os_timer_setfn(&some_timer, some_timerfn, NULL);                 
            os_timer_arm(&some_timer, timerIntervalmls, 1);
            
	    }else{ 
	        timerIsOn=0;
	        //Disarm timer
	        os_timer_disarm(&some_timer);
	        //ioLed(0); // so para o caso de ser interompido desliga o led
	    }
	  
    }else
    ///////////////////////////////////////////////////////////////////
    /// status
    if (httpdFindArg(connData->postBuff, "status", buff, sizeof(buff))>0) { 
      	       
         if(timerIsOn==1){
          uint32 time = system_get_time()/TIMEMILIMIL-triggerLastTime;	
          if(time<0)time=0;
          int remaningTime=timerInterval-time;
          os_sprintf(msg, "Timer triggered <b>%d</b> times.<br>Time left to next trigger <b>%d</b> seconds.", timerCounter, remaningTime);	
           //os_sprintf(msg, "Timer triggered <b>%d</b> times.<br>Last trigger was <b>%d</b> seconds ago.", timerCounter, time);	
         }else{
           os_sprintf(msg, "Timer triggered <b>%d</b> times.", timerCounter);	
         }
          os_printf("> entrou no status [ %d ][ %d ]  \n\n",timerCounterOverAll,timerCounter);
            //		       os_sprintf(msg, "<p>Triggered <b>%d</b> times.</p><p>Triggered <b>%d</b> times by the current timer.<br>Last trigger was <b>%d</b> seconds ago</p>", timerCounterOverAll,timerCounter, time);	
    }     
    
    
    
    
    
    
    // envia resposta ok	 
	sendResponse(connData,msg );
	return HTTPD_CGI_DONE;
}





void printApconfig(){
 struct softap_config *config = (struct softap_config  *)os_malloc(sizeof(struct softap_config  ));       
    wifi_softap_get_config(config);
  os_printf("\nWifi AP config:\n");
     
    	os_printf("\nSSID: %s\n",config->ssid);
		os_printf("password: %s\n",config->password);
		os_printf("ssid_len: %d \n",config->ssid_len);
		os_printf("channel: %d\n",config->channel);
		char* authmode="noone";
		if(AUTH_OPEN == config->authmode )
		    authmode="AUTH_OPEN ";
		else if(AUTH_WEP == config->authmode )
		    authmode="AUTH_WEP ";
		else if(AUTH_WPA_PSK == config->authmode )
		    authmode="AUTH_WPA_PSK ";
		else if(AUTH_WPA2_PSK == config->authmode )
		    authmode="AUTH_WPA2_PSK ";
		else if(AUTH_WPA_WPA2_PSK == config->authmode )
		    authmode="AUTH_WPA_WPA2_PSK ";		 
		os_printf("authmode: %d  %s\n",config->authmode,authmode );		
		os_printf("ssid_hidden: %d\n",config->ssid_hidden);
		os_printf("max_connection: %d\n\n",config->max_connection);
		
 

}


int ICACHE_FLASH_ATTR cgiConfig(HttpdConnData *connData) {
	 
	char buff[1024]; 
	if (connData->conn==NULL) {
		//Connection aborted. Clean up.
		return HTTPD_CGI_DONE;
	}

    struct softap_config *config = (struct softap_config  *)os_malloc(sizeof(struct softap_config  ));       
    wifi_softap_get_config(config);
	

	// if (httpdFindArg(connData->getArgs, "SSID", buff, sizeof(buff))>0) {
	if (httpdFindArg(connData->postBuff, "SSID", buff, sizeof(buff))>0) {
	     os_sprintf( (char *) config->ssid, "%s", buff);	     
		config->ssid_len=os_strlen((const char*)config->ssid);
	} 
    if (httpdFindArg(connData->postBuff, "password", buff, sizeof(buff))>0) {
		 os_sprintf( (char *) config->password, "%s", buff);			    
	} 
    if (httpdFindArg(connData->postBuff, "channel", buff, sizeof(buff))>0) {
	     config->channel=atoi(buff);		    
	} 
    if (httpdFindArg(connData->postBuff, "authmode", buff, sizeof(buff))>0) {
	     config->authmode=atoi(buff);		    
	} 
    if (httpdFindArg(connData->postBuff, "ssid_hidden", buff, sizeof(buff))>0) {
	     config->ssid_hidden=atoi(buff);		    
	}  
    if (httpdFindArg(connData->postBuff, "max_connection", buff, sizeof(buff))>0) {
	     config->max_connection=atoi(buff);		    
	}  
     
     
     
     
        os_printf("\nChanging WIFI to:\n");
     
    	os_printf("\nSSID: %s\n",config->ssid);
		os_printf("password: %s\n",config->password);
		os_printf("ssid_len: %d \n",config->ssid_len);
		os_printf("ssid_len: %d \n",os_strlen((const char*)config->ssid));
		os_printf("channel: %d\n",config->channel);
		char* authmode="noone";
		if(AUTH_OPEN == config->authmode )
		    authmode="AUTH_OPEN ";
		else if(AUTH_WEP == config->authmode )
		    authmode="AUTH_WEP ";
		else if(AUTH_WPA_PSK == config->authmode )
		    authmode="AUTH_WPA_PSK ";
		else if(AUTH_WPA2_PSK == config->authmode )
		    authmode="AUTH_WPA2_PSK ";
		else if(AUTH_WPA_WPA2_PSK == config->authmode )
		    authmode="AUTH_WPA_WPA2_PSK ";		 
		os_printf("authmode: %d  %s\n",config->authmode,authmode );		
		os_printf("ssid_hidden: %d\n",config->ssid_hidden);
		os_printf("max_connection: %d\n\n",config->max_connection);
		
		
		 
		wifi_softap_set_config(config);
		 
		printApconfig();
    
    
	httpdRedirect(connData, "/config.tpl");
	return HTTPD_CGI_DONE;
}







//Template code for the SystemConfig page.
void ICACHE_FLASH_ATTR tplConfig(HttpdConnData *connData, char *token, void **arg) {
	
    struct softap_config *config = (struct softap_config  *)os_malloc(sizeof(struct softap_config  ));
    wifi_softap_get_config(config);
		 
	char buff[128];
	if (token==NULL) return;	 
    os_strcpy(buff, "Unknown");
    
	if (os_strcmp(token, "SSID")==0) {		 
			os_sprintf(buff, "%s", config->ssid);	
	}else if (os_strcmp(token, "authmode")==0) {		
			os_sprintf(buff, "%d", config->authmode);	
	}else if (os_strcmp(token, "password")==0) {		 
			os_sprintf(buff, "%s",  config->password);		
	}else if (os_strcmp(token, "channel")==0) {		 
			os_sprintf(buff, "%d", config->channel);		
	}else if (os_strcmp(token, "max_connection")==0) {		 
			os_sprintf(buff, "%d", config->max_connection);		
	}else if (os_strcmp(token, "ssid_hidden")==0) {		 
			os_sprintf(buff, "%d", config->ssid_hidden);		
	}else if (os_strcmp(token, "ssid_len")==0) {		 
			os_sprintf(buff, "%d", config->ssid_len);		
	}  else if (os_strcmp(token, "otherInfo0")==0) {	    	 
			  
//#define STATION_IF      0x00
//#define SOFTAP_IF       0x01

//bool wifi_get_ip_info(uint8 if_index, struct ip_info *info);
///bool wifi_set_ip_info(uint8 if_index, struct ip_info *info);
//bool wifi_get_macaddr(uint8 if_index, uint8 *macaddr);
//bool wifi_set_macaddr(uint8 if_index, uint8 *macaddr);
        struct ip_info *info=NULL;
        bool r=false;
        uint8 if_index;
        
        if_index=0x00;
	    r =  wifi_get_ip_info( if_index,info);
	    os_sprintf(buff, "IF %d, r:%d, ip "IPSTR, if_index, r, IP2STR(&info->ip) );		
	}	
	
	espconn_sent(connData->conn, (uint8 *)buff, os_strlen(buff));
}






void ICACHE_FLASH_ATTR tplIndex(HttpdConnData *connData, char *token, void **arg){
	char buff[128];
	if (token==NULL) return;

	os_strcpy(buff, "Unknown");
         
		       
	if (os_strcmp(token, "timerCounter")==0) {		 
			os_sprintf(buff, "%d",  timerCounter);	
	}else if (os_strcmp(token, "timerCounterOverAll")==0) {		
			os_sprintf(buff, "%d",  timerCounterOverAll);	
	}else if (os_strcmp(token, "timerInterval")==0) {		
			os_sprintf(buff, "%d",  timerInterval);	
	}else if (os_strcmp(token, "triggerLastTime")==0) {	
	
	/*int seconds = (int) (time / 1000) % 60 ;
int minutes = (int) ((milliseconds / (1000*60)) % 60);
int hours   = (int) ((milliseconds / (1000*60*60)) % 24);
*/
//[2 000 000] 25 23 set led on.

	    uint32 time = system_get_time()/TIMEMILIMIL ;	 		   
        time = time -triggerLastTime;
		os_sprintf(buff, "%d",  time);		
	}else if (os_strcmp(token, "isTimerOn")==0) {	    	 
			if(timerIsOn==1){
    			os_sprintf(buff, "true");		
    		}else{
    		    os_sprintf(buff, "false");		
    		}    
	}
	
		
	
	espconn_sent(connData->conn, (uint8 *)buff, os_strlen(buff));
}










