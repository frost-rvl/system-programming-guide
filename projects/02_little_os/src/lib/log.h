#ifndef LOG_H
#define LOG_H

enum { LOG_DEBUG, LOG_INFO, LOG_ERROR };

#include "./stdio.h"

/* log_msg
 * Print log messages into a specific device
 *
 * device : the target device
 * type : the log type
 * msg : the messages to print
 * */
void log_msg(unsigned int device, unsigned int type, const char *msg);

#endif // LOG_H
