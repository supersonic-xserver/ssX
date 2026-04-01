/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FONTCACHEP_H_
#define _FONTCACHEP_H_

#include <X11/extensions/fontcache.h>

int	FontCacheChangeSettings(FontCacheSettingsPtr /* cinfo */);
void	FontCacheGetSettings(FontCacheSettingsPtr /* cinfo */);
void	FontCacheGetStatistics(FontCacheStatisticsPtr /* cstats */);

#endif /* _FONTCACHEP_H_ */
