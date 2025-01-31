#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"


std::string GetPaddingAttrString() { return "padding: {'SAME', 'VALID'}"; }

std::string GetPaddingAttrStringWithExplicit() {
  return "padding: {'SAME', 'VALID', 'EXPLICIT'}";
}

std::string GetExplicitPaddingsAttrString() {
  return "explicit_paddings: list(int) = []";
}

std::string GetConvnetDataFormatAttrString() {
  return "data_format: { 'NHWC', 'NCHW' } = 'NHWC' ";
}


REGISTER_OP("SecureSigmoidCrossEntropy")
    .Input("logits: string")
    .Input("labels: string")
    .Output("loss: string")
    .Doc(R"doc(
SecureSigmoidCrossEntropyOp
)doc");

REGISTER_OP("SecureSigmoid")
  .Input("x: string")
  .Output("y: string")
  // .SetShapeFn(shape_inference::UnchangedShape)
  .Doc(R"doc(
SecureSigmoidOp
)doc");

REGISTER_OP("SecureRelu")
  .Input("x: string")
  .Output("y: string")
  // .SetShapeFn(shape_inference::UnchangedShape)
  .Doc(R"doc(
SecureReluOp
)doc");

REGISTER_OP("SecureReluPrime")
  .Input("x: string")
  .Output("y: string")
  // .SetShapeFn(shape_inference::UnchangedShape)
  .Doc(R"doc(
SecureReluPrimeOp
)doc");

REGISTER_OP("SecureConv2D")
    .Input("input: string")
    .Input("filter: string")
    .Output("output: string")
    .Attr("strides: list(int)")
    .Attr("use_cudnn_on_gpu: bool = true")
    .Attr(GetPaddingAttrStringWithExplicit())
    .Attr(GetExplicitPaddingsAttrString())
    .Attr(GetConvnetDataFormatAttrString())
    .Attr("dilations: list(int) = [1, 1, 1, 1]")
    // .SetShapeFn(::tensorflow::shape_inference::Conv2DShapeWithExplicitPadding)
    .Doc(R"doc(
SecureConv2DOp
)doc");

REGISTER_OP("SecureBiasAdd")
    .Input("value: string")
    .Input("bias: string")
    .Attr(GetConvnetDataFormatAttrString())
    .Output("output: string")
    // .SetShapeFn(::tensorflow::shape_inference::BiasAddShape)
    .Doc(R"doc(
SecureBiasAddOp
)doc");

REGISTER_OP("SecureL2Loss")
    .Input("t: string")
    .Output("output: string")
    // .SetShapeFn(::tensorflow::shape_inference::ScalarShape)
    .Doc(R"doc(
SecureL2LossOp
)doc");

REGISTER_OP("SecureFusedBatchNorm")
    .Input("x: string")
    .Input("scale: string")
    .Input("offset: string")
    .Input("mean: string")
    .Input("variance: string")
    .Output("y: string")
    .Output("batch_mean: string")
    .Output("batch_variance: string")
    .Output("reserve_space_1: string")
    .Output("reserve_space_2: string")
    .Attr("epsilon: float = 0.0001")
    .Attr(GetConvnetDataFormatAttrString())
    .Attr("is_training: bool = true")
    // .SetShapeFn(::tensorflow::shape_inference::FusedBatchNormShape)
    .Doc(R"doc(
SecureFusedBatchNormOp
)doc");

REGISTER_OP("SecureAvgPool")
    .Input("value: string")
    .Output("output: string")
    .Attr("ksize: list(int) >= 4")
    .Attr("strides: list(int) >= 4")
    .Attr(GetPaddingAttrString())
    .Attr(GetConvnetDataFormatAttrString())
    // .SetShapeFn(::tensorflow::shape_inference::AvgPoolShape)
    .Doc(R"doc(
SecureAvgPoolOp
)doc");

REGISTER_OP("SecureMaxPool")
    .Input("input: string")
    .Output("output: string")
    .Attr("ksize: list(int) >= 4")
    .Attr("strides: list(int) >= 4")
    .Attr(GetPaddingAttrString())
    .Attr("data_format: {'NHWC', 'NCHW', 'NCHW_VECT_C'} = 'NHWC'")
    // .SetShapeFn(::tensorflow::shape_inference::MaxPoolShape)
    .Doc(R"doc(
SecureMaxPoolOp
)doc");

REGISTER_OP("SecureSoftmax")
    .Input("logits: string")
    .Output("softmax: string")
    // .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
    //   return ::tensorflow::shape_inference::UnchangedShapeWithRankAtLeast(c, 1);
    // })
    .Doc(R"doc(
SecureSoftmaxOp
)doc");