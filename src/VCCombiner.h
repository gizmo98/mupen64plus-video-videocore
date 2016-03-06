// mupen64plus-video-videocore/VCCombiner.h
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#ifndef VCCOMBINER_H
#define VCCOMBINER_H

struct VCColorf;
struct VCCombiner;

void VCCombiner_FillCombiner(VCCombiner *combiner, VCColorf *shade);
void VCCombiner_FillCombinerForTextureBlit(VCCombiner *vcCombiner);
void VCCombiner_FillCombinerForRectFill(VCCombiner *vcCombiner, VCColorf *fillColor);

#endif

