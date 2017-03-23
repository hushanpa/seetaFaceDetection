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

#include "classifier/lab_boosted_classifier.h"

#include <memory>
#include <string>

namespace seeta {
namespace fd {

void LABBaseClassifier::SetWeights(const float* weights, int32_t num_bin) {
  weights_.resize(num_bin + 1);
  num_bin_ = num_bin;
  std::copy(weights, weights + num_bin_ + 1, weights_.begin());
}

bool LABBoostedClassifier::Classify(float* score, float* outputs) {
  bool isPos = true;
  float s = 0.0f;
  /*
  (9,9) (20,17) (31,28) (15,27) (23,10) (16,2) (0,27) (11,16) (20,7) (28,21) (4,22) (23,17) (7,12) (0,0) (19,29) 
  (12,7) (10,26) (31,2) (26,31) (0,9) (17,23) (17,9) (24,5) (6,31) (24,13) (20,26) (10,3) (13,19) (0,17) (31,15) 
  (18,2) (8,19) (3,4) (15,7) (26,25) (31,8) (19,14) (11,28) (31,31) (15,21) (13,11) (26,0) (15,24) (1,25) (10,8) 
  (19,19) (22,7) (15,0) (4,16) (23,21) (31,22) (8,0) (14,17) (14,29) (0,31) (8,11) (6,24) (25,12) (0,14) (17,5) 
  (22,31) (18,11) (17,27) (23,0) (31,0) (0,4) (14,9) (28,5) (25,23) (11,20) (12,26) (6,8) (8,4) (13,13) (18,8) 
  (23,27) (19,22) (3,18) (29,27) (14,7) (6,29) (12,0) (18,17) (31,11) (8,15) (21,10) (20,1) (5,1) (16,29) (28,14) 
  (0,20) (19,4) (14,23) (31,17) (8,21) (11,9) (24,15) (13,16) (28,30) (13,3) (3,28) (16,11) (25,6) (13,28) (27,18) 
  (20,8) (19,25) (17,19) (1,0) (25,29) (3,12) (21,21) (24,11) (25,2) (16,26) (11,7) (2,31) (11,14) (30,20) (7,9) 
  (18,15) (18,0) (0,8) (20,27) (29,3) (12,18) (24,24) (31,30) (9,23) (0,23) (18,6) (6,16) (10,1) (11,11) (7,26) 
  (23,8) (29,9) (22,3) (9,29) (31,25) (7,6) (22,14) (12,5) (20,18) (19,30) (19,13) (17,21) (4,31) (9,18) (22,23)
  
  */
  for (size_t i = 0; isPos && i < base_classifiers_.size();) {		//150 features
    for (int32_t j = 0; j < kFeatGroupSize; j++, i++) {			//10 features in a group to detect whether isPos is true or false. If false,then breakout. This speeds up detection.
      uint8_t featVal = feat_map_->GetFeatureVal(feat_[i].x, feat_[i].y);
      s += base_classifiers_[i]->weights(featVal);
    }
    if (s < base_classifiers_[i - 1]->threshold())
      isPos = false;
  }
  isPos = isPos && ((!use_std_dev_) || feat_map_->GetStdDev() > kStdDevThresh);		//don't understand the fuction GetStdDev() here

  if (score != nullptr)
    *score = s;
  if (outputs != nullptr)
    *outputs = s;

  return isPos;
}

void LABBoostedClassifier::AddFeature(int32_t x, int32_t y) {
  LABFeature feat;
  feat.x = x;
  feat.y = y;
  feat_.push_back(feat);
}

void LABBoostedClassifier::AddBaseClassifier(const float* weights,
    int32_t num_bin, float thresh) {
  std::shared_ptr<LABBaseClassifier> classifier(new LABBaseClassifier());
  classifier->SetWeights(weights, num_bin);
  classifier->SetThreshold(thresh);
  base_classifiers_.push_back(classifier);
}

}  // namespace fd
}  // namespace seeta
