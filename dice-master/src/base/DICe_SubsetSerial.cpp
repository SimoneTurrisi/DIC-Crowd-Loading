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

#include <DICe_Subset.h>
#include <DICe_ImageUtils.h>

#include <cassert>

namespace DICe {

Subset::Subset(int_t cx,
  int_t cy,
  Teuchos::ArrayRCP<int_t> x,
  Teuchos::ArrayRCP<int_t> y):
  num_pixels_(x.size()),
  cx_(cx),
  cy_(cy),
  has_gradients_(false),
  is_conformal_(false),
  sub_image_id_(0)
{
  assert(num_pixels_>0);
  assert(x.size()==y.size());
  x_ = x;
  y_ = y;
  ref_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  def_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  grad_x_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  grad_y_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  is_active_ = Teuchos::ArrayRCP<bool>(num_pixels_,true);
  is_deactivated_this_step_ = Teuchos::ArrayRCP<bool>(num_pixels_,false);
  reset_is_active();
  reset_is_deactivated_this_step();
}

Subset::Subset(const int_t cx,
  const int_t cy,
  const int_t width,
  const int_t height):
 cx_(cx),
 cy_(cy),
 has_gradients_(false),
 is_conformal_(false),
 sub_image_id_(0)
{
  assert(width>0);
  assert(height>0);
  const int_t half_width = width/2;
  const int_t half_height = height/2;
  // if the width and height arguments are not odd, the next larges odd size is used:
  num_pixels_ = (2*half_width+1)*(2*half_height+1);
  assert(num_pixels_>0);
  x_ = Teuchos::ArrayRCP<int_t>(num_pixels_,0);
  y_ = Teuchos::ArrayRCP<int_t>(num_pixels_,0);
  int_t index = 0;
  for(int_t y=cy_-half_height;y<=cy_+half_height;++y){
    for(int_t x=cx_-half_width;x<=cx_+half_width;++x){
      x_[index] = x;
      y_[index] = y;
      index++;
    }
  }
  ref_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  def_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  grad_x_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  grad_y_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  is_active_ = Teuchos::ArrayRCP<bool>(num_pixels_,true);
  is_deactivated_this_step_ = Teuchos::ArrayRCP<bool>(num_pixels_,false);
  reset_is_active();
  reset_is_deactivated_this_step();
}

Subset::Subset(const int_t cx,
  const int_t cy,
  const Conformal_Area_Def & subset_def):
  cx_(cx),
  cy_(cy),
  has_gradients_(false),
  conformal_subset_def_(subset_def),
  is_conformal_(true),
  sub_image_id_(0)
{
  assert(subset_def.has_boundary());
  std::set<std::pair<int_t,int_t> > coords;
  for(size_t i=0;i<subset_def.boundary()->size();++i){
    std::set<std::pair<int_t,int_t> > shapeCoords = (*subset_def.boundary())[i]->get_owned_pixels();
    coords.insert(shapeCoords.begin(),shapeCoords.end());
  }
  // at this point all the coordinate pairs are in the set
  num_pixels_ = coords.size();
  x_ = Teuchos::ArrayRCP<int_t>(num_pixels_,0);
  y_ = Teuchos::ArrayRCP<int_t>(num_pixels_,0);
  int_t index = 0;
  // NOTE: the pairs are (y,x) not (x,y) so that the ordering is correct in the set
  std::set<std::pair<int_t,int_t> >::iterator set_it = coords.begin();
  for( ; set_it!=coords.end();++set_it){
    x_[index] = set_it->second;
    y_[index] = set_it->first;
    index++;
  }
  // warn the user if the centroid is outside the subset
  std::pair<int_t,int_t> centroid_pair = std::pair<int_t,int_t>(cy_,cx_);
  if(coords.find(centroid_pair)==coords.end())
    std::cout << "*** Warning: centroid " << cx_ << " " << cy_ << " is outside the subset boundary" << std::endl;
  ref_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  def_intensities_ = Teuchos::ArrayRCP<intensity_t>(num_pixels_,0.0);
  grad_x_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  grad_y_ = Teuchos::ArrayRCP<scalar_t>(num_pixels_,0.0);
  is_active_ = Teuchos::ArrayRCP<bool>(num_pixels_,true);
  is_deactivated_this_step_ = Teuchos::ArrayRCP<bool>(num_pixels_,false);
  reset_is_active();
  reset_is_deactivated_this_step();

  // now set the inactive bit for the second set of multishapes if they exist.
  if(subset_def.has_excluded_area()){
    for(size_t i=0;i<subset_def.excluded_area()->size();++i){
      (*subset_def.excluded_area())[i]->deactivate_pixels(num_pixels_,is_active_.getRawPtr(),x_.getRawPtr(),y_.getRawPtr());
    }
  }
  if(subset_def.has_obstructed_area()){
    for(size_t i=0;i<subset_def.obstructed_area()->size();++i){
      std::set<std::pair<int_t,int_t> > obstructedArea = (*subset_def.obstructed_area())[i]->get_owned_pixels();
      obstructed_coords_.insert(obstructedArea.begin(),obstructedArea.end());
    }
  }
}

void
Subset::update_centroid(const int_t cx, const int_t cy){
  const int_t delta_x = cx - cx_;
  const int_t delta_y = cy - cy_;
  cx_ = cx;
  cy_ = cy;
  for(int_t i=0;i<num_pixels_;++i){
    x_[i] += delta_x;
    y_[i] += delta_y;
  }
}

const int_t&
Subset::x(const int_t pixel_index)const{
  return x_[pixel_index];
}

const int_t&
Subset::y(const int_t pixel_index)const{
  return y_[pixel_index];
}

const scalar_t&
Subset::grad_x(const int_t pixel_index)const{
  return grad_x_[pixel_index];
}

const scalar_t&
Subset::grad_y(const int_t pixel_index)const{
  return grad_y_[pixel_index];
}

intensity_t&
Subset::ref_intensities(const int_t pixel_index){
  return ref_intensities_[pixel_index];
}

intensity_t&
Subset::def_intensities(const int_t pixel_index){
  return def_intensities_[pixel_index];
}

/// returns true if this pixel is active
bool &
Subset::is_active(const int_t pixel_index){
  return is_active_[pixel_index];
}

/// returns true if this pixel is deactivated for this particular frame
bool &
Subset::is_deactivated_this_step(const int_t pixel_index){
  return is_deactivated_this_step_[pixel_index];
}

void
Subset::reset_is_active(){
  for(int_t i=0;i<num_pixels_;++i)
    is_active_[i] = true;
}

void
Subset::reset_is_deactivated_this_step(){
  for(int_t i=0;i<num_pixels_;++i)
    is_deactivated_this_step_[i] = false;
}

intensity_t
Subset::max(const Subset_View_Target target){
  intensity_t max = -1.0E10;
  if(target==REF_INTENSITIES){
    for(int_t i=0;i<num_pixels_;++i){
      if(is_active_[i]&!is_deactivated_this_step_[i])
        if(ref_intensities_[i]>max)
          max = ref_intensities_[i];
    }
  }else{
    for(int_t i=0;i<num_pixels_;++i)
      if(is_active_[i]&!is_deactivated_this_step_[i]){
        if(def_intensities_[i]>max)
          max = def_intensities_[i];
      }
  }
  return max;
}

intensity_t
Subset::min(const Subset_View_Target target){
  intensity_t min = 1.0E10;
  if(target==REF_INTENSITIES){
    for(int_t i=0;i<num_pixels_;++i){
      if(is_active_[i]&!is_deactivated_this_step_[i])
        if(ref_intensities_[i]<min)
          min = ref_intensities_[i];
    }
  }else{
    for(int_t i=0;i<num_pixels_;++i)
      if(is_active_[i]&!is_deactivated_this_step_[i]){
        if(def_intensities_[i]<min)
          min = def_intensities_[i];
      }
  }
  return min;
}

void
Subset::round(const Subset_View_Target target){
  if(target==REF_INTENSITIES){
    for(int_t i=0;i<num_pixels_;++i)
      ref_intensities_[i] = std::round(ref_intensities_[i]);
  }else{
    for(int_t i=0;i<num_pixels_;++i)
      def_intensities_[i] = std::round(def_intensities_[i]);
  }
}

scalar_t
Subset::mean(const Subset_View_Target target){
  scalar_t mean = 0.0;
  int_t num_active = num_active_pixels();
  if(target==REF_INTENSITIES){
    for(int_t i=0;i<num_pixels_;++i){
      if(is_active_[i]&!is_deactivated_this_step_[i])
        mean += ref_intensities_[i];
    }
  }else{
    for(int_t i=0;i<num_pixels_;++i)
      if(is_active_[i]&!is_deactivated_this_step_[i]){
        mean += def_intensities_[i];
      }
  }
  return num_active != 0 ? mean/num_active : 0.0;
}

scalar_t
Subset::mean(const Subset_View_Target target,
  scalar_t & sum){
  scalar_t mean_ = mean(target);
  sum = 0.0;
  if(target==REF_INTENSITIES){
    for(int_t i=0;i<num_pixels_;++i){
      if(is_active_[i]&!is_deactivated_this_step_[i])
        sum += (ref_intensities_[i]-mean_)*(ref_intensities_[i]-mean_);
    }
  }else{
    for(int_t i=0;i<num_pixels_;++i){
      if(is_active_[i]&!is_deactivated_this_step_[i])
        sum += (def_intensities_[i]-mean_)*(def_intensities_[i]-mean_);
    }
  }
  sum = std::sqrt(sum);
  return mean_;
}

scalar_t
Subset::gamma(){
  // assumes obstructed pixels are already turned off
  scalar_t mean_sum_ref = 0.0;
  const scalar_t mean_ref = mean(REF_INTENSITIES,mean_sum_ref);
  scalar_t mean_sum_def = 0.0;
  const scalar_t mean_def = mean(DEF_INTENSITIES,mean_sum_def);
  if(mean_sum_ref==0.0||mean_sum_def==0.0) return -1.0;
  scalar_t gamma = 0.0;
  scalar_t value = 0.0;
  for(int_t i=0;i<num_pixels_;++i){
    if(is_active_[i]&!is_deactivated_this_step_[i]){
      value = (def_intensities_[i]-mean_def)/mean_sum_def - (ref_intensities_[i]-mean_ref)/mean_sum_ref;
      gamma += value*value;
    }
  }
  return gamma;
}

scalar_t
Subset::diff_ref_def() const{
  scalar_t diff = 0.0;
  for(int_t i=0;i<num_pixels_;++i)
    diff += (ref_intensities_[i]-def_intensities_[i])*(ref_intensities_[i]-def_intensities_[i]);
  diff = std::sqrt(diff);
  return diff;
}


Teuchos::ArrayRCP<scalar_t>
Subset::grad_x_array()const{
  // note: the Kokkos version returns a copy of the array, the serial version returns the array itself (providing access to modify)
  return grad_x_;
}

Teuchos::ArrayRCP<scalar_t>
Subset::grad_y_array()const{
  return grad_y_;
}

scalar_t
Subset::sssig(){
  // assumes obstructed pixels are already turned off
  scalar_t sssig = 0.0;
  for(int_t i=0;i<num_pixels_;++i){
    sssig += grad_x_[i]*grad_x_[i] + grad_y_[i]*grad_y_[i];
  }
  sssig /= num_pixels_==0.0?1.0:num_pixels_;
  return sssig;
}

void
Subset::initialize(Teuchos::RCP<Image> image,
  const Subset_View_Target target,
  Teuchos::RCP<Local_Shape_Function> shape_function,
  const Interpolation_Method interp){

  // coordinates for points x and y are always in global coordinates
  // if the input image is a sub-image i.e. it has offsets, then these need to be taken into account
  const int_t offset_x = image->offset_x();
  const int_t offset_y = image->offset_y();
  const int_t w = image->width();
  const int_t h = image->height();
  Teuchos::ArrayRCP<intensity_t> intensities_ = target==REF_INTENSITIES ? ref_intensities_ : def_intensities_;
  // assume if the map is null, use the no_map_tag in the parrel for call of the functor
  if(shape_function==Teuchos::null){
    for(int_t i=0;i<num_pixels_;++i)
      intensities_[i] = (*image)(x_[i]-offset_x,y_[i]-offset_y);
  }
  else{
    int_t px,py;
    const bool has_blocks = !pixels_blocked_by_other_subsets_.empty();
    // initialize the work variables
    scalar_t mapped_x = 0.0;
    scalar_t mapped_y = 0.0;
    const scalar_t ox=(scalar_t)offset_x,oy=(scalar_t)offset_y;
    for(int_t i=0;i<num_pixels_;++i){
      shape_function->map(x_[i],y_[i],cx_,cy_,mapped_x,mapped_y);
      px = ((int_t)(mapped_x + 0.5) == (int_t)(mapped_x)) ? (int_t)(mapped_x) : (int_t)(mapped_x) + 1;
      py = ((int_t)(mapped_y + 0.5) == (int_t)(mapped_y)) ? (int_t)(mapped_y) : (int_t)(mapped_y) + 1;
      // out of image bounds ( 4 pixel buffer to ensure enough room to interpolate away from the sub image boundary)
      if(px<offset_x+4||px>=offset_x+w-4||py<offset_y+4||py>=offset_y+h-4){
        is_deactivated_this_step(i) = true;
        continue;
      }
      if(is_obstructed_pixel(mapped_x,mapped_y)){
        is_deactivated_this_step(i) = true;
        continue;
      }
      if(has_blocks){
        if(pixels_blocked_by_other_subsets_.find(std::pair<int_t,int_t>(py,px))
            !=pixels_blocked_by_other_subsets_.end()){
          is_deactivated_this_step(i) = true;
          continue;
        }
      }
      // if the code got here, the pixel is not deactivated
      is_deactivated_this_step(i) = false;
      if(interp==BILINEAR){
        image->interpolate_bilinear_all(intensities_[i], grad_x_[i], grad_y_[i],
               image->has_gradients(), mapped_x-ox, mapped_y-oy);
      }
      else if(interp==BICUBIC){
        image->interpolate_bicubic_all(intensities_[i], grad_x_[i], grad_y_[i],
               image->has_gradients(), mapped_x-ox, mapped_y-oy);
      }
      else if(interp==KEYS_FOURTH){
        image->interpolate_keys_fourth_all(intensities_[i], grad_x_[i], grad_y_[i],
               image->has_gradients(), mapped_x-ox, mapped_y-oy);
      }
      else{
        TEUCHOS_TEST_FOR_EXCEPTION(true,std::invalid_argument,
          "Error, unknown interpolation method requested");
      }
    }
  }
  // now sync up the intensities:
  if(target==REF_INTENSITIES){
    if(image->has_gradients()){
      // copy over the image gradients:
      for(int_t px=0;px<num_pixels_;++px){
        grad_x_[px] = image->grad_x(x_[px]-offset_x,y_[px]-offset_y);
        grad_y_[px] = image->grad_y(x_[px]-offset_x,y_[px]-offset_y);
      }
      has_gradients_ = true;
    }
  }
}

}// End DICe Namespace
