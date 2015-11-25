



INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -IE:/slug_3d/include -IE:/flare_gui/include
LINK_FLAGS=-LE:/allegro-5.1.11-mingw-edgar/lib -LE:/allegro_flare/lib -LE:/flare_gui/lib

# these are the names of the libs you are linking
ALLEGRO_MONOLITH_LIB=allegro_monolith-debug.dll
FGUI_LIB=flare_gui-0.6.6-mingw-4.8.1
ALLEGRO_FLARE_LIB=allegro_flare-0.8.6-mingw-4.8.1


CORE_ITEMS=aabb3d collision_mesh dirty_send_signal door enemy entity entity2 gui_screen hud info_pod item item_factory level main map map_factory pickup_trinket player_character program_master program_master__collision_response program_master__input

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)


bin/slugfest.exe: $(CORE_OBJ_FILES)
	g++ -std=gnu++11 obj/*.o -o bin/slugfest.exe -lopengl32 -l$(FGUI_LIB) -l$(ALLEGRO_FLARE_LIB) -l$(ALLEGRO_MONOLITH_LIB) $(LINK_FLAGS)


$(CORE_OBJ_FILES): obj/%.o : src/%.cpp
	g++ -std=gnu++11 -c -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)







