# Tein tän makefilen, koska en jaksa alkaa säätään Linuxille Arduino Ideä
# tai käyttää Arduino CLI:n compile komentoja joka kerta.
# Windowsilla ei tarvitse tästä tiedostosta välittää siis.
# - Nico

# ?=: Overwrtiable variables through cli
FQBN   ?= arduino:avr:uno
PORT   ?= /dev/ttyACM0
SKETCH ?= .
BAUD   ?= 9600
BUILD  ?= build

.PHONY: all compile upload monitor boards clean

all: upload

compile:
	arduino-cli compile --fqbn $(FQBN) --build-path $(BUILD) $(SKETCH)

upload: compile
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) --input-dir $(BUILD) $(SKETCH)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(BAUD)

boards:
	arduino-cli board list

clean:
	rm -rf $(BUILD)