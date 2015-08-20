#ifndef CGI_H
#define CGI_H

#include "httpd.h"

int cgiTimer(HttpdConnData *connData);
int cgiConfig(HttpdConnData *connData); 

void tplIndex(HttpdConnData *connData, char *token, void **arg);
void tplConfig(HttpdConnData *connData, char *token, void **arg);

void printApconfig();
#endif
