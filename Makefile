SDCC=sdcc-sdcc
SDLD=sdcc-sdld
OBJECTS=blinky.ihx blinky-timer.ihx serial.ihx pwm.ihx
FAC_DEF=factory_defaults.bin
MODEL=stm8s103f3
PROGRAMMER=stlinkv2

.PHONY: all clean flash

all: $(OBJECTS)

clean:
	rm -f *.asm *.cdb *.ihx *.lk *.lst *.map *.rel *.rst *.sym $(FAC_DEF)

%.flash: %.ihx
	stm8flash -c $(PROGRAMMER) -p $(MODEL) -w $<

reset: $(FAC_DEF)
	stm8flash -c $(PROGRAMMER) -p $(MODEL) -s opt -w $(FAC_DEF)

$(FAC_DEF):
	echo "00 00 ff 00 ff 00 ff 00 ff 00 ff" | xxd -r -p > $(FAC_DEF)

%.ihx: %.c
	$(SDCC) -pstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) $<
