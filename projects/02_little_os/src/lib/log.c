#include "./log.h"

PUBLIC void log_msg(unsigned int device, unsigned int type, const char *msg) {
  switch (type) {
  case LOG_DEBUG:
    printf(device, "[DEBUG] : ");
    break;
  case LOG_INFO:
    printf(device, "[INFO] : ");
    break;
  case LOG_ERROR:
    printf(device, "[ERROR] : ");
    break;
  default:
    break;
  }
  printf(device, msg);
  putchar(device, '\n');
}
