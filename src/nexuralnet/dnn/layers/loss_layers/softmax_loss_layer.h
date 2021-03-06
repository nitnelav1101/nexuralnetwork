/* Copyright (C) 2017 Alexandru-Valentin Musat (contact@nexuralsoftware.com)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "loss_base_layer.h"
#include "multi_class_classification_result.h"

#ifndef NEXURALNET_DNN_LAYERS_SOFTMAX_LOSS_LAYER
#define NEXURALNET_DNN_LAYERS_SOFTMAX_LOSS_LAYER

namespace nexural {
	class SoftmaxLossLayer : public LossBaseLayer {
	public:
		SoftmaxLossLayer(const Params& layerParams);
		~SoftmaxLossLayer();

		virtual void Setup(const LayerShape& prevLayerShape);
		virtual void FeedForward(const Tensor& inputData, const NetworkState = NetworkState::RUN);
		virtual void SetupLayerForTraining();

		virtual void CalculateError(const Tensor& targetData);
		virtual void CalculateTrainingMetrics(const Tensor& targetData, Tensor& confusionMatrix);
		virtual void SetResult();
		virtual DNNBaseResult* GetResult();
		virtual const std::string GetResultJSON();

	private:
		void Softmax(const Tensor& inputData, Tensor& outputData);

	private:
		MultiClassClassificationResult _netResult;
	};
}
#endif
