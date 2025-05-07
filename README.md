# FFXRando
Randomizer for many elements of the game Final Fantasy 10

# How to use
1. Extract your Final Fantasy X game files from FFX_Data.vbf utilizing the VBF Browser application (can be found on Nexus Mods, under Final Fantasy 12 mods)
2. Place extracted files into the input folder. Currently the only directory that is needed is ffx_ps2.
3. Run the executeable, chose your options and hit Randomize.
4. import the files back into the game using the VBF Browser **OR**
5. If utilizing the the FFX/X2 External File Loader mod, you can place the ffx_ps2 directory from the "output" folder into the `/data/mods/` folder in your games directory. **OR**
6. If utilizing the Fahrenheit Mod Loarder, you can place the FFXRando directory (loacted in the "output" folder) into the `/fahrenheit/modules` folder. Dont forget to edit your loadorder file to include "FFXRando"!
7. Play and have fun... hopefully.

# Currently Supports
1. Field Item Randomization
2. Enemy Reward Randomization, including Gil, AP, Steal, Drop, Bribe, and Equipment.
3. Shop Randomization
4. Equipment Randomization
5. Player Stat Randomization
6. Aeon Stat Randomization
7. Starting overdrive mode Randomization
8. Enemy Elemental Affinity Randomization
9. Sphere Grid Randomization

# Planned Future Additons
1. Random Encounters

# Maybe Future Additions
1. Enemy Ability randomization??

# How to Build
**Currently only supports MSVC compilation**
1. Setup wxWidgets following the directions on their website.
2. Open FFXRando.sln in Visual Studio, or run msbuild on the .sln
3. If running from the command line, you may need to edit the project settings (vcxproj) to point to your wxWidgets directory.
4. If running in Visual Studio, make sure you setup your wxwidgets.props file in the property manager.
5. Compile the application and enjoy!

____
**Big shoutout to the wonderful folks in the [Cid's Salvage Ship](https://discord.gg/vEu5wkjXGv) discord for answering all my questions and giving suggestions while i was making this.**

**This would not have been possible without the data mapping already done by Karifean and their [Data Parser](https://github.com/Karifean/FFXDataParser) project , as well as the [Fahrenheit](https://github.com/peppy-enterprises/fahrenheit) team**

## External Libraries

This program uses the following external libraries.

json (https://github.com/nlohmann/json)

Copyright © 2013-2025 Niels Lohmann
MIT License (see LICENSE for more information).

wxWidgets (https://wxwidgets.org/)

Copyright (c) 1998-2005 Julian Smart, Robert Roebling et al
[wxWindows Library Licence](https://github.com/wxWidgets/wxWidgets/blob/master/docs/licence.txt)
