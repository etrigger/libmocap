// Copyright (c) 2014, CNRS-AIST JRL/UMI3218
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef LIBMOCAP_ABSTRACT_VIRTUAL_MARKER_HH
# define LIBMOCAP_ABSTRACT_VIRTUAL_MARKER_HH
# include <iosfwd>

# include <libmocap/config.hh>
# include <libmocap/abstract-marker.hh>
# include <libmocap/util.hh>

namespace libmocap
{
  class LIBMOCAP_DLLEXPORT AbstractVirtualMarker : public AbstractMarker
  {
  public:
    AbstractVirtualMarker ();
    AbstractVirtualMarker (const AbstractVirtualMarker&);
    virtual ~AbstractVirtualMarker ();
    AbstractVirtualMarker& operator= (const AbstractVirtualMarker& rhs);

    LIBMOCAP_ACCESSOR (originMarker, int);
    LIBMOCAP_ACCESSOR (longAxisMarker, int);
    LIBMOCAP_ACCESSOR (planeAxisMarker, int);

    virtual std::ostream& print (std::ostream& o) const;
  private:
    int originMarker_;
    int longAxisMarker_;
    int planeAxisMarker_;
  };

  LIBMOCAP_DLLEXPORT std::ostream&
  operator<< (std::ostream& o, const AbstractVirtualMarker& virtualMarker);

} // end of namespace libmocap.

#endif //! LIBMOCAP_ABSTRACT_VIRTUAL_MARKER_HH
