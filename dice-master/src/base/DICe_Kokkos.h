// @HEADER
// ************************************************************************
//
//               Digital Image Correlation Engine (DICe)
//                 Copyright 2015 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
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
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NTESS OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact: Dan Turner (dzturne@sandia.gov)
//
// ************************************************************************
// @HEADER

#ifndef DICE_KOKKOS_H
#define DICE_KOKKOS_H

#include <Kokkos_Core.hpp>
#include <Kokkos_DualView.hpp>

#include <DICe.h>

namespace DICe{

/// execution space
typedef Kokkos::DefaultExecutionSpace device_space;
/// host space (cpu)
typedef Kokkos::HostSpace host_space;

/// kokkos view types

/// 2 dimensional array of intensity values for the device
typedef Kokkos::View<intensity_t **, Kokkos::MemoryTraits<Kokkos::RandomAccess> > intensity_device_view_2d;
/// host mirrors of the intensity value arrays
typedef intensity_device_view_2d::HostMirror intensity_host_view_2d;

/// 1 dimensional array of (subset) intensity values for the device
// note this is not random access on purpose
typedef Kokkos::View<intensity_t *> intensity_device_view_1d;

/// 1 dimensional dual view of intensity type values
typedef Kokkos::DualView<intensity_t *,Kokkos::MemoryTraits<Kokkos::RandomAccess> >  intensity_dual_view_1d;

/// 2 dimensional dual view of intensity type values
typedef Kokkos::DualView<intensity_t **,Kokkos::MemoryTraits<Kokkos::RandomAccess> >  intensity_dual_view_2d;

/// 2 dimensional dual view of intensity type values
typedef Kokkos::DualView<scalar_t *,Kokkos::MemoryTraits<Kokkos::RandomAccess> >  scalar_dual_view_1d;

/// 1 dimensional dual view of bool type values
typedef Kokkos::DualView<bool *,Kokkos::MemoryTraits<Kokkos::RandomAccess> >  bool_dual_view_1d;

/// 2 dimensional dual view of scalar type values
typedef Kokkos::DualView<scalar_t **>  scalar_dual_view_2d;

/// 2 dimensional array of scalar values for the device
// note this is not random access on purpose
typedef Kokkos::View<scalar_t **> scalar_device_view_2d;

/// 1 dimensional array of pixel coordinate values for the device
typedef Kokkos::View<int_t *> pixel_coord_device_view_1d;

/// 1 dimensional array of bool values for the device
typedef Kokkos::View<bool *> bool_device_view_1d;

/// host mirrors of the intensity value arrays
typedef pixel_coord_device_view_1d::HostMirror pixel_coord_host_view_1d;

/// 1 dimensional dual view of size type values
typedef Kokkos::DualView<int_t *>  pixel_coord_dual_view_1d;

/// member type
typedef typename Kokkos::TeamPolicy<device_space>::member_type member_type;


} // end DICe namespace

#endif
