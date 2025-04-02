# FFXRando
Randomizer for many elements of the game Final Fantasy 10

# How to use
1. Extract your Final Fantasy X game files from FFX_Data.vbf utilizing the VBF Browser application (can be found on Nexus Mods, under Final Fantasy 12 mods)
2. Place extracted files into the input folder. Currently the only directory that is needed is ffx_ps2.
3. Run the executeable.
4. After randomizing, you can import the files back into the game using the VBF Browser, or if utilizing the FFX/X2 External File Loader mod, you can place the ffx_ps2 directory into the /data/mods/ folder in your games directory.
5. Play and have fun... hopefully.

# Currently Supports
1. Field Item randomization
2. Enemy Reward randomization, including Gil, AP, Steal, Drop, Bribe, and Equipment.
3. Shop Randomization
4. Equipment Randomization
5. Player Stat randomization
6. Aeon Stat randomization
7. Starting overdrive mode randomization
8. Enemy Elemental Affinity randomization

# Planned Future Additons
1. Random Encounters
2. Sphere Grid

# Maybe Future Additions
1. Enemy Ability randomization??

# How to Build
**Currently only supports MSVC compilation**
1. Setup wxWidgets following the directions on their website.
2. Open FFXRando.sln in Visual Studio, or run msbuild on the .sln
3. If running from the command line, you may need to edit the project settings (vcxproj) to point to your wxWidgets directory.
4. If running in Visual Studio, make sure you setup your wxwidgets.props file in the property manager.
5. Compile the application and enjoy!

**Big shoutout to the wonderful folks in the [Cid's Salvage Ship](https://discord.gg/AGx2grw9nD) discord for answering all my questions and giving suggestions while i was making this.**
**This would not have been possible without the data mapping already done by Karifean and their [Data Parser](https://github.com/Karifean/FFXDataParser) project , as well as the [Ferenheight](https://github.com/peppy-enterprises/fahrenheit) team**
