# Generated Makefile for ${PROJECT_NAME}
.PHONY: all synth run clean

LIBRARY_PATH := /vol/ece303/genus_tutorial
LIB_FILE := $(LIBRARY_PATH)/NangateOpenCellLibrary_typical.lib
LEF_FILE := $(LIBRARY_PATH)/NangateOpenCellLibrary.lef

SYNTH ?= 0

all: run

synth: Synthesis/synthesis.tcl
	cd Synthesis && \
	csh -c 'source $(LIBRARY_PATH)/cadence.env && \
	genus -f synthesis.tcl' && \
	sed -i '1i\`timescale 1ns/10ps' ${PROJECT_NAME}_syn.v

Synthesis/synthesis.tcl: | Synthesis
	@echo "read_hdl ../${PROJECT_NAME}.v" > $@
	@echo "set_db library $(LIB_FILE)" >> $@
	@echo "set_db lef_library $(LEF_FILE)" >> $@
	@echo "elaborate" >> $@
	@echo "current_design ${PROJECT_NAME}" >> $@
	@echo "read_sdc ../${PROJECT_NAME}.sdc" >> $@
	@echo "syn_generic" >> $@
	@echo "syn_map" >> $@
	@echo "syn_opt" >> $@
	@echo "report_timing > timing.rpt" >> $@
	@echo "report_area > area.rpt" >> $@
	@echo "write_hdl > ${PROJECT_NAME}_syn.v" >> $@
	@echo "quit" >> $@

Synthesis:
	mkdir -p $@

run:
	@if [ "$(SYNTH)" = "1" ]; then \
		csh -c 'source $(LIBRARY_PATH)/cadence.env && \
		xrun -64bit -gui -access r -xmelab_args "-warnmax 0 -maxdelays" \
			Synthesis/${PROJECT_NAME}_syn.v ${PROJECT_NAME}_tb.v $(LIBRARY_PATH)/NangateOpenCellLibrary.v'; \
	else \
		csh -c 'source $(LIBRARY_PATH)/cadence.env && \
		xrun -64bit -gui -access r ${PROJECT_NAME}.v ${PROJECT_NAME}_tb.v'; \
	fi

clean:
	rm -rf Synthesis
