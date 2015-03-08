/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <imagine/input/Device.hh>
#include <imagine/input/Input.hh>
#include <imagine/logger/logger.h>

namespace Input
{

static const char *keyButtonName(Key b)
{
	switch(b)
	{
		case 0: return "None";
		case Keycode::SPACE: return "Space";
		case Keycode::A: return "a";
		case Keycode::B: return "b";
		case Keycode::C: return "c";
		case Keycode::D: return "d";
		case Keycode::E: return "e";
		case Keycode::F: return "f";
		case Keycode::G: return "g";
		case Keycode::H: return "h";
		case Keycode::I: return "i";
		case Keycode::J: return "j";
		case Keycode::K: return "k";
		case Keycode::L: return "l";
		case Keycode::M: return "m";
		case Keycode::N: return "n";
		case Keycode::O: return "o";
		case Keycode::P: return "p";
		case Keycode::Q: return "q";
		case Keycode::R: return "r";
		case Keycode::S: return "s";
		case Keycode::T: return "t";
		case Keycode::U: return "u";
		case Keycode::V: return "v";
		case Keycode::W: return "w";
		case Keycode::X: return "x";
		case Keycode::Y: return "y";
		case Keycode::Z: return "z";
		case Keycode::APOSTROPHE: return "'";
		case Keycode::COMMA: return ",";
		case Keycode::MINUS: return "-";
		case Keycode::PERIOD: return ".";
		case Keycode::SLASH: return "/";
		case Keycode::_0: return "0";
		case Keycode::_1: return "1";
		case Keycode::_2: return "2";
		case Keycode::_3: return "3";
		case Keycode::_4: return "4";
		case Keycode::_5: return "5";
		case Keycode::_6: return "6";
		case Keycode::_7: return "7";
		case Keycode::_8: return "8";
		case Keycode::_9: return "9";
		case Keycode::SEMICOLON: return ";";
		case Keycode::EQUALS: return "=";
		case Keycode::LEFT_BRACKET: return "[";
		case Keycode::BACKSLASH: return "\\";
		case Keycode::RIGHT_BRACKET: return "]";
		case Keycode::GRAVE: return "`";
		case Keycode::BACK: return "Back";
		case Keycode::ESCAPE: return "Escape";
		case Keycode::ENTER: return "Enter";
		case Keycode::LALT: return "Left Alt";
		case Keycode::RALT: return Config::envIsWebOS1 ? "Mod" : "Right Alt";
		case Keycode::LSHIFT: return "Left Shift";
		case Keycode::RSHIFT: return "Right Shift";
		case Keycode::LCTRL: return "Left Ctrl";
		case Keycode::RCTRL: return Config::envIsWebOS1 ? "Sym" : "Right Ctrl";
		case Keycode::UP: return "Up";
		case Keycode::RIGHT: return "Right";
		case Keycode::DOWN: return "Down";
		case Keycode::LEFT: return "Left";
		case Keycode::BACK_SPACE: return "Back Space";
		case Keycode::MENU: return "Menu";
		case Keycode::HOME: return "Home";
		case Keycode::END: return "End";
		case Keycode::INSERT: return "Insert";
		case Keycode::DELETE: return "Delete";
		case Keycode::TAB: return "Tab";
		case Keycode::SCROLL_LOCK: return "Scroll Lock";
		case Keycode::CAPS: return "Caps Lock";
		case Keycode::PAUSE: return "Pause";
		case Keycode::LSUPER: return "Left Start/Option";
		case Keycode::RSUPER: return "Right Start/Option";
		case Keycode::PGUP: return "Page Up";
		case Keycode::PGDOWN: return "Page Down";
		case Keycode::PRINT_SCREEN: return "Print Screen";
		case Keycode::NUM_LOCK: return "Num Lock";
		case Keycode::NUMPAD_0: return "Numpad 0";
		case Keycode::NUMPAD_1: return "Numpad 1";
		case Keycode::NUMPAD_2: return "Numpad 2";
		case Keycode::NUMPAD_3: return "Numpad 3";
		case Keycode::NUMPAD_4: return "Numpad 4";
		case Keycode::NUMPAD_5: return "Numpad 5";
		case Keycode::NUMPAD_6: return "Numpad 6";
		case Keycode::NUMPAD_7: return "Numpad 7";
		case Keycode::NUMPAD_8: return "Numpad 8";
		case Keycode::NUMPAD_9: return "Numpad 9";
		case Keycode::NUMPAD_DIV: return "Numpad /";
		case Keycode::NUMPAD_MULT: return "Numpad *";
		case Keycode::NUMPAD_SUB: return "Numpad -";
		case Keycode::NUMPAD_ADD: return "Numpad +";
		case Keycode::NUMPAD_DOT: return "Numpad .";
		case Keycode::NUMPAD_COMMA: return "Numpad ,";
		case Keycode::NUMPAD_ENTER: return "Numpad Enter";
		case Keycode::NUMPAD_EQUALS: return "Numpad =";
		#if defined CONFIG_BASE_X11 || defined __ANDROID__
		case Keycode::AT: return "@";
		case Keycode::STAR: return "*";
		case Keycode::PLUS: return "+";
		case Keycode::POUND: return "#";
		case Keycode::LEFT_PAREN: return "(";
		case Keycode::RIGHT_PAREN: return ")";
		case Keycode::SEARCH: return "Search";
		case Keycode::CLEAR: return "Clear";
		case Keycode::EXPLORER: return "Explorer";
		case Keycode::MAIL: return "Mail";
		case Keycode::VOL_UP: return "Vol Up";
		case Keycode::VOL_DOWN: return "Vol Down";
		#endif
		#ifdef CONFIG_BASE_X11
		case Keycode::NUMPAD_INSERT: return "Numpad Insert";
		case Keycode::NUMPAD_DELETE: return "Numpad Delete";
		case Keycode::NUMPAD_BEGIN: return "Numpad Begin";
		case Keycode::NUMPAD_HOME: return "Numpad Home";
		case Keycode::NUMPAD_END: return "Numpad End";
		case Keycode::NUMPAD_PGUP: return "Numpad Page Up";
		case Keycode::NUMPAD_PGDOWN: return "Numpad Page Down";
		case Keycode::NUMPAD_UP: return "Numpad Up";
		case Keycode::NUMPAD_RIGHT: return "Numpad Right";
		case Keycode::NUMPAD_DOWN: return "Numpad Down";
		case Keycode::NUMPAD_LEFT: return "Numpad Left";
		case Keycode::LMETA: return "Left Meta";
		case Keycode::RMETA: return "Right Meta";
		#endif
		case Keycode::F1: return "F1";
		case Keycode::F2: return "F2";
		case Keycode::F3: return "F3";
		case Keycode::F4: return "F4";
		case Keycode::F5: return "F5";
		case Keycode::F6: return "F6";
		case Keycode::F7: return "F7";
		case Keycode::F8: return "F8";
		case Keycode::F9: return "F9";
		case Keycode::F10: return "F10";
		case Keycode::F11: return "F11";
		case Keycode::F12: return "F12";
		case Keycode::GAME_A: return "A";
		case Keycode::GAME_B: return "B";
		case Keycode::GAME_C: return "C";
		case Keycode::GAME_X: return "X";
		case Keycode::GAME_Y: return "Y";
		case Keycode::GAME_Z: return "Z";
		case Keycode::GAME_L1: return "L1";
		case Keycode::GAME_R1: return "R1";
		case Keycode::GAME_L2: return "L2";
		case Keycode::GAME_R2: return "R2";
		case Keycode::GAME_LEFT_THUMB: return "L-Thumb";
		case Keycode::GAME_RIGHT_THUMB: return "R-Thumb";
		case Keycode::GAME_START: return "Start";
		case Keycode::GAME_SELECT: return "Select";
		case Keycode::GAME_MODE: return "Mode";
		case Keycode::GAME_1: return "G1";
		case Keycode::GAME_2: return "G2";
		case Keycode::GAME_3: return "G3";
		case Keycode::GAME_4: return "G4";
		case Keycode::GAME_5: return "G5";
		case Keycode::GAME_6: return "G6";
		case Keycode::GAME_7: return "G7";
		case Keycode::GAME_8: return "G8";
		case Keycode::GAME_9: return "G9";
		case Keycode::GAME_10: return "G10";
		case Keycode::GAME_11: return "G11";
		case Keycode::GAME_12: return "G12";
		case Keycode::GAME_13: return "G13";
		case Keycode::GAME_14: return "G14";
		case Keycode::GAME_15: return "G15";
		case Keycode::GAME_16: return "G16";
		case Keycode::JS1_XAXIS_POS: return "X Axis+";
		case Keycode::JS1_XAXIS_NEG: return "X Axis-";
		case Keycode::JS1_YAXIS_POS: return "Y Axis+";
		case Keycode::JS1_YAXIS_NEG: return "Y Axis-";
		case Keycode::JS2_XAXIS_POS: return "X Axis+ 2";
		case Keycode::JS2_XAXIS_NEG: return "X Axis- 2";
		case Keycode::JS2_YAXIS_POS: return "Y Axis+ 2";
		case Keycode::JS2_YAXIS_NEG: return "Y Axis- 2";
		case Keycode::JS3_XAXIS_POS: return "X Axis+ 3";
		case Keycode::JS3_XAXIS_NEG: return "X Axis- 3";
		case Keycode::JS3_YAXIS_POS: return "Y Axis+ 3";
		case Keycode::JS3_YAXIS_NEG: return "Y Axis- 3";
		case Keycode::JS_POV_XAXIS_POS: return "POV Right";
		case Keycode::JS_POV_XAXIS_NEG: return "POV Left";
		case Keycode::JS_POV_YAXIS_POS: return "POV Down";
		case Keycode::JS_POV_YAXIS_NEG: return "POV Up";
		case Keycode::JS_RUDDER_AXIS_POS: return "Rudder Right";
		case Keycode::JS_RUDDER_AXIS_NEG: return "Rudder Left";
		case Keycode::JS_WHEEL_AXIS_POS: return "Wheel Right";
		case Keycode::JS_WHEEL_AXIS_NEG: return "Wheel Left";
		case Keycode::JS_LTRIGGER_AXIS: return "L Trigger";
		case Keycode::JS_RTRIGGER_AXIS: return "R Trigger";
		case Keycode::JS_GAS_AXIS: return "Gas";
		case Keycode::JS_BRAKE_AXIS: return "Brake";
		// Android-specific
		#ifdef __ANDROID__
		case Keycode::SYMBOL: return "Sym";
		case Keycode::NUM: return "Num";
		case Keycode::FUNCTION: return "Function";
		case Keycode::CENTER: return "Center";
		case Keycode::CAMERA: return "Camera";
		case Keycode::CALL: return "Call";
		case Keycode::END_CALL: return "End Call";
		case Keycode::FOCUS: return "Focus";
		case Keycode::HEADSET_HOOK: return "Headset Hook";
		#endif
	}
	return "Unknown";
}

static const char *iCadeButtonName(Key b)
{
	switch(b)
	{
		case 0: return "None";
		#ifdef CONFIG_BASE_IOS
		// Show the iControlPad buttons only on iOS
		case ICade::X: return "5 (iCP A)";
		case ICade::A: return "6 (iCP X)";
		case ICade::Y: return "7 (iCP Y)";
		case ICade::B: return "8 (iCP B)";
		case ICade::Z: return "9 (iCP L)";
		case ICade::C: return "0 (iCP R)";
		case ICade::SELECT: return "E1 (iCP Select)";
		case ICade::START: return "E2 (iCP Start)";
		#else
		case ICade::X: return "5";
		case ICade::A: return "6";
		case ICade::Y: return "7";
		case ICade::B: return "8";
		case ICade::Z: return "9";
		case ICade::C: return "0";
		case ICade::SELECT: return "E1";
		case ICade::START: return "E2";
		#endif
		case ICade::UP: return "Up";
		case ICade::RIGHT: return "Right";
		case ICade::DOWN: return "Down";
		case ICade::LEFT: return "Left";
	}
	return nullptr;
}

static const char *ps3SysButtonName(Key b)
{
	#if defined CONFIG_BASE_ANDROID
	switch(b)
	{
		case Keycode::PS3::CROSS: return "Cross";
		case Keycode::PS3::CIRCLE: return "Circle";
		case Keycode::PS3::SQUARE: return "Square";
		case Keycode::PS3::TRIANGLE: return "Triangle";
		case Keycode::PS3::PS: return "PS";
		case Keycode::GAME_LEFT_THUMB: return "L3";
		case Keycode::GAME_RIGHT_THUMB: return "R3";
	}
	return nullptr;
	#else
	return nullptr;
	#endif
}

#ifdef CONFIG_BASE_ANDROID
static const char *xperiaPlayButtonName(Key b)
{
	switch(b)
	{
		case Keycode::XperiaPlay::CROSS: return "Cross";
		case Keycode::XperiaPlay::CIRCLE: return "Circle";
		case Keycode::XperiaPlay::SQUARE: return "Square";
		case Keycode::XperiaPlay::TRIANGLE: return "Triangle";
	}
	return nullptr;
}

static const char *ouyaButtonName(Key b)
{
	switch(b)
	{
		case Keycode::Ouya::O: return "O";
		case Keycode::Ouya::U: return "U";
		case Keycode::Ouya::Y: return "Y";
		case Keycode::Ouya::A: return "A";
		case Keycode::Ouya::L3: return "L3";
		case Keycode::Ouya::R3: return "R3";
		case Keycode::MENU: return "System";
	}
	return nullptr;
}
#endif

#ifdef CONFIG_MACHINE_PANDORA
static const char *openPandoraButtonName(Key b)
{
	switch(b)
	{
		case Keycode::Pandora::L: return "L";
		case Keycode::Pandora::R: return "R";
		case Keycode::Pandora::A: return "A";
		case Keycode::Pandora::B: return "B";
		case Keycode::Pandora::Y: return "Y";
		case Keycode::Pandora::X: return "X";
		case Keycode::Pandora::SELECT: return "Select";
		case Keycode::Pandora::START: return "Start";
		case Keycode::Pandora::LOGO: return "Logo";
	}
	return nullptr;
}
#endif

const char *Device::keyName(Key k) const
{
	switch(map())
	{
		case Input::Event::MAP_SYSTEM:
		{
			const char *name = nullptr;
			switch(subtype())
			{
				#ifdef CONFIG_BASE_ANDROID
				bcase Device::SUBTYPE_XPERIA_PLAY: name = xperiaPlayButtonName(k);
				bcase Device::SUBTYPE_OUYA_CONTROLLER: name = ouyaButtonName(k);
				bcase Device::SUBTYPE_PS3_CONTROLLER: name = ps3SysButtonName(k);
				#endif
				#ifdef CONFIG_MACHINE_PANDORA
				bcase Device::SUBTYPE_PANDORA_HANDHELD: name = openPandoraButtonName(k);
				#endif
			}
			if(!name)
				return keyButtonName(k);
			return name;
		}
		#ifdef CONFIG_INPUT_ICADE
		case Input::Event::MAP_ICADE:
		{
			auto name = iCadeButtonName(k);
			if(!name)
			{
				return keyButtonName(k); // if it's not an iCade button, fall back to regular keys
			}
			return name;
		}
		#endif
	}
	return "Unknown";
}

uint Device::map() const
{
	return
		#ifdef CONFIG_INPUT_ICADE
		iCadeMode() ? (uint)Input::Event::MAP_ICADE :
		#endif
		map_;
}

#ifdef CONFIG_INPUT_ICADE
void Device::setICadeMode(bool on)
{
	logWarn("setICadeMode called but unimplemented");
}
#endif

}
