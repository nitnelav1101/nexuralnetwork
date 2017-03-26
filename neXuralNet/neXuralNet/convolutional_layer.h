/* Copyright (C) 2016-2017 Alexandru-Valentin Musat (alexandruvalentinmusat@gmail.com)

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

#include "computational_base_layer.h"
#include "data_parser.h"

#ifndef _NEXURALNET_DNN_LAYERS_CONVOLUTIONAL_LAYER
#define _NEXURALNET_DNN_LAYERS_CONVOLUTIONAL_LAYER

namespace nexural {
	class ConvolutionalLayer : public ComputationalBaseLayer {
	public:
		ConvolutionalLayer(const LayerParams &layerParams) : ComputationalBaseLayer(layerParams) {
			_num_of_filters = parser::ParseLong(_layerParams, "num_of_filters");
			_kernel_width = parser::ParseLong(_layerParams, "kernel_width");
			_kernel_height = parser::ParseLong(_layerParams, "kernel_height");
			_padding_width = parser::ParseLong(_layerParams, "padding_width");
			_padding_height = parser::ParseLong(_layerParams, "padding_height");
			_stride_width = parser::ParseLong(_layerParams, "stride_width");
			_stride_height = parser::ParseLong(_layerParams, "stride_height");
			_hasWeights = true;
			_hasBiases = true;
		}

		~ConvolutionalLayer() {

		}

		virtual void Setup(const LayerShape& prevLayerShape, const int layerIndex) {
			_inputShape.Resize(prevLayerShape);
			_outputShape.Resize(_inputShape.GetNumSamples(), _num_of_filters, 
				(((_inputShape.GetNR() - _kernel_height - (2 * _padding_height)) / _stride_height)  + 1), 
				(((_inputShape.GetNC() - _kernel_width - (2 * _padding_width)) / _stride_width) + 1));
			_outputData.Resize(_outputShape);
			_weights.Resize(_num_of_filters, _inputShape.GetK(), _kernel_height, _kernel_width);
			_weights.FillRandom();
			if (_hasBiases) {
				_biases.Resize(1, 1, 1, _num_of_filters);
			}
			_layerID = "convolutional_layer" + std::to_string(layerIndex);
		}

		virtual void FeedForward(const Tensor& inputData) {

		}

		virtual void SetupLayerForTraining() {
			_layerErrors.Resize(_inputShape);
		}

		virtual void BackPropagate(const Tensor& prevLayerErrors) {

		}

		virtual void Serialize(std::string& data) {
			DataSerializer::AddParentNode(_layerID, data);
			DataSerializer::SerializeTensor(_weights, _layerID, "weights", data);
			DataSerializer::SerializeTensor(_biases, _layerID, "biases", data);
		}

		virtual void Deserialize(const std::string& data) {
			DataSerializer::DeserializeTensor(_weights, _layerID, "weights", data);
			DataSerializer::DeserializeTensor(_biases, _layerID, "biases", data);
		}

	private:
		long _num_of_filters;
		long _kernel_width;
		long _kernel_height;
		long _padding_width;
		long _padding_height;
		long _stride_width;
		long _stride_height;
	};
}
#endif
