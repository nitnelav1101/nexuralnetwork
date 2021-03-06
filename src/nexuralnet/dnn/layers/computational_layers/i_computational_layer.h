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

#include <string>
#include "../../data_types/general_data_types.h"
#include "../../utility/serializer/serializer.h"

#ifndef NEXURALNET_DNN_I_COMPUTATIONAL_LAYER
#define NEXURALNET_DNN_I_COMPUTATIONAL_LAYER

namespace nexural {
	class IComputationalLayer {
	public:
		virtual ~IComputationalLayer() { }
		virtual void Setup(const LayerShape& prevLayerShape, const size_t layerIndex) = 0;
		virtual void BackPropagate(const Tensor& prevLayerErrors) = 0;
		virtual Tensor* GetLayerWeights() = 0;
		virtual Tensor* GetLayerDWeights() = 0; 
		virtual Tensor* GetLayerBiases() = 0;
		virtual Tensor* GetLayerDBiases() = 0;
		virtual bool HasWeights() = 0;
		virtual bool HasBiases() = 0;
		virtual std::string GetLayerID() const = 0;
		virtual void Serialize(Serializer& serializer) = 0;
		virtual void Deserialize(Serializer& serializer) = 0;
		virtual void SetWeights(const std::vector<float_n>& values) = 0;
		virtual void SetBiases(const std::vector<float_n>& values) = 0;
	};
}
#endif
