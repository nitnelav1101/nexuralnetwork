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

#include "i_solver.h"
#include "../data_types/general_data_types.h"
#include "../utility/params_parser.h"

#ifndef NEXURALNET_DNN_BASE_SOLVER
#define NEXURALNET_DNN_BASE_SOLVER

namespace nexural {
	class BaseSolver : public ISolver {
	public:
		BaseSolver();
		BaseSolver(Params &solverParams);
		virtual ~BaseSolver();
		virtual void UpdateLearningRate(const float_n scaleFactor);
		virtual float_n GetLearningRate() const;

	protected:
		float_n _learningRate;
		float_n _weightDecay;
	};
	typedef std::shared_ptr<BaseSolver> BaseSolverPtr;
}
#endif 
