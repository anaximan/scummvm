/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GOB_GOB_H
#define GOB_GOB_H

#include "common/random.h"
#include "common/system.h"

#include "graphics/pixelformat.h"

#include "engines/engine.h"

#include "gob/console.h"
#include "gob/detection/detection.h"

/**
 * This is the namespace of the Gob engine.
 *
 * Status of this engine: ???
 *
 * Games using this engine:
 * - Gobliiins
 * - Gobliins 2
 * - Goblins 3
 * - Ween: The Prophecy
 * - Bargon Attack
 * - Lost in Time
 * - The Bizarre Adventures of Woodruff and the Schnibble
 * - Fascination
 * - Urban Runner
 * - Bambou le sauveur de la jungle
 * - Geisha
 * - Once Upon A Time: Little Red Riding Hood
 * - Croustibat
 */
namespace Gob {

class Game;
class Sound;
class Video;
class Global;
class Draw;
class DataIO;
class Goblin;
class VideoPlayer;
class Init;
class Inter;
class Map;
class Mult;
class PalAnim;
class Scenery;
class Util;
class SaveLoad;
class PreGob;

#define WRITE_VAR_UINT32(var, val)  _vm->_inter->_variables->writeVar32(var, val)
#define WRITE_VAR_UINT16(var, val)  _vm->_inter->_variables->writeVar16(var, val)
#define WRITE_VAR_UINT8(var, val)   _vm->_inter->_variables->writeVar8(var, val)
#define WRITE_VAR_STR(var, str)     _vm->_inter->_variables->writeVarString(var, str)
#define WRITE_VARO_UINT32(off, val) _vm->_inter->_variables->writeOff32(off, val)
#define WRITE_VARO_UINT16(off, val) _vm->_inter->_variables->writeOff16(off, val)
#define WRITE_VARO_UINT8(off, val)  _vm->_inter->_variables->writeOff8(off, val)
#define WRITE_VARO_STR(off, str)    _vm->_inter->_variables->writeOffString(off, str)
#define READ_VAR_UINT32(var)        _vm->_inter->_variables->readVar32(var)
#define READ_VAR_UINT16(var)        _vm->_inter->_variables->readVar16(var)
#define READ_VAR_UINT8(var)         _vm->_inter->_variables->readVar8(var)
#define READ_VARO_UINT32(off)       _vm->_inter->_variables->readOff32(off)
#define READ_VARO_UINT16(off)       _vm->_inter->_variables->readOff16(off)
#define READ_VARO_UINT8(off)        _vm->_inter->_variables->readOff8(off)
#define GET_VAR_STR(var)            _vm->_inter->_variables->getAddressVarString(var)
#define GET_VARO_STR(off)           _vm->_inter->_variables->getAddressOffString(off)
#define GET_VAR_FSTR(var)           _vm->_inter->_variables->getAddressVarString(var)
#define GET_VARO_FSTR(off)          _vm->_inter->_variables->getAddressOffString(off)

#define WRITE_VAR_OFFSET(off, val)  WRITE_VARO_UINT32((off), (val))
#define WRITE_VAR(var, val)         WRITE_VAR_UINT32((var), (val))
#define VAR_OFFSET(off)             READ_VARO_UINT32(off)
#define VAR(var)                    READ_VAR_UINT32(var)


// WARNING: Reordering these will invalidate save games!
enum Endianness {
	kEndiannessLE,
	kEndiannessBE
};

enum EndiannessMethod {
	kEndiannessMethodLE,     ///< Always little endian.
	kEndiannessMethodBE,     ///< Always big endian.
	kEndiannessMethodSystem, ///< Follows system endianness.
	kEndiannessMethodAltFile ///< Different endianness in alternate file.
};

enum {
	kDebugFuncOp     = 1 <<  0,
	kDebugDrawOp     = 1 <<  1,
	kDebugGobOp      = 1 <<  2,
	kDebugSound      = 1 <<  3,
	kDebugExpression = 1 <<  4,
	kDebugGameFlow   = 1 <<  5,
	kDebugFileIO     = 1 <<  6,
	kDebugSaveLoad   = 1 <<  7,
	kDebugGraphics   = 1 <<  8,
	kDebugVideo      = 1 <<  9,
	kDebugHotspots   = 1 << 10,
	kDebugDemo       = 1 << 11
};

class GobEngine : public Engine {
private:
	GameType _gameType;
	int32 _features;
	Common::Platform _platform;

	EndiannessMethod _endiannessMethod;

	uint32 _pauseStart;

	// Engine APIs
	Common::Error run() override;
	bool hasFeature(EngineFeature f) const override;
	void pauseEngineIntern(bool pause) override;
	void syncSoundSettings() override;

	Common::Error initGameParts();
	Common::Error initGraphics();

	void deinitGameParts();

public:
	static const Common::Language _gobToScummVMLang[];

	Common::RandomSource _rnd;

	Common::Language _language;
	uint16 _width;
	uint16 _height;
	uint8 _mode;

	Graphics::PixelFormat _pixelFormat;

	Common::String _startStk;
	Common::String _startTot;
	uint32 _demoIndex;

	bool _copyProtection;
	bool _noMusic;

	GobConsole *_console;

	bool _resourceSizeWorkaround;
	bool _enableAdibou2FreeBananasWorkaround;
	bool _enableAdibou2FlowersInfiniteLoopWorkaround;

	Global *_global;
	Util *_util;
	DataIO *_dataIO;
	Game *_game;
	Sound *_sound;
	Video *_video;
	Draw *_draw;
	Goblin *_goblin;
	Init *_init;
	Map *_map;
	Mult *_mult;
	PalAnim *_palAnim;
	Scenery *_scenery;
	Inter *_inter;
	SaveLoad *_saveLoad;
	VideoPlayer *_vidPlayer;
	PreGob *_preGob;

	const char *getLangDesc(int16 language) const;
	void validateLanguage();
	void validateVideoMode(int16 videoMode);

	void pauseGame();

	EndiannessMethod getEndiannessMethod() const;
	Endianness getEndianness() const;
	Common::Platform getPlatform() const;
	GameType getGameType() const;
	bool isCD() const;
	bool isEGA() const;
	bool hasAdLib() const;
	bool isSCNDemo() const;
	bool isBATDemo() const;
	bool is640x480() const;
	bool is800x600() const;
	bool isTrueColor() const;
	bool isDemo() const;

	bool hasResourceSizeWorkaround() const;

	bool isCurrentTot(const Common::String &tot) const;

	void setTrueColor(bool trueColor);

	const Graphics::PixelFormat &getPixelFormat() const;

	GobEngine(OSystem *syst);
	~GobEngine() override;

	void initGame(const GOBGameDescription *gd);
};

} // End of namespace Gob

#endif // GOB_GOB_H
