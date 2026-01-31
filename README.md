# PSP Plugin to Fix Misaligned Joysticks

Lightweight PSP plugin that fixes joystick center misalignment, resolving most joystick drift issues.

## Quick Setup Guide

1. Copy the latest `joycenterfix.prx` file from the [releases page](https://github.com/vladimir-cucu/joycenterfix/releases) to the `SEPLUGINS` folder on your memory stick.

2. Create a `joycenterfix.ini` text file in the same folder with exactly 2 numbers (in the interval `[0..255]`) on 2 consecutive separate lines:
   1. First line: x-axis missaligned joystick center
   2. Second line: y-axis missaligned joystick center

   For example, a valid `joycenterfix.ini` file would look like this:

```
140
134
```

3. Add the following activation entry to `VSH.txt`, `GAME.txt`, and/or `POPS.txt`:
   1. PSP 1000, 2000, 3000, and STREET: `ms0:/SEPLUGINS/joycenterfix.prx 1`
   2. PSP GO: `ef0:/SEPLUGINS/joycenterfix.prx 1`

**Note:** You can use [Key[s]Tester by Yoti](https://github.com/PSP-Archive/keysTester) to find the coordinates of the missaligned joystick center.

## Credits

Inspired by [JoySens plugin](https://github.com/albe/joysens). I recommend using JoySens for more fine-tuning options.
