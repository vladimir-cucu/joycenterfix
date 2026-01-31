# PSP Plugin to Fix Misaligned Joysticks

Lightweight PSP plugin that fixes joystick center misalignment and deadzone, addressing most joystick drift issues.

## Quick Setup Guide

1. Copy the latest `joycenterfix.prx` file from the [releases page](https://github.com/vladimir-cucu/joycenterfix/releases) to the `SEPLUGINS` folder.

2. Create a text file named `joycenterfix.ini` in the `SEPLUGINS` folder with exactly 3 integer numbers, one per line:
   1. First line: x-axis center in the interval [1..254] (default: 128)
   2. Second line: y-axis center in the interval [1..254] (default: 128)
   3. Third line: deadzone in the interval [0..64] (default: 0)
   
   Numbers outside these ranges will be replaced by the default values. For example, a valid `joycenterfix.ini` file would look like this:

```
140
134
20
```

3. Add the following line to `VSH.txt`, `GAME.txt`, and/or `POPS.txt`:
   1. PSP 1000, 2000, 3000, and STREET: `ms0:/SEPLUGINS/joycenterfix.prx 1`
   2. PSP GO: `ef0:/SEPLUGINS/joycenterfix.prx 1`

**Note:** You can use [Key[s]Tester by Yoti](https://github.com/PSP-Archive/keysTester) to find the coordinates of the joystick center.

## Credits

Inspired by [JoySens plugin](https://github.com/albe/joysens). I recommend using JoySens for more fine-tuning options.
