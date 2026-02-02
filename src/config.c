#include <pspiofilemgr.h>

#include "constants.h"

void read_value(int* value, char* buffer, int buffer_size, int* i) {
  *value = 0;
  while (*i < buffer_size && (buffer[*i] < '0' || buffer[*i] > '9')) {
    (*i)++;
  }
  while (*i < buffer_size && buffer[*i] >= '0' && buffer[*i] <= '9') {
    *value = *value * 10 + (buffer[*i] - '0');
    (*i)++;
  }
}

int load_config(int* x_center, int* y_center, int* x_deadzone, int* y_deadzone) {
  SceUID fd = sceIoOpen(PLUGIN_INI_PATH, PSP_O_RDONLY, 0);
  if (fd < 0) {
    fd = sceIoOpen(PLUGIN_INI_PATH_GO, PSP_O_RDONLY, 0);
  }
  if (fd < 0) {
    return -1;
  }

  char buffer[64];
  int buffer_size = sceIoRead(fd, buffer, sizeof(buffer) - 1);
  sceIoClose(fd);

  if (buffer_size <= 0) {
    return -1;
  }
  buffer[buffer_size] = '\0';

  int i = 0;
  read_value(x_center, buffer, buffer_size, &i);
  if (*x_center <= INPUT_MIN || *x_center >= INPUT_MAX) {
    *x_center = INPUT_CENTER;
  }
  read_value(y_center, buffer, buffer_size, &i);
  if (*y_center <= INPUT_MIN || *y_center >= INPUT_MAX) {
    *y_center = INPUT_CENTER;
  }
  read_value(x_deadzone, buffer, buffer_size, &i);
  if (*x_deadzone < DEADZONE_MIN || *x_deadzone > DEADZONE_MAX) {
    *x_deadzone = DEADZONE_MIN;
  }
  read_value(y_deadzone, buffer, buffer_size, &i);
  if (*y_deadzone < DEADZONE_MIN || *y_deadzone > DEADZONE_MAX) {
    *y_deadzone = DEADZONE_MIN;
  }
  return 0;
}
