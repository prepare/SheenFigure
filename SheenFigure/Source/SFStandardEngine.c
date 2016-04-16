/*
* Copyright (C) 2016 Muhammad Tayyab Akram
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <SFConfig.h>
#include <SFFeatureTag.h>
#include <SFScriptTag.h>
#include <SFTypes.h>

#include <stddef.h>

#include "SFAssert.h"
#include "SFShapingEngine.h"
#include "SFShapingKnowledge.h"
#include "SFTextProcessor.h"
#include "SFStandardEngine.h"

static SFScriptKnowledgeRef _SFStandardKnowledgeSeekScript(const void *object, SFScriptTag scriptTag);
static void _SFStandardEngineProcessAlbum(const void *object, SFAlbumRef album, SFDirection direction);

enum {
    _SFStandardFeatureMaskNone = 0 << 0
};

static SFFeatureInfo _SFStandardFeatureInfoArray[] = {
    /* Language based forms. */
    { SFFeatureTagCCMP, _SFStandardFeatureMaskNone },
    /* Typographical forms */
    { SFFeatureTagLIGA, _SFStandardFeatureMaskNone },
    { SFFeatureTagCLIG, _SFStandardFeatureMaskNone },
    /* Positioning features. */
    { SFFeatureTagDIST, _SFStandardFeatureMaskNone },
    { SFFeatureTagKERN, _SFStandardFeatureMaskNone },
    { SFFeatureTagMARK, _SFStandardFeatureMaskNone },
    { SFFeatureTagMKMK, _SFStandardFeatureMaskNone }
};
#define _SFStandardFeatureInfoCount (sizeof(_SFStandardFeatureInfoArray) / sizeof(SFFeatureInfo))

static SFScriptKnowledge _SFStandardScriptKnowledge = {
    SFDirectionLTR,
    { _SFStandardFeatureInfoArray, _SFStandardFeatureInfoCount },
    { NULL, 0 }
};

SFShapingKnowledge SFStandardKnowledgeInstance = {
    &_SFStandardKnowledgeSeekScript
};

static SFScriptKnowledgeRef _SFStandardKnowledgeSeekScript(const void *object, SFScriptTag scriptTag)
{
    switch (scriptTag) {
    case SFScriptTagARMN:
    case SFScriptTagCYRL:
    case SFScriptTagGEOR:
    case SFScriptTagGREK:
    case SFScriptTagLATN:
    case SFScriptTagOGAM:
    case SFScriptTagRUNR:
        return &_SFStandardScriptKnowledge;
    }

    return NULL;
}

static SFShapingEngine _SFStandardEngineBase = {
    &_SFStandardEngineProcessAlbum
};

SF_INTERNAL void SFStandardEngineInitialize(SFStandardEngineRef standardEngine, SFPatternRef pattern)
{
    standardEngine->_base = _SFStandardEngineBase;
    standardEngine->_pattern = pattern;
}

static void _SFStandardEngineProcessAlbum(const void *object, SFAlbumRef album, SFDirection direction)
{
    SFStandardEngineRef standardEngine = (SFStandardEngineRef)object;
    SFTextProcessor processor;

    SFTextProcessorInitialize(&processor, standardEngine->_pattern, album, direction);
    SFTextProcessorDiscoverGlyphs(&processor);
    SFTextProcessorSubstituteGlyphs(&processor);
    SFTextProcessorPositionGlyphs(&processor);
    SFTextProcessorWrapUp(&processor);
}
