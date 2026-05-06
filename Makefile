# Targets
LIB_NAME				:= PotatoEngine
LIB_TARGET				:= lib$(LIB_NAME).a
GAME_TARGET				:= Program

CXX						:= g++
# REMOVE -08 AFTER DEBUGGING
CXXFLAGS				:= -g -Wall -std=c++17 -O0 -MMD -MP
LDLIBS					:= -lncurses

SRCDIR					:= Source
OBJDIR					:= Binaries
THIRDPARTYDIR			:= $(SRCDIR)/ThirdParty
LOGDIR					:= logs/debug.log

# Both Engine and Game can see ThirdParty
ENGINE_INCLUDES			:= -I$(SRCDIR)/Internal/Public -I$(SRCDIR)/Internal/Private -I$(THIRDPARTYDIR)
GAME_INCLUDES			:= -I$(SRCDIR)/Internal/Public -I$(THIRDPARTYDIR)

# Collect Sources from both Internal AND ThirdParty
ENGINE_SOURCES			:= $(shell find $(SRCDIR)/Internal -name '*.cpp')
THIRDPARTY_SOURCES		:= $(shell find $(THIRDPARTYDIR) -name '*.cpp' -o -name '*.cc')

# 4. Map to Objects
ENGINE_OBJECTS			:= $(ENGINE_SOURCES:$(SRCDIR)/Internal/%.cpp=$(OBJDIR)/Internal/%.o)
THIRDPARTY_OBJECTS		:= $(patsubst $(THIRDPARTYDIR)/%.cpp,$(OBJDIR)/ThirdParty/%.o,$(filter %.cpp,$(THIRDPARTY_SOURCES)))
THIRDPARTY_OBJECTS		+= $(patsubst $(THIRDPARTYDIR)/%.cc,$(OBJDIR)/ThirdParty/%.o,$(filter %.cc,$(THIRDPARTY_SOURCES)))

# Combined list for the Library
ALL_LIB_OBJECTS			:= $(ENGINE_OBJECTS) $(THIRDPARTY_OBJECTS)

# Game logic
GAME_SOURCES			:= $(shell find $(SRCDIR)/Program -name '*.cpp')
GAME_OBJECTS			:= $(GAME_SOURCES:$(SRCDIR)/Program/%.cpp=$(OBJDIR)/Program/%.o)

DEPENDENCIES			:= $(ALL_LIB_OBJECTS:.o=.d) $(GAME_OBJECTS:.o=.d)

all: $(GAME_TARGET)

# build engine lib
$(LIB_TARGET): $(ALL_LIB_OBJECTS)
	@echo "> ARCHIVING ENGINE (Internal + ThirdParty)..."
	ar rcs $@ $^

# build game exe  	-Wl,--whole-archive -L. -l$(LIB_NAME) -Wl,--no-whole-archive $(LDLIBS)
$(GAME_TARGET): $(LIB_TARGET) $(GAME_OBJECTS)
	@echo "> LINKING GAME..."
	$(CXX) $(CXXFLAGS) $(GAME_INCLUDES) -o $@ $(GAME_OBJECTS) \
	-Wl,--whole-archive ./$(LIB_TARGET) -Wl,--no-whole-archive $(LDLIBS)

# Rule for Internal objects
$(OBJDIR)/Internal/%.o: $(SRCDIR)/Internal/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(ENGINE_INCLUDES) -c $< -o $@

# Rule for ThirdParty objects
$(OBJDIR)/ThirdParty/%.o: $(THIRDPARTYDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(ENGINE_INCLUDES) -c $< -o $@

$(OBJDIR)/ThirdParty/%.o: $(THIRDPARTYDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(ENGINE_INCLUDES) -c $< -o $@

# game object rule
$(OBJDIR)/Program/%.o: $(SRCDIR)/Program/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GAME_INCLUDES) -c $< -o $@

-include $(DEPENDENCIES)

.PHONY: all