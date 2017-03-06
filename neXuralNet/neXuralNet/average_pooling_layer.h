// Copyright (C) 2016 Alexandru-Valentin Musat (alexandruvalentinmusat@gmail.com)

#ifndef _NEXURALNET_DNN_LAYERS_AVERAGE_POOLING_LAYER
#define _NEXURALNET_DNN_LAYERS_AVERAGE_POOLING_LAYER

#include "data_types.h"
#include "computational_base_layer.h"
#include "data_parser.h"
#include <iostream>

namespace nexural {

	class AveragePoolingLayer : public ComputationalBaseLayer {
	public:
		AveragePoolingLayer(LayerParams &layerParams) : ComputationalBaseLayer(layerParams) {
			_kernel_width = parser::ParseLong(_layerParams, "kernel_width");
			_kernel_height = parser::ParseLong(_layerParams, "kernel_height");
		}

		~AveragePoolingLayer() {
			
		}
		
		virtual void Setup(LayerShape& prevLayerShape) {
			_outputShape.Resize(prevLayerShape.GetNumSamples(), prevLayerShape.GetK(),
				(prevLayerShape.GetNR() / _kernel_height + (prevLayerShape.GetNR() % _kernel_height == 0 ? 0 : 1)),
				(prevLayerShape.GetNC() / _kernel_width + (prevLayerShape.GetNC() % _kernel_width == 0 ? 0 : 1)));

			_outputData.Resize(_outputShape);
		}
		
		virtual void FeedForward(const Tensor& inputData) {
			
			for (long numSamples = 0; numSamples < inputData.GetNumSamples(); numSamples++)
			{
				for (long k = 0; k < inputData.GetK(); k++)
				{
					long outNR = 0;
					for (long nr = 0; nr < inputData.GetNR(); nr += _kernel_height)
					{
						long outNC = 0;
						for (long nc = 0; nc < inputData.GetNC(); nc += _kernel_width)
						{
							long khLimit = _kernel_height - (nr == (inputData.GetNR() - (inputData.GetNR() % _kernel_height)) ? _kernel_height - inputData.GetNR() % _kernel_height : 0);
							long kwLimit = _kernel_width - (nc == (inputData.GetNC() - (inputData.GetNC() % _kernel_width)) ? _kernel_width - inputData.GetNC() % _kernel_width : 0);
							
							float sum = 0;

							for (long kh = 0; kh < khLimit; kh++)
							{
								for (long kw = 0; kw < kwLimit; kw++)
								{
									float value = inputData[(((numSamples * inputData.GetK()) + k) * inputData.GetNR() + (nr + kh)) * inputData.GetNC() + (nc + kw)];
									sum += value;
								}
							}
							_outputData[(((numSamples * _outputData.GetK()) + k) * _outputData.GetNR() + outNR) * _outputData.GetNC() + outNC] = sum / (khLimit * kwLimit);
							outNC++;
						}
						outNR++;
					}
				}
			}

		}

		virtual void BackPropagate(const Tensor& layerErrors) {
		
		}

		virtual void Update() {

		}


	private:
		long _kernel_width;
		long _kernel_height;

	};

}
#endif
