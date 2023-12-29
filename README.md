# Spyro: A Hero's Tail Map Browser Mod
Patch to Spyro: A Hero's Tail to add a map browser to the game (GameCube, NTSC).

Made using Composer's [code injection utility](https://github.com/C0mposer/C-Game-Modding-Utility).

Project can be loaded up in the tool manually, and the pre-made [xdelta](https://www.romhacking.net/utilities/598/) patch to the GameCube NTSC ISO can be downloaded from the "releases" section.

# How to use
Controls for the browser menu are mapped to controller port 2. You can assign hotkeys to them as you wish. Here are the controls:

Y-button: Toggle the map browser HUD on/off.<br>
D-pad left/right: Browse maps.<br>
D-pad up/down: Browse startpoints.<br>
A-button: Go to currently selected map and startpoint.<br>
X-button: Select current map and startpoint.<br>
B-button: Enable/disable scanmode. When enabled, use the Z-button on controller 1 to toggle it on and off.<br>
Z-button: Clear all trigger data for the level (reset most of the level, essentially). Reload to make it take effect.<br>
Start-button: Reload to latest checkpoint.<br>
L-trigger/R-trigger: Browse characters (reload checkpoint to actually spawn as them).

# Things to note
* Maps labelled "OLDFILE" will crash when loaded due to being an older format than the engine expects.
* Changing characters sets your current checkpoint to be with that character. If it doesn't work when reloading the checkpoint, try changing to another character and back again.

# Known issues
* Swapping characters doesn't always work due to certain maps being hardcoded to spawn you as a certain character.
* When the game is displaying a timer on-screen, the default font changes and the menu is garbled.
