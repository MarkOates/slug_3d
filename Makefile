



INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -IE:/slug_3d/include -IE:/flare_gui/include
LINK_FLAGS=-LE:/allegro-5.1.11-mingw-edgar/lib -LE:/allegro_flare/lib -LE:/flare_gui/lib

# these are the names of the libs you are linking
ALLEGRO_MONOLITH_LIB=allegro_monolith-debug.dll
FGUI_LIB=flare_gui-0.6.6-mingw-4.8.1
ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-mingw-4.8.1



bin/slugfest.exe:
	g++ -std=gnu++11 src/*.cpp -o bin/slugfest.exe -IE:/allegro_flare/include $(INCLUDE_FLAGS)  -lopengl32 -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) $(LINK_FLAGS)






