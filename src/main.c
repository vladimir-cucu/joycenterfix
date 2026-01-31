#include <pspctrl.h>
#include <pspkernel.h>

#include "config.h"
#include "constants.h"
#include "hook.h"

PSP_MODULE_INFO(PLUGIN_NAME, PSP_MODULE_KERNEL, 1, 0);

int x_offset = INPUT_CENTER;
int y_offset = INPUT_CENTER;
int deadzone = DEADZONE_MIN;

int (*g_ctrl_read_positive)(SceCtrlData*, int count, int type);
int (*g_ctrl_peek_positive)(SceCtrlData*, int count, int type);
int (*g_ctrl_read_negative)(SceCtrlData*, int count, int type);
int (*g_ctrl_peek_negative)(SceCtrlData*, int count, int type);

int adjust_stick_value(int value, int offset, int deadzone) {
  int threshold_left = offset - deadzone;
  int threshold_right = offset + deadzone;
  if (threshold_left <= INPUT_MIN || threshold_right >= INPUT_MAX ||
      (value >= threshold_left && value <= threshold_right)) {
    return INPUT_CENTER;
  }
  if (value < offset) {
    return INPUT_CENTER - ((INPUT_CENTER - INPUT_MIN) * (threshold_left - value)) / (threshold_left - INPUT_MIN);
  } else {
    return INPUT_CENTER + ((INPUT_MAX - INPUT_CENTER) * (value - threshold_right)) / (INPUT_MAX - threshold_right);
  }
}

void adjust_values(SceCtrlData* pad_data, int count, int neg) {
  for (int i = 0; i < count; i++) {
    int buttons = pad_data[i].Buttons;
    if (neg) {
      buttons = ~buttons;
    }

    if ((buttons & PSP_CTRL_HOLD) == PSP_CTRL_HOLD) {
      pad_data[i].Lx = INPUT_CENTER;
      pad_data[i].Ly = INPUT_CENTER;
      continue;
    }

    int x = adjust_stick_value((int)pad_data[i].Lx, x_offset, deadzone);
    pad_data[i].Lx = (unsigned char)x;
    int y = adjust_stick_value((int)pad_data[i].Ly, y_offset, deadzone);
    pad_data[i].Ly = (unsigned char)y;
  }
}

#define MAKE_HOOK(hook_name, func_ptr)                        \
  int hook_name(SceCtrlData* pad_data, int count, int type) { \
    int ret = func_ptr(pad_data, count, type);                \
    if (ret <= 0) return ret;                                 \
    adjust_values(pad_data, ret, type & 1);                   \
    return ret;                                               \
  }

MAKE_HOOK(ctrl_read_positive_hook, g_ctrl_read_positive)
MAKE_HOOK(ctrl_peek_positive_hook, g_ctrl_peek_positive)
MAKE_HOOK(ctrl_read_negative_hook, g_ctrl_read_negative)
MAKE_HOOK(ctrl_peek_negative_hook, g_ctrl_peek_negative)

int main_thread(SceSize args, void* argp) {
  sceKernelDelayThread(1000000);
  load_config(&x_offset, &y_offset, &deadzone);

  hook_function((unsigned int*)sceCtrlReadBufferPositive, ctrl_read_positive_hook,
                (unsigned int*)&g_ctrl_read_positive);
  hook_function((unsigned int*)sceCtrlPeekBufferPositive, ctrl_peek_positive_hook,
                (unsigned int*)&g_ctrl_peek_positive);
  hook_function((unsigned int*)sceCtrlReadBufferNegative, ctrl_read_negative_hook,
                (unsigned int*)&g_ctrl_read_negative);
  hook_function((unsigned int*)sceCtrlPeekBufferNegative, ctrl_peek_negative_hook,
                (unsigned int*)&g_ctrl_peek_negative);

  sceKernelDcacheWritebackInvalidateAll();
  sceKernelIcacheInvalidateAll();
  sceKernelExitDeleteThread(0);
  return 0;
}

int module_start(SceSize args, void* argp) {
  int thid = sceKernelCreateThread(PLUGIN_NAME, main_thread, 0x77, 0x1000, 0, NULL);
  if (thid >= 0) {
    sceKernelStartThread(thid, args, argp);
  }
  return 0;
}

int module_stop(SceSize args, void* argp) {
  return 0;
}
