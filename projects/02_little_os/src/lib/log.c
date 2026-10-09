#include "./log.h"
#include "stdio.h"

PUBLIC void log_msg(unsigned int device, unsigned int type, const char *msg) {
  switch (type) {
  case LOG_DEBUG:
    set_color(device, COLOR_DEBUG);
    printf(device, "[DEBUG] : ");
    break;
  case LOG_INFO:
    set_color(device, COLOR_INFO);
    printf(device, "[INFO] : ");
    break;
  case LOG_ERROR:
    set_color(device, COLOR_ERROR);
    printf(device, "[ERROR] : ");
    break;
  default:
    break;
  }
  printf(device, msg);
  set_color(device, COLOR_RESET);
  putchar(device, '\n');
}
