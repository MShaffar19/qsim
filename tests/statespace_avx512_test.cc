// Copyright 2019 Google LLC. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "statespace_testfixture.h"

#include "gtest/gtest.h"

#ifdef __AVX512F__

#ifdef _OPENMP
#include "../lib/parfor.h"
#endif
#include "../lib/seqfor.h"
#include "../lib/simulator_avx512.h"
#include "../lib/statespace_avx512.h"

namespace qsim {

template <class T>
class StateSpaceAVX512Test : public testing::Test {};

using ::testing::Types;
#ifdef _OPENMP
typedef Types<ParallelFor, SequentialFor> for_impl;
#else
typedef Types<SequentialFor> for_impl;
#endif

TYPED_TEST_SUITE(StateSpaceAVX512Test, for_impl);

TYPED_TEST(StateSpaceAVX512Test, Add) {
  TestAdd<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, NormSmall) {
  TestNormSmall<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, NormAndInnerProductSmall) {
  TestNormAndInnerProductSmall<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, NormAndInnerProduct) {
  TestNormAndInnerProduct<SimulatorAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, SamplingSmall) {
  TestSamplingSmall<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, SamplingCrossEntropyDifference) {
  TestSamplingCrossEntropyDifference<SimulatorAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, Ordering) {
  TestOrdering<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, MeasurementSmall) {
  TestMeasurementSmall<StateSpaceAVX512<TypeParam>, TypeParam>();
}

TYPED_TEST(StateSpaceAVX512Test, MeasurementLarge) {
  TestMeasurementLarge<SimulatorAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, Collapse) {
  TestCollapse<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, InvalidStateSize) {
  TestInvalidStateSize<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, BulkSetAmpl) {
  TestBulkSetAmplitude<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, BulkSetAmplExclude) {
  TestBulkSetAmplitudeExclusion<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, BulkSetAmplDefault) {
  TestBulkSetAmplitudeDefault<StateSpaceAVX512<TypeParam>>();
}

TYPED_TEST(StateSpaceAVX512Test, ThreadThrashing) {
  TestThreadThrashing<StateSpaceAVX512<TypeParam>>();
}

}  // namespace qsim

#endif  // __AVX512F__

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
