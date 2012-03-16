/*
    Mosh: the mobile shell
    Copyright 2012 Keith Winstein

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TERMINALDISPLAY_HPP
#define TERMINALDISPLAY_HPP

#include "terminalframebuffer.h"

namespace Terminal {
  /* variables used within a new_frame */
  class FrameState {
  public:
    int x, y;
    std::string str;

    int cursor_x, cursor_y;
    Renditions current_rendition;

    Framebuffer last_frame;

    FrameState( const Framebuffer &s_last )
      : x(0), y(0),
	str(), cursor_x(0), cursor_y(0), current_rendition( 0 ),
	last_frame( s_last )
    {
      str.reserve( 1024 );
    }

    void append( const char * s ) { str.append( s ); }
    void appendstring( const std::string s ) { str.append( s ); }

    void append_silent_move( int y, int x );
  };

  class Display {
  private:
    bool has_ech; /* erase character is part of vt200 but not supported by tmux
		     (or by "screen" terminfo entry, which is what tmux advertises) */

    bool has_bce; /* erases result in cell filled with background color */

    void put_cell( bool initialized, FrameState &frame, const Framebuffer &f ) const;

  public:
    std::string new_frame( bool initialized, const Framebuffer &last, const Framebuffer &f ) const;

    Display( bool use_environment );
  };
}

#endif
