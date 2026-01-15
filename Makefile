# =============================================================================
# Planet Donut Simulation - Makefile
# =============================================================================
# Authors: Daniel Abraham Elmaleh, Imane Jennane
# Date: May 2021
# Institution: EPFL
# =============================================================================

OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./include
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`

SRCDIR = src
INCDIR = include

OFILES = projet.o geomod.o message.o gisement.o base.o robot.o simulation.o gui.o graphic.o

# =============================================================================
# Build Targets
# =============================================================================

all: $(OUT)

projet.o: $(SRCDIR)/projet.cc $(INCDIR)/geomod.h $(INCDIR)/simulation.h $(INCDIR)/gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

geomod.o: $(SRCDIR)/geomod.cc $(INCDIR)/geomod.h $(INCDIR)/graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

message.o: $(SRCDIR)/message.cc $(INCDIR)/message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gisement.o: $(SRCDIR)/gisement.cc $(INCDIR)/gisement.h $(INCDIR)/geomod.h $(INCDIR)/constantes.h $(INCDIR)/message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

base.o: $(SRCDIR)/base.cc $(INCDIR)/base.h $(INCDIR)/geomod.h $(INCDIR)/gisement.h $(INCDIR)/constantes.h $(INCDIR)/message.h $(INCDIR)/robot.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

robot.o: $(SRCDIR)/robot.cc $(INCDIR)/robot.h $(INCDIR)/geomod.h $(INCDIR)/constantes.h $(INCDIR)/gisement.h $(INCDIR)/message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

simulation.o: $(SRCDIR)/simulation.cc $(INCDIR)/simulation.h $(INCDIR)/geomod.h $(INCDIR)/message.h $(INCDIR)/constantes.h $(INCDIR)/base.h $(INCDIR)/gisement.h $(INCDIR)/robot.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gui.o: $(SRCDIR)/gui.cc $(INCDIR)/gui.h $(INCDIR)/constantes.h $(INCDIR)/graphic.h $(INCDIR)/graphic_gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

graphic.o: $(SRCDIR)/graphic.cc $(INCDIR)/graphic.h $(INCDIR)/graphic_gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

# =============================================================================
# Utility Targets
# =============================================================================

clean:
	@echo "Cleaning compilation files"
	@rm -f *.o $(OUT)

.PHONY: all clean
