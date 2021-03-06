/*

Copyright (c) 2003, Arvid Norberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TORRENT_FINGERPRINT_HPP_INCLUDED
#define TORRENT_FINGERPRINT_HPP_INCLUDED

#include <string>
#include <sstream>

#include "libtorrent/peer_id.hpp"

namespace libtorrent
{

	struct fingerprint
	{
		fingerprint(const char* id_string, int major, int minor, int revision, int tag)
			: major_version(major)
			, minor_version(minor)
			, revision_version(revision)
			, tag_version(tag)
		{
			assert(id_string);
			assert(major >= 0);
			assert(minor >= 0);
			assert(revision >= 0);
			assert(tag >= 0);
			assert(std::strlen(id_string) == 2);
			name[0] = id_string[0];
			name[1] = id_string[1];
		}

		std::string to_string() const
		{
			std::stringstream s;
			s << "-" << name[0] << name[1]
				<< version_to_char(major_version)
				<< version_to_char(minor_version)
				<< version_to_char(revision_version)
				<< version_to_char(tag_version) << "-";
			return s.str();
		}

		char name[2];
		int major_version;
		int minor_version;
		int revision_version;
		int tag_version;

	private:

		char version_to_char(int v) const
		{
			if (v >= 0 && v < 10) return '0' + v;
			else if (v >= 10) return 'A' + (v - 10);
			assert(false);
			return '0';
		}

	};

}

#endif // TORRENT_FINGERPRINT_HPP_INCLUDED
