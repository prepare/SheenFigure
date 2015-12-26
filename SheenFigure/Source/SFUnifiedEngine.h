/*
 * Copyright (C) 2015 Muhammad Tayyab Akram
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

#ifndef SF_UNIFIED_ENGINE_INTERNAL_H
#define SF_UNIFIED_ENGINE_INTERNAL_H

#include <SFConfig.h>
#include <SFScriptTag.h>

#include "SFArabicEngine.h"
#include "SFShapingEngine.h"
#include "SFStandardEngine.h"

typedef union _SFUnifiedEngine {
    SFShapingEngine _base;
    SFArabicEngine _arabicEngine;
    SFStandardEngine _standardEngine;
} SFUnifiedEngine, *SFUnifiedEngineRef;

extern SFShapingKnowledge SFUnifiedKnowledgeInstance;

SF_INTERNAL void SFUnifiedEngineInitialize(SFUnifiedEngineRef unifiedEngine, SFScriptTag scriptTag);

#endif