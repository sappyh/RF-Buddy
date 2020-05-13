/* -*- c++ -*- */

#define ANNOTATOR_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "annotator_swig_doc.i"

%{
#include "annotator/packet_annotator.h"
%}

%include "annotator/packet_annotator.h"
GR_SWIG_BLOCK_MAGIC2(annotator, packet_annotator);
