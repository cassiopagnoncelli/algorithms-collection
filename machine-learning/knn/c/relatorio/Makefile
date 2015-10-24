LU_MASTERS = relatorio
#---
.PHONY: clean default

default: dvi

clean ::
	@$(RM) -v $(addsuffix .dvi, $(LU_MASTERS)) \
	          $(addsuffix .aux, $(LU_MASTERS)) \
	          $(addsuffix .blg, $(LU_MASTERS)) \
	          $(addsuffix .out, $(LU_MASTERS)) \
	          $(addsuffix .toc, $(LU_MASTERS)) \
	          $(addsuffix .dvi_FAILED, $(LU_MASTERS)) \
	          $(addsuffix .aux.orig, $(LU_MASTERS))
#---
include LaTeX.mk
