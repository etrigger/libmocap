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
#include <algorithm>
#include <iterator>
#include <stdexcept>

#include <libmocap/marker-set.hh>

namespace libmocap
{
  template <typename T>
  static T& dereference(T* ptr)
  {
    return *ptr;
  }

  MarkerSet::MarkerSet ()
    : name_ (),
      markers_ (),
      links_ (),
      segments_ (),
      poses_ ()
  {}

  MarkerSet::MarkerSet (const MarkerSet& rhs)
    : name_ (rhs.name_),
      markers_ (),
      links_ (rhs.links_),
      segments_ (rhs.segments_),
      poses_ (rhs.poses_)
  {
    std::vector<AbstractMarker*>::const_iterator it;
    for (it = rhs.markers_.begin (); it != rhs.markers_.end (); ++it)
      if (*it)
	markers_.push_back ((*it)->clone ());
  }


  MarkerSet::~MarkerSet ()
  {
    std::vector<AbstractMarker*>::const_iterator it;
    for (it = markers ().begin (); it != markers ().end (); ++it)
      delete *it;
    markers ().clear ();
  }

  MarkerSet&
  MarkerSet::operator= (const MarkerSet& rhs)
  {
    if (&rhs == this)
      return *this;
    name_ = rhs.name_;

    std::vector<AbstractMarker*>::const_iterator it;
    for (it = rhs.markers_.begin (); it != rhs.markers_.end (); ++it)
      if (*it)
	markers_.push_back ((*it)->clone ());

    links_ = rhs.links_;
    segments_ = rhs.segments_;
    poses_ = rhs.poses_;
    return *this;
  }

  std::ostream&
  MarkerSet::print (std::ostream& stream) const
  {
    stream
      << "name: " << name () << "\n"
      << "markers:\n";
    if (markers ().empty ())
      stream << "(no marker)\n";
    std::transform(markers ().begin (),
		   markers ().end (),
		   std::ostream_iterator<AbstractMarker>(stream, "\n"),
		   dereference<AbstractMarker>);
    stream << '\n' << "links:\n";
    if (links ().empty ())
      stream << "(no link)\n";
    std::copy
      (links ().begin (), links ().end (),
       std::ostream_iterator<Link>(stream, "\n"));
    stream
      << '\n' << "segments:\n";
    if (segments ().empty ())
      stream << "(no segment)\n";
    std::copy
      (segments ().begin (), segments ().end (),
       std::ostream_iterator<Segment>(stream, "\n"));
    stream
      << '\n' << "poses:\n";
    if (poses ().empty ())
      stream << "(no pose)\n";
    std::copy
      (poses ().begin (), poses ().end (),
       std::ostream_iterator<Pose>(stream, "\n"));
    stream << '\n';
    return stream;
  }

  const AbstractMarker&
  MarkerSet::markerByName (const std::string name) const
  {
    std::vector<AbstractMarker*>::const_iterator it;
    for (it = markers_.begin (); it != markers_.end (); ++it)
      {
	if (*it && (*it)->name () == name)
	  return **it;
      }

    std::string error =
      "marker " + name + " does not exist";
    throw std::runtime_error (error);
  }

  std::ostream&
  operator<< (std::ostream& o, const MarkerSet& markerSet)
  {
    return markerSet.print (o);
  }


} // end of namespace libmocap.
