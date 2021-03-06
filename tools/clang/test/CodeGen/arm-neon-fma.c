// RUN: %clang_cc1 -triple thumbv7-none-linux-gnueabihf \
// RUN:   -target-abi aapcs \
// RUN:   -target-cpu cortex-a7 \
// RUN:   -mfloat-abi hard \
// RUN:   -ffreestanding \
// RUN:   -emit-llvm -o - %s | opt -S -mem2reg | FileCheck %s

#include <arm_neon.h>

// CHECK-LABEL: define <2 x float> @test_fma_order(<2 x float> %accum, <2 x float> %lhs, <2 x float> %rhs) #0 {
// CHECK:   [[TMP0:%.*]] = bitcast <2 x float> %accum to <8 x i8>
// CHECK:   [[TMP1:%.*]] = bitcast <2 x float> %lhs to <8 x i8>
// CHECK:   [[TMP2:%.*]] = bitcast <2 x float> %rhs to <8 x i8>
// CHECK:   [[TMP3:%.*]] = bitcast <8 x i8> [[TMP0]] to <2 x float>
// CHECK:   [[TMP4:%.*]] = bitcast <8 x i8> [[TMP1]] to <2 x float>
// CHECK:   [[TMP5:%.*]] = bitcast <8 x i8> [[TMP2]] to <2 x float>
// CHECK:   [[TMP6:%.*]] = call <2 x float> @llvm.fma.v2f32(<2 x float> [[TMP4]], <2 x float> [[TMP5]], <2 x float> [[TMP3]]) #2
// CHECK:   ret <2 x float> [[TMP6]]
float32x2_t test_fma_order(float32x2_t accum, float32x2_t lhs, float32x2_t rhs) {
  return vfma_f32(accum, lhs, rhs);
}

// CHECK-LABEL: define <4 x float> @test_fmaq_order(<4 x float> %accum, <4 x float> %lhs, <4 x float> %rhs) #0 {
// CHECK:   [[TMP0:%.*]] = bitcast <4 x float> %accum to <16 x i8>
// CHECK:   [[TMP1:%.*]] = bitcast <4 x float> %lhs to <16 x i8>
// CHECK:   [[TMP2:%.*]] = bitcast <4 x float> %rhs to <16 x i8>
// CHECK:   [[TMP3:%.*]] = bitcast <16 x i8> [[TMP0]] to <4 x float>
// CHECK:   [[TMP4:%.*]] = bitcast <16 x i8> [[TMP1]] to <4 x float>
// CHECK:   [[TMP5:%.*]] = bitcast <16 x i8> [[TMP2]] to <4 x float>
// CHECK:   [[TMP6:%.*]] = call <4 x float> @llvm.fma.v4f32(<4 x float> [[TMP4]], <4 x float> [[TMP5]], <4 x float> [[TMP3]]) #2
// CHECK:   ret <4 x float> [[TMP6]]
float32x4_t test_fmaq_order(float32x4_t accum, float32x4_t lhs, float32x4_t rhs) {
  return vfmaq_f32(accum, lhs, rhs);
}
