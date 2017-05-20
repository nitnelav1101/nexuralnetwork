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

#include "../include/nexuralnet/dnn.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

#ifndef _NEXURALNET_TOOLS_CONVERTER_H
#define _NEXURALNET_TOOLS_CONVERTER_H

namespace nexural {
	PYBIND11_PLUGIN(nexuralNet) {
		py::module m("nexuralNet", "neXt neural network");

		py::class_<Network>(m, "Network")
			.def(py::init<const std::string &>())
			.def("deserialize", &Network::Deserialize)
			.def("run", &Network::Run)
			.def("getResult", &Network::GetResult);

		return m.ptr();
	}
}
#endif