#include <pspiofilemgr.h>

#define PLUGIN_INI_PATH "ms0:/SEPLUGINS/joycenterfix.ini"
#define PLUGIN_INI_PATH_GO "ef0:/SEPLUGINS/joycenterfix.ini"

void read_offset(int* offset, char* buffer, int buffer_size, int* i) {
  *offset = 0;
  while (*i < buffer_size && (buffer[*i] < '0' || buffer[*i] > '9')) {
    (*i)++;
  }
  while (*i < buffer_size && buffer[*i] >= '0' && buffer[*i] <= '9') {
    *offset = *offset * 10 + (buffer[*i] - '0');
    (*i)++;
  }
}

int load_config(int* x_offset, int* y_offset) {
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
  read_offset(x_offset, buffer, buffer_size, &i);
  read_offset(y_offset, buffer, buffer_size, &i);
  return 0;
}
