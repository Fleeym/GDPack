# GDPack - The CLI Geometry Dash texture pack manager

A small program I made for myself that manages Geometry Dash texture packs. As it stands this will probably be compatible with 2.2 with little or no updates, because it uses the file system. It should also work on any OS, I tried to only use std.
This is my first project so if the code sucks, you know why. If you want to report a bug, or contact me, here's my discord: ```Flame#7148```

## Commands

- ```gdpack help``` to show help dialogue. This can also be used as an argument for the other commands.
- ```gdpack setup``` to repeat the first-run setup (used if you want to change the Geometry Dash path).
- ```gdpack list``` to list all available packs.
- ```gdpack revert``` to revert to the vanilla textures.
- ```gdpack set``` to set a pack as active.

## First time setup

When you first run GDPack, the first time setup will prompt you for your Geometry Dash folder. Just paste the **root** folder of Geometry Dash. A few examples are:

```text
C:\Program Files (x86)\Steam\steamapps\common\Geometry Dash
D:\SteamLibrary\steamapps\common\Geometry Dash
```

This heavily depends on where you installed GD. If you're not sure where it is installed, right click on Geometry Dash in Steam, hover over Manage, and click Browse Local Files. Just copy the path at the top and paste it in the terminal.

## Pack storage

GDPack creates it's own folder in the Geometry Dash folder to store packs.

Packs also have a specific folder structure. GDPack won't work if they are not setup this way.

```text
*Pack Folder*
|
--Resources
  |
  -- *Pack files go here*
-- manifest.json
```

**Don't worry if you don't have a manifest.json, gdpack will generate one for you when running it with any command!**

So, an example folder structure would be:

```text
Geometry Dash
|
   gdpack
   |
   -- config.json
   -- Pack 1
      |
      -- Resources
         |
         -- *pack 1 files*
      -- manifest.json
      -- cache.json
   -- Pack 2
      |
      -- Resources
         |
         -- *pack 2 files*
      -- manifest.json
      -- cache.json

And so on...
```

## Vanilla resources

GDPack stores the vanilla files it replaces in a "vanilla" pack. Do not touch this folder, stuff will break.

**IMPORTANT**: If your Geometry Dash Resources folder has been edited before running GDPack for the first time, the state it is in will be considered as "vanilla". GDPack won't magically make the vanilla files appear when running "gdpack revert" if your resources were modified. If you want this behaviour, reinstall Geometry Dash, and run GDPack.

## The manifest system

GDPack uses a manifest.json for every pack. If your pack doesn't have one, GDPack will create a template for you. The manifest.json has the following structure:

```json
{
  "author": "",
  "description": "",
  "gdVersion": "",
  "name": "",
  "path": "",
  "version": "",
}
```

GDPack also uses the manifest system to cache files that it detected moving to the Resources folder of the game. This is so that it can reduce pack switching times when setting small packs with a large vanilla cache. This cache is stored in a separate file, cache.json.

## Building from source

At the moment you can only build this from source. This is how I do it.

- Clone this repository (either by using the command line or by clicking the **Code** button at the top of the page)
- Extract the archive and open a terminal/cmd in the extracted folder.
- ```sh
  mkdir build
  cmake -B build -D CMAKE_BUILD_TYPE=Release ..
  cmake --build build
  ```
After the build is done, copy gdpack(.exe) from the "build" folder wherever you want.