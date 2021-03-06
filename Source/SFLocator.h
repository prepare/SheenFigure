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

#ifndef _SF_INTERNAL_LOCATOR_H
#define _SF_INTERNAL_LOCATOR_H

#include <SFConfig.h>

#include "SFAlbum.h"
#include "SFCommon.h"
#include "SFData.h"

typedef struct _SFLocator {
    SFAlbumRef _album;
    SFData _markAttachClassDef;
    SFData _markGlyphSetsDef;
    SFData _markFilteringCoverage;
    SFUInteger _version;
    SFUInteger _startIndex;
    SFUInteger _limitIndex;
    SFUInteger _stateIndex;
    SFUInteger index;
    SFGlyphMask _ignoreMask;
    SFLookupFlag lookupFlag;
} SFLocator, *SFLocatorRef;

SF_INTERNAL void SFLocatorInitialize(SFLocatorRef locator, SFAlbumRef album, SFData gdef);

SF_INTERNAL void SFLocatorSetFeatureMask(SFLocatorRef locator, SFUInt16 featureMask);

/**
 * Sets the lookup flag describing the criterion for ignoring glyphs.
 */
SF_INTERNAL void SFLocatorSetLookupFlag(SFLocatorRef locator, SFLookupFlag lookupFlag);

/**
 * Sets the mark filtering set to use, if needed.
 */
SF_INTERNAL void SFLocatorSetMarkFilteringSet(SFLocatorRef locator, SFUInt16 markFilteringSet);

SF_INTERNAL void SFLocatorReset(SFLocatorRef locator, SFUInteger index, SFUInteger count);

SF_INTERNAL void SFLocatorReserveGlyphs(SFLocatorRef locator, SFUInteger glyphCount);

/**
 * Advances the locator to next glyph.
 * @return
 *      SFTrue if the locator was successfully advanced to the next glyph; SFFalse if the locator
 *      has passed the end of the album.
 */
SF_INTERNAL SFBoolean SFLocatorMoveNext(SFLocatorRef locator);

/**
 * Skips the given number of legitimate glyphs.
 * @return
 *      SFTrue if the given number of glyphs were successfully skipped; SFFalse if the locator could
 *      not find enough legitimate glyphs to skip.
 */
SF_INTERNAL SFBoolean SFLocatorSkip(SFLocatorRef locator, SFUInteger count);

/**
 * Jumps the locator to given index in such a way that next call to MoveNext starts looking
 * legitimate glyphs from this index.
 */
SF_INTERNAL void SFLocatorJumpTo(SFLocatorRef locator, SFUInteger index);

/**
 * Gets the index of legitimate glyph after the given index.
 * @return
 *      The index of next legitimate glyph if available, or SFInvalidIndex if there was no
 *      legitimate glyph after the given index.
 */
SF_INTERNAL SFUInteger SFLocatorGetAfter(SFLocatorRef locator, SFUInteger index);

/**
 * Gets the index of legitimate glyph before the given index.
 * @return
 *      The index of previous legitimate glyph if available, or SFInvalidIndex if there was no
 *      legitimate glyph after the given index.
 */
SF_INTERNAL SFUInteger SFLocatorGetBefore(SFLocatorRef locator, SFUInteger index);

/**
 * Takes the state of other locator provided that it also belong to the same album and is subset of
 * the input locator.
 */
SF_INTERNAL void SFLocatorTakeState(SFLocatorRef locator, SFLocatorRef sibling);

#endif
