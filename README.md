# PSP Plugin to Fix Misaligned Joysticks

Lightweight PSP plugin that fixes joystick center misalignment and deadzone, addressing most joystick drift issues.

## Quick Setup Guide

1. Copy the latest version of the `joycenterfix.prx` file from the [releases page](https://github.com/vladimir-cucu/joycenterfix/releases) to the `SEPLUGINS` folder.

2. Create a text file named `joycenterfix.ini` in the `SEPLUGINS` folder with exactly 4 integer numbers, two per line separated by space:
   1. First line: x-axis center and y-axis center, both in the interval [1..254] (default: 128)
   2. Second line: x-axis deadzone and y-axis deadzone, both in the interval [0..64] (default: 0)

   Numbers outside those ranges will be replaced by the default values. If the file doesn't exist, all default values will be used. For example, a valid `joycenterfix.ini` file would look like this:

```
140 134
20 0
```

3. Add the following line to `VSH.txt`, `GAME.txt`, and/or `POPS.txt`:
   1. PSP 1000, 2000, 3000, and STREET: `ms0:/SEPLUGINS/joycenterfix.prx 1`
   2. PSP GO: `ef0:/SEPLUGINS/joycenterfix.prx 1`

**Note:** You can use [Key[s]Tester by Yoti](https://github.com/PSP-Archive/keysTester) to find the coordinates of the joystick center.

## Credits

Inspired by [JoySens plugin](https://github.com/albe/joysens). I recommend using JoySens plugin if you want more fine-tuning options.
