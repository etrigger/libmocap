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
#include <iostream>
#include <libmocap/abstract-marker.hh>

namespace libmocap
{
  AbstractMarker::AbstractMarker ()
    : id_ (),
      name_ (),
      color_ (),
      physicalColor_ (),
      size_ (),
      optional_ ()
  {}

  AbstractMarker::AbstractMarker (const AbstractMarker& rhs)
    : id_ (rhs.id_),
      name_ (rhs.name_),
      color_ (rhs.color_),
      physicalColor_ (rhs.physicalColor_),
      size_ (rhs.size_),
      optional_ (rhs.optional_)
  {}

  AbstractMarker::~AbstractMarker ()
  {}

  AbstractMarker&
  AbstractMarker::operator= (const AbstractMarker& rhs)
  {
    if (this == &rhs)
      return *this;

    id_ = rhs.id_;
    name_ = rhs.name_;
    color_ = rhs.color_;
    physicalColor_ = rhs.physicalColor_;
    size_ = rhs.size_;
    optional_ = rhs.optional_;

    return *this;
  }

  std::ostream&
  AbstractMarker::print (std::ostream& stream) const
  {
    stream
      << "abstract marker:\n"
      << "id: " << id () << '\n'
      << "name: " << name () << '\n'
      << "color: " << color () << '\n'
      << "physical color: " << physicalColor () << '\n'
      << "size: " << size () << '\n'
      << "optional: " << (optional () ? "yes" : "no");

    return stream;
  }

  std::ostream&
  operator<< (std::ostream& o, const AbstractMarker& markerSet)
  {
    return markerSet.print (o);
  }

} // end of namespace libmocap.