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

#ifndef _NEXURALNET_DNN_LAYERS_FULLY_CONNECTED_LAYER
#define _NEXURALNET_DNN_LAYERS_FULLY_CONNECTED_LAYER

namespace nexural {
	class FullyConnectedLayer : public ComputationalBaseLayer {
	public:
		FullyConnectedLayer(const LayerParams &layerParams) : ComputationalBaseLayer(layerParams) {
			_numOutputNeurons = parser::ParseLong(_layerParams, "neurons");
			_hasWeights = true;
			_hasBias = true;
		}

		~FullyConnectedLayer() {

		}

		virtual void Setup(const LayerShape& prevLayerShape) {
			_inputShape.Resize(prevLayerShape);
			_outputShape.Resize(_inputShape.GetNumSamples(), 1, 1, _numOutputNeurons);
			_outputData.Resize(_outputShape);
			_weights.Resize(1, 1, _numOutputNeurons, (_inputShape.GetK() * _inputShape.GetNR() * _inputShape.GetNC()));
			_biases.Resize(1, 1, 1, _numOutputNeurons);
			_weights.FillRandom();
			_biases.FillRandom();
		}

		virtual void FeedForward(const Tensor& inputData) {
			_internalInputData.ShareTensor(inputData);
			for (long numSamples = 0; numSamples < inputData.GetNumSamples(); numSamples++)
			{
				for (long n = 0; n < _numOutputNeurons; n++)
				{
					float neuronCalculatedValue = 0;
					for (long k = 0; k < inputData.GetK(); k++)
					{
						for (long nr = 0; nr < inputData.GetNR(); nr++)
						{
							for (long nc = 0; nc < inputData.GetNC(); nc++)
							{
								float inputValue = inputData[(((numSamples * inputData.GetK()) + k) * inputData.GetNR() + nr) * inputData.GetNC() + nc];
								float testInputValue = _internalInputData[(((numSamples * _internalInputData.GetK()) + k) * _internalInputData.GetNR() + nr) * _internalInputData.GetNC() + nc];
								float weightValue = _weights[(((1 * 1) + 0) * _weights.GetNR() + n) * _weights.GetNC() + (k * nr * nc)];
								neuronCalculatedValue += inputValue * weightValue;
							}
						}
					}
					_outputData[numSamples * inputData.GetNC() + n] = neuronCalculatedValue + _biases[n];
				}
			}
		}

		virtual void SetupLayerForTraining() {
			_layerErrors.Resize(_inputShape);
			_dWeights.Resize(_weights.GetShape());
			_dBiases.Resize(_biases.GetShape());
		}

		virtual void BackPropagate(const Tensor& prevLayerErrors) {
			_dWeights.Fill(0.0);
			_dBiases.Fill(0.0);

			// Calculate gradient wrt. weights ( _internalInputData * prevLayerErrors)
			// Calculate gradient wrt. biases ( 1 * prevLayerErrors)
			for (long numSamples = 0; numSamples < _dWeights.GetNumSamples(); numSamples++)
			{
				for (long n = 0; n < _numOutputNeurons; n++)
				{
					float error = prevLayerErrors[numSamples * prevLayerErrors.GetNC() + n];
					if (_hasBias) {
						_dBiases[numSamples * prevLayerErrors.GetNC() + n] += error;
					}

					for (long k = 0; k < _dWeights.GetK(); k++)
					{
						for (long nr = 0; nr < _dWeights.GetNR(); nr++)
						{
							for (long nc = 0; nc < _dWeights.GetNC(); nc++)
							{
								float value = _internalInputData[(((numSamples * _internalInputData.GetK()) + k) * _internalInputData.GetNR() + nr) * _internalInputData.GetNC() + nc];
								_dWeights[(((numSamples * _dWeights.GetK()) + k) * _dWeights.GetNR() + nr) * _dWeights.GetNC() + nc] += value * error;
							}
						}
					}
				}
			}

			// Calculate gradient wrt. input (_weights * prevLayerErrors)
			for (long numSamples = 0; numSamples < _dWeights.GetNumSamples(); numSamples++)
			{
				for (long n = 0; n < _numOutputNeurons; n++)
				{
					float error = prevLayerErrors[numSamples * prevLayerErrors.GetNC() + n];
					for (long k = 0; k < _dWeights.GetK(); k++)
					{
						for (long nr = 0; nr < _dWeights.GetNR(); nr++)
						{
							for (long nc = 0; nc < _dWeights.GetNC(); nc++)
							{
								float value = _weights[(((_weights.GetK()) + k) * _weights.GetNR() + nr) * _weights.GetNC() + nc];
								_layerErrors[(((numSamples * _layerErrors.GetK()) + k) * _layerErrors.GetNR() + nr) * _layerErrors.GetNC() + nc] = value * error;
							}
						}
					}
				}
			}
		}

	private:
		Tensor _internalInputData;
		long _numOutputNeurons;
	};
}
#endif
