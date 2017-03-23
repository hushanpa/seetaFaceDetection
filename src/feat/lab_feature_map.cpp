/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
 *
 * This file is part of the SeetaFace Detection module, containing codes implementing the
 * face detection method described in the following paper:
 *
 *
 *   Funnel-structured cascade for multi-view face detection with alignment awareness,
 *   Shuzhe Wu, Meina Kan, Zhenliang He, Shiguang Shan, Xilin Chen.
 *   In Neurocomputing (under review)
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developed by Shuzhe Wu (a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#include "feat/lab_feature_map.h"

#include <cmath>

#include "util/math_func.h"
#include "hi_ive/Integ.h"

unsigned short mySqrTab[] =
{
	16384, 16129, 15876, 15625, 15376, 15129, 14884, 14641,
	14400, 14161, 13924, 13689, 13456, 13225, 12996, 12769,
	12544, 12321, 12100, 11881, 11664, 11449, 11236, 11025,
	10816, 10609, 10404, 10201, 10000, 9801, 9604, 9409,
	9216, 9025, 8836, 8649, 8464, 8281, 8100, 7921,
	7744, 7569, 7396, 7225, 7056, 6889, 6724, 6561,
	6400, 6241, 6084, 5929, 5776, 5625, 5476, 5329,
	5184, 5041, 4900, 4761, 4624, 4489, 4356, 4225,
	4096, 3969, 3844, 3721, 3600, 3481, 3364, 3249,
	3136, 3025, 2916, 2809, 2704, 2601, 2500, 2401,
	2304, 2209, 2116, 2025, 1936, 1849, 1764, 1681,
	1600, 1521, 1444, 1369, 1296, 1225, 1156, 1089,
	1024, 961, 900, 841, 784, 729, 676, 625,
	576, 529, 484, 441, 400, 361, 324, 289,
	256, 225, 196, 169, 144, 121, 100, 81,
	64, 49, 36, 25, 16, 9, 4, 1,
	0, 1, 4, 9, 16, 25, 36, 49,
	64, 81, 100, 121, 144, 169, 196, 225,
	256, 289, 324, 361, 400, 441, 484, 529,
	576, 625, 676, 729, 784, 841, 900, 961,
	1024, 1089, 1156, 1225, 1296, 1369, 1444, 1521,
	1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209,
	2304, 2401, 2500, 2601, 2704, 2809, 2916, 3025,
	3136, 3249, 3364, 3481, 3600, 3721, 3844, 3969,
	4096, 4225, 4356, 4489, 4624, 4761, 4900, 5041,
	5184, 5329, 5476, 5625, 5776, 5929, 6084, 6241,
	6400, 6561, 6724, 6889, 7056, 7225, 7396, 7569,
	7744, 7921, 8100, 8281, 8464, 8649, 8836, 9025,
	9216, 9409, 9604, 9801, 10000, 10201, 10404, 10609,
	10816, 11025, 11236, 11449, 11664, 11881, 12100, 12321,
	12544, 12769, 12996, 13225, 13456, 13689, 13924, 14161,
	14400, 14641, 14884, 15129, 15376, 15625, 15876, 16129,
	16384, 16641, 16900, 17161, 17424, 17689, 17956, 18225,
	18496, 18769, 19044, 19321, 19600, 19881, 20164, 20449,
	20736, 21025, 21316, 21609, 21904, 22201, 22500, 22801,
	23104, 23409, 23716, 24025, 24336, 24649, 24964, 25281,
	25600, 25921, 26244, 26569, 26896, 27225, 27556, 27889,
	28224, 28561, 28900, 29241, 29584, 29929, 30276, 30625,
	30976, 31329, 31684, 32041, 32400, 32761, 33124, 33489,
	33856, 34225, 34596, 34969, 35344, 35721, 36100, 36481,
	36864, 37249, 37636, 38025, 38416, 38809, 39204, 39601,
	40000, 40401, 40804, 41209, 41616, 42025, 42436, 42849,
	43264, 43681, 44100, 44521, 44944, 45369, 45796, 46225,
	46656, 47089, 47524, 47961, 48400, 48841, 49284, 49729,
	50176, 50625, 51076, 51529, 51984, 52441, 52900, 53361,
	53824, 54289, 54756, 55225, 55696, 56169, 56644, 57121,
	57600, 58081, 58564, 59049, 59536, 60025, 60516, 61009,
	61504, 62001, 62500, 63001, 63504, 64009, 64516, 65025
};

 void mySquare(const int32_t* src, uint32_t* dest, int32_t len) {
	int32_t i;
	for (i = 0; i < len; i++)
	{
		int32_t value = *(src + i);
		*(dest + i) = mySqrTab[(value)+128];
	}

}

namespace seeta {
namespace fd {

void LABFeatureMap::Compute(const uint8_t* input, int32_t width,
    int32_t height) {
  if (input == nullptr || width <= 0 || height <= 0) {
    return;  // @todo handle the errors!!!
  }

  Reshape(width, height);		//scaled img width and height
  ComputeIntegralImages(input);	//calculate integral img
  ComputeRectSum();
  ComputeFeatureMap();
}

float LABFeatureMap::GetStdDev() const {
  double mean;
  double m2;
  double area = roi_.width * roi_.height;

  int32_t top_left;
  int32_t top_right;
  int32_t bottom_left;
  int32_t bottom_right;

  if (roi_.x != 0) {
    if (roi_.y != 0) {
      top_left = (roi_.y - 1) * width_ + roi_.x - 1;
      top_right = top_left + roi_.width;
      bottom_left = top_left + roi_.height * width_;
      bottom_right = bottom_left + roi_.width;

      mean = (int_img_[bottom_right] - int_img_[bottom_left] +
        int_img_[top_left] - int_img_[top_right]) / area;
      m2 = (square_int_img_[bottom_right] - square_int_img_[bottom_left] +
        square_int_img_[top_left] - square_int_img_[top_right]) / area;
    } else {
      bottom_left = (roi_.height - 1) * width_ + roi_.x - 1;
      bottom_right = bottom_left + roi_.width;

      mean = (int_img_[bottom_right] - int_img_[bottom_left]) / area;
      m2 = (square_int_img_[bottom_right] - square_int_img_[bottom_left]) / area;
    }
  } else {
    if (roi_.y != 0) {
      top_right = (roi_.y - 1) * width_ + roi_.width - 1;
      bottom_right = top_right + roi_.height * width_;

      mean = (int_img_[bottom_right] - int_img_[top_right]) / area;
      m2 = (square_int_img_[bottom_right] - square_int_img_[top_right]) / area;
    } else {
      bottom_right = (roi_.height - 1) * width_ + roi_.width - 1;
      mean = int_img_[bottom_right] / area;
      m2 = square_int_img_[bottom_right] / area;
    }
  }

  return static_cast<float>(std::sqrt(m2 - mean * mean));
}

void LABFeatureMap::Reshape(int32_t width, int32_t height) {
  width_ = width;
  height_ = height;

  int32_t len = width_ * height_;
  feat_map_.resize(len);
  rect_sum_.resize(len);
  int_img_.resize(len);
  square_int_img_.resize(len);
}

void LABFeatureMap::ComputeIntegralImages(const uint8_t* input) {
	int32_t len = width_ * height_;

	seeta::fd::MathFunction::UInt8ToInt32(input, int_img_.data(), len);
#if 1
	//seeta::fd::MathFunction::Square(int_img_.data(), square_int_img_.data(), len);
	mySquare(int_img_.data(), square_int_img_.data(), len);
	Integral(int_img_.data());
	Integral(square_int_img_.data());
#else
	memcpy(square_int_img_.data(), int_img_.data(), width_*height_*sizeof(int));
	IntegSampleSum(int_img_.data(), width_, height_);
	IntegSampleSqsum((int*)square_int_img_.data(), width_, height_);
#endif
}

void LABFeatureMap::ComputeRectSum() {
  int32_t width = width_ - rect_width_;	//rect: = 3*3
  int32_t height = height_ - rect_height_;
  const int32_t* int_img = int_img_.data();
  int32_t* rect_sum = rect_sum_.data();

  *rect_sum = *(int_img + (rect_height_ - 1) * width_ + rect_width_ - 1);		//the first val
  seeta::fd::MathFunction::VectorSub(int_img + (rect_height_ - 1) * width_ +	//the first line of rect_sum, meanning the first row  3*3 rect of the ini_img,calculated by rect bottom right sub rect bottom left.
    rect_width_, int_img + (rect_height_ - 1) * width_, rect_sum + 1, width);

#pragma omp parallel num_threads(SEETA_NUM_THREADS)
  {
#pragma omp for nowait
    for (int32_t i = 1; i <= height; i++) {
      const int32_t* top_left = int_img + (i - 1) * width_;
      const int32_t* top_right = top_left + rect_width_ - 1;
      const int32_t* bottom_left = top_left + rect_height_ * width_;
      const int32_t* bottom_right = bottom_left + rect_width_ - 1;
      int32_t* dest = rect_sum + i * width_;

      *(dest++) = (*bottom_right) - (*top_right);
      seeta::fd::MathFunction::VectorSub(bottom_right + 1, top_right + 1, dest, width);
      seeta::fd::MathFunction::VectorSub(dest, bottom_left, dest, width);
      seeta::fd::MathFunction::VectorAdd(dest, top_left, dest, width);	//bottom_right + top_left - top_right - bottom_left
    }
  }
}

void LABFeatureMap::ComputeFeatureMap() {
  int32_t width = width_ - rect_width_ * num_rect_;			//LAB:3*3 rect  rect:3*3
  int32_t height = height_ - rect_height_ * num_rect_;
  int32_t offset = width_ * rect_height_;
  uint8_t* feat_map = feat_map_.data();

#pragma omp parallel num_threads(SEETA_NUM_THREADS)
  {
#pragma omp for nowait
    for (int32_t r = 0; r <= height; r++) {
      for (int32_t c = 0; c <= width; c++) {
        uint8_t* dest = feat_map + r * width_ + c;
        *dest = 0;

        int32_t white_rect_sum = rect_sum_[(r + rect_height_) * width_ + c + rect_width_];
        int32_t black_rect_idx = r * width_ + c;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x80 : 0x0);
        black_rect_idx += rect_width_;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x40 : 0x0);
        black_rect_idx += rect_width_;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x20 : 0x0);
        black_rect_idx += offset;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x08 : 0x0);
        black_rect_idx += offset;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x01 : 0x0);
        black_rect_idx -= rect_width_;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x02 : 0x0);
        black_rect_idx -= rect_width_;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x04 : 0x0);
        black_rect_idx -= offset;
        *dest |= (white_rect_sum >= rect_sum_[black_rect_idx] ? 0x10 : 0x0);
      }
    }
  }
}

}  // namespace fd
}  // namespace seeta
