# FFXRando
Randomizer for many elements of the game Final Fantasy 10

# THIS PROJECT IS STILL IN THE VERY EARLY STAGES OF DEVELOPMENT.
# THERE WILL BE BUGS.

Currently does not even have an interface, just a simple command line that reads, randomizes, then outputs files. 

# How to use
1. Extract your Final Fantasy X game files from FFX_Data.vbf utilizing the VBF Browser application (can be found on Nexus Mods, under Final Fantasy 12 mods)
2. Place extracted files into the input folder. Currently the only directory that is needed is ffx_ps2.
3. Run the executeable.
4. After randomizing, you can import the files back into the game using the VBF Browser, or if utilizing the FFX/X2 External File Loader mod, you can place the ffx_ps2 directory into the /data/mods/ folder in your games directory.
5. Play and have fun... hopefully.

# Currently Supports
1. Field Item randomization, excluding Key Items.
2. Enemy Reward randomization, including Gil, AP, Steal, Drop, Bribe, and Equipment.
3. Shop Randomization. Randomizes both the number of items in every shop, but also what items they are.
4. Equipment Randomization. Every piece of equipment in the game, except Celestial Weapons, and Brotherhood will have random abilities.

# Planned Future Additons
1. Stat Randomization (Player, Enemy, Aeon)
2. Enemy Weaknesses/Resists

# Maybe Future Additions
1. Sphere Grid??
2. Random Encounters??


# How to Build
**Currently only supports MSVC compilation**
1. Setup wxWidgets following the directions on their website.
2. Open FFXRando.sln in Visual Studio, or run msbuild on the .sln
3. If running from the command line, you may need to edit the project settings (vcxproj) to point to your wxWidgets directory.
4. If running in Visual Studio, make sure you setup your wxwidgets.props file in the property manager.
5. Compile the application and enjoy!
