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

int load_config(int* x_offset, int* y_offset, int* deadzone) {
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
  read_value(x_offset, buffer, buffer_size, &i);
  if (*x_offset <= INPUT_MIN || *x_offset >= INPUT_MAX) {
    *x_offset = INPUT_CENTER;
  }
  read_value(y_offset, buffer, buffer_size, &i);
  if (*y_offset <= INPUT_MIN || *y_offset >= INPUT_MAX) {
    *y_offset = INPUT_CENTER;
  }
  read_value(deadzone, buffer, buffer_size, &i);
  if (*deadzone < DEADZONE_MIN || *deadzone > DEADZONE_MAX) {
    *deadzone = DEADZONE_MIN;
  }
  return 0;
}
