#include <stdlib.h>
#include <string.h>
#include "Configuration.h"
#define PORT 23333


Configuration* createConfiguration()
{
    Configuration* conf = malloc(sizeof(Configuration));
    conf->address=0;
    conf->port=PORT;
    conf->queue=5;
    conf->socket=-1;
    conf->ip=NULL;
    return conf;
}
void deleteConfiguration(Configuration* conf)
{
    if(NULL == conf)
        return;
    free(conf);
}
