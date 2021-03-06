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
#include <cmath>
#include <stdexcept>

#include <libmocap/abstract-virtual-marker.hh>
#include <libmocap/marker-set.hh>
#include <libmocap/marker-trajectory.hh>
#include <libmocap/virtual-marker-two-points-measured.hh>

namespace libmocap
{
  VirtualMarkerTwoPointsMeasured::VirtualMarkerTwoPointsMeasured
  (const double& offset)
    : AbstractVirtualMarker (),
      offset_ (offset)
  {}

  VirtualMarkerTwoPointsMeasured::VirtualMarkerTwoPointsMeasured
  (const VirtualMarkerTwoPointsMeasured& rhs)
    : AbstractVirtualMarker (rhs),
      offset_ (rhs.offset_)
  {}

  VirtualMarkerTwoPointsMeasured::~VirtualMarkerTwoPointsMeasured ()
  {}

  VirtualMarkerTwoPointsMeasured&
  VirtualMarkerTwoPointsMeasured::operator= (const VirtualMarkerTwoPointsMeasured& rhs)
  {
    if (&rhs == this)
      return *this;
    AbstractVirtualMarker::operator= (rhs);
    offset_ = rhs.offset_;
    return *this;
  }

  std::ostream&
  VirtualMarkerTwoPointsMeasured::print (std::ostream& stream) const
  {
    AbstractVirtualMarker::print (stream);
    return stream;
  }

  AbstractMarker*
  VirtualMarkerTwoPointsMeasured::clone () const
  {
    return new VirtualMarkerTwoPointsMeasured (*this);
  }


  void
  VirtualMarkerTwoPointsMeasured::position
  (double position[3],
   const MarkerSet& markerSet,
   const MarkerTrajectory& trajectory,
   int frameId) const
  {
    std::size_t originMarker_ = static_cast<std::size_t> (originMarker ());
    std::size_t longAxisMarker_ = static_cast<std::size_t> (longAxisMarker ());

    if (frameId < 0)
      throw std::runtime_error ("negative frame id");
    if (frameId >= static_cast<int> (trajectory.positions ().size ()))
      throw std::runtime_error ("frame id is too large");
    if (originMarker () < 0)
      throw std::runtime_error ("negative origin marker");
    if (originMarker () >= static_cast<int> (markerSet.markers ().size ()))
      throw std::runtime_error ("origin marker id too large");
    if (longAxisMarker () < 0)
      throw std::runtime_error ("negative long axis marker");
    if (longAxisMarker () >= static_cast<int> (markerSet.markers ().size ()))
      throw std::runtime_error ("long axis marker id too large");
    if (!markerSet.markers ()[longAxisMarker_])
      throw std::runtime_error ("null long axis marker");

    double marker1[3];
    markerSet.markers ()[originMarker_]->position
      (marker1, markerSet, trajectory, frameId);

    double marker2[3];
    markerSet.markers ()[longAxisMarker_]->position
      (marker2, markerSet, trajectory, frameId);

    double norm = 0.;
    for (std::size_t i = 0; i < 3; ++i)
      norm += std::pow (marker2[i] - marker1[i], 2);
    norm = std::sqrt (norm);

    for (std::size_t i = 0; i < 3; ++i)
      position[i] = marker1[i] + offset_ * (marker2[i] - marker1[i]) / norm;
  }

  std::ostream&
  operator<< (std::ostream& o, const VirtualMarkerTwoPointsMeasured& markerSet)
  {
    return markerSet.print (o);
  }

} // end of namespace libmocap.
