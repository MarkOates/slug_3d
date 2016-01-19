



# INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -IE:/slug_3d/include -IE:/flare_gui/include
# INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -IE:/slug_3d/include -IE:/flare_gui/include
LINK_FLAGS=-L/Users/markoates/Repos/allegro5/build/lib -L/Users/markoates/Repos/allegro_flare/lib -L/Users/markoates/Repos/flare_gui/lib
INCLUDE_FLAGS=-I/Users/markoates/Repos/allegro5/include -I/Users/markoates/Repos/allegro_flare/include -I/Users/markoates/Repos/slug_3d/include -I/Users/markoates/Repos/flare_gui/include


# ALLEGRO_LIBS=-lallegro_monolith-debug.dll
# ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-mingw-4.8.1
ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro
FGUI_LIB=flare_gui-0.6.6-mingw-4.8.1
ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-clang-7.0.2


# EXE_EXTENSION=
EXE_EXTENSION=.exe




CORE_ITEMS=aabb3d collision_mesh dirty_send_signal door enemy entity entity2 gui_screen hud info_pod item item_factory level main map map_factory pickup_trinket player_character program_master program_master__collision_response program_master__input

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)




bin/slugfest: $(CORE_OBJ_FILES)
	g++ -std=gnu++11 obj/*.o -o bin/slugfest -framework OpenGL -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) $(LINK_FLAGS)


bin/slugfest$(EXE_EXTENSION): $(CORE_OBJ_FILES)
	g++ -std=gnu++11 obj/*.o -o bin/slugfest$(EXE_EXTENSION) -lopengl32 -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) $(ALLEGRO_LIBS) $(LINK_FLAGS)


package: bin/slugfest
	cp ./bin/slugfest /Users/markoates/Desktop/cosmic_protector.app/Contents/MacOS/cosmic_protector
	cp -R ./bin/data/ /Users/markoates/Desktop/cosmic_protector.app/Contents/Resources/data/
	cp -R ./bin/data/ /Users/markoates/Desktop/cosmic_protector.app/Contents/MacOS/data/



$(CORE_OBJ_FILES): obj/%.o : src/%.cpp
	g++ -std=gnu++11 -c -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)







