/* Residual - Virtual machine to run LucasArts' 3D adventure games
 * Copyright (C) 2003-2006 The ScummVM-Residual Team (www.scummvm.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#ifndef IMUSE_TRACK_H
#define IMUSE_TRACK_H

#include "common/sys.h"
#include "common/debug.h"

#include "engine/lua.h"

#include "mixer/mixer.h"
#include "mixer/audiostream.h"

#include "engine/imuse/imuse_sndmgr.h"
#include "engine/imuse/imuse_mcmp_mgr.h"

enum {
	kFlagUnsigned = 1 << 0,
	kFlag16Bits = 1 << 1,
	kFlagLittleEndian = 1 << 2,
	kFlagStereo = 1 << 3,
	kFlagReverseStereo = 1 << 4
};

struct Track {
	int trackId;

	int32 pan;
	int32 panFadeDest;
	int32 panFadeStep;
	int32 panFadeDelay;
	bool panFadeUsed;
	int32 vol;
	int32 volFadeDest;
	int32 volFadeStep;
	int32 volFadeDelay;
	bool volFadeUsed;

	char soundName[32];
	bool used;
	bool toBeRemoved;
	int32 priority;
	int32 regionOffset;
	int32 dataOffset;
	int32 curRegion;
	int32 curHookId;
	int32 volGroupId;
	int32 feedSize;
	int32 mixerFlags;

	ImuseSndMgr::SoundDesc *soundDesc;
	Audio::SoundHandle handle;
	Audio::AppendableAudioStream *stream;

	Track() : used(false), stream(NULL) {
		soundName[0] = 0;
	}

	int getPan() const { return (pan != 6400) ? 2 * (pan / 1000) - 127 : 0; }
	int getVol() const { return vol / 1000; }
	Audio::Mixer::SoundType getType() const {
		Audio::Mixer::SoundType type = Audio::Mixer::kPlainSoundType;
		if (volGroupId == IMUSE_VOLGRP_VOICE)
			type = Audio::Mixer::kSpeechSoundType;
		else if (volGroupId == IMUSE_VOLGRP_SFX)
			type = Audio::Mixer::kSFXSoundType;
		else if (volGroupId == IMUSE_VOLGRP_MUSIC)
			type = Audio::Mixer::kMusicSoundType;
		else if (volGroupId == IMUSE_VOLGRP_BGND)
			type = Audio::Mixer::kPlainSoundType;
		else if (volGroupId == IMUSE_VOLGRP_ACTION)
			type = Audio::Mixer::kPlainSoundType;
		return type;
	}
};

#endif
