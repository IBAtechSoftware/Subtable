# Lazy DLL loading mode:
# When this is enabled, client.dll symbols are only loaded when the functions are called the first time
# This leads to faster game load times, but could cause microstutters when resolving symbols for the first time
# On the other hand, the Now DLL loading mode loads the ENTIRE client.dll at once
# This could make the game load slower, but will completly remove microstutters
# Fates Sealed uses NOW dll loading mode
# Other games may choose to use LAZY loading mode
# Its your choice

?Game {
    ?Assets {
        @Textures = [wall.png, menu_background.png]
        @Fonts = [exampleFont.ttf, otherFont.ttf]
    }

    ?PersistentData {
        @SaveFilePrefix = exampleGame

        # Located under the game prefix folder, which cant be modified
        @SaveFileDirectory = saveFiles

        # SubTable, XML, JSON, or CUSTOM
        @SaveFileStorageMode = SubTable
    }

    # Set title of the game(used in the window title)
    @Title = Example Game

    # Copyright of the game(can be grabbed from the game using the Game.Global.GetProperty api call)
    @Copyright = 2023
    
    # What version the 
    @EngineVersion = 1
    @GameVersion = 1
    
    @ClientDLL = client.dll

    # LAZY(Read more at top of file), or NOW
    @ClientDLL_LoadMode = NOW

    
    # Game config used by Fusion engine
    # Fusion (c) IBAtech software 2022-2023
}