# GDPack - A CLI Geometry Dash texture pack manager!
A small program I made for myself that manages Geometry Dash texture packs. As it stands this will probably be compatible with 2.2 with little or no updates, because it uses the file system. It should also work on any OS, I tried to only use std.
This is my first project so if the code sucks, you know why. If you want to report a bug, or contact me, here's my discord: ```Flame#7148```

# Usage
## Commands
 - ```gdpack help``` to show help dialogue. This can also be used as an argument for the other commands.
 - ```gdpack setup``` to repeat the first-run setup (used if you want to change the Geometry Dash path).
 - ```gdpack list``` to list all available packs.
 - ```gdpack revert``` to revert to the vanilla textures.
 - ```gdpack set``` to set a pack as active.
## First time setup
When you first run GDPack, the first time setup will prompt you for your Geometry Dash folder. Just paste the **root** folder of Geometry Dash. A few examples are: 
```
C:\Program Files (x86)\Steam\steamapps\common\Geometry Dash
D:\SteamLibrary\steamapps\common\Geometry Dash
```

This heavily depends on where you installed GD. If you're not sure where it is installed, right click on Geometry Dash in Steam, hover over Manage, and click Browse Local Files. Just copy the path at the top and paste it in the terminal.

## Pack storage
GDPack checks the folder it's in for the packs. It is advised to place GDPack in an empty folder. Your folder structure should look like this: 

```
GDPack
|
-- GDPack.exe
-- config.json (after it is generated by the initial setup)
-- *your packs*
```

Packs also have a specific folder structure. GDPack won't work if they are not setup this way.
```
[Pack_Folder]
|
--Resources
  |
  -- *Pack files go here*
```

So, an example folder structure would be:
```
GDPack
|
-- GDPack.exe
-- config.json
-- Pack 1
   |
   -- Resources
      |
      -- *pack 1 files*
-- Pack 2
   |
   -- Resources
      |
      -- *pack 2 files*

And so on...
```

## Vanilla resources
GDPack stores the vanilla files it replaces in a "vanilla" pack. Do not touch this folder, stuff will break.

**IMPORTANT**: If your Geometry Dash Resources folder has been edited before running GDPack for the first time, the state it is in will be considered as "vanilla". GDPack won't magically make the vanilla files appear when running "gdpack revert" if your resources were modified. If you want this behaviour, reinstall Geometry Dash, and run GDPack.

I will try to create a system that saves your edited resources when it detects that they are modified so that you can reinstall the game. Expect this soon™️.

# Building from source
At the moment you can only build this from source. This is how I do it.

- Clone this repository (either by using the command line or by clicking the **Code** button at the top of the page)
- Install CMake Tools for VSCode
- Open gdpack-master in VSCode
- F1 -> CMake: Configure
- F1 -> CMake: Select Variant -> Release
- Build it using the button in the bottom bar or by pressing F7

You can do this with commands, too, but you're on your own there.