// Copyright (C) 2016 Alexandru-Valentin Musat (alexandruvalentinmusat@gmail.com)

#include <cstdio>
#include <vector>
#include <memory>
#include <string>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include "computational_base_layer.h"
#include "average_pooling_layer.h"
//#include "loss_base_layer.h"

#include "input_layer.h"

#ifndef MAVNET_DNN_NETWORK_NETWORK
#define MAVNET_DNN_NETWORK_NETWORK

namespace nexural {

	class Network {
		typedef std::vector<ComputationalBaseLayerPtr> ComputationalNetworkLayers;
		//typedef LossBaseLayerPtr LossNetworkLayer;

	public:
		Network(const std::string jsonFilePath) {
			NetworkReader netParser(jsonFilePath);
			netParser.loadNetwork(*this);
			for (int i = 0; i < this->_computationalNetworkLyers.size(); i++) {
				_computationalNetworkLyers[i]->Setup();
			}
			//_lossNetworkLayer.reset(new LossBaseLayer());
		}

		~Network() {

		}

		void SetInputSettings() {

		}

		//void SetLossLayer(LossBaseLayerPtr layer) {
		//	_lossNetworkLayer = layer;
		//}

		void AddComputationalLayer(ComputationalBaseLayerPtr layer) {
			_computationalNetworkLyers.push_back(layer);
		}

		void Run(const cv::Mat& inputData) {
			_inputNetworkLayer.LoadImage(inputData);
			Tensor *internalNetData = _inputNetworkLayer.GetOutput();
			for (int i = 0; i < this->_computationalNetworkLyers.size(); i++) {
				_computationalNetworkLyers[i]->FeedForward(*internalNetData);
				internalNetData = _computationalNetworkLyers[i]->GetOutput();	
			}

			for (int i = 0; i < internalNetData->Size(); i++) {
				std::cout << (*(&(*internalNetData)))[i] << std::endl;
			}

			/*
			_lossNetworkLayer->FeedForward(internalNetData);
			Tensor result = _lossNetworkLayer->GetOutput();
			*/
		}

		void Train() {

		}

	private:

		class NetworkReader {

		public:
			NetworkReader(const std::string jsonFilePath) {
				_fp = fopen(jsonFilePath.c_str(), "rb");
				if (!_fp) {
					throw std::runtime_error("Cannot load the JSON!");
				}
				char readBuffer[65536];
				rapidjson::FileReadStream is(_fp, readBuffer, sizeof(readBuffer));
				_document.ParseStream(is);
			}

			~NetworkReader() {
				if (_fp) {
					fclose(_fp);
				}
			}

			void loadNetwork(Network &net) {
				if (!_document.HasMember("NetworkLayers")) { 
					throw std::runtime_error("NetworkLayers member is missing from the JSON file!");
				}

				const rapidjson::Value& netLayers = _document["NetworkLayers"].GetArray();
				for (rapidjson::SizeType i = 0; i < netLayers.Size(); i++)
				{
					const rapidjson::Value& currentLayer = netLayers[i];

					if (!currentLayer.HasMember("type")) {
						throw std::runtime_error("type member is missing from the JSON file!");
					}
					if (!currentLayer.HasMember("params")) {
						throw std::runtime_error("params member is missing from the JSON file!");
					}

					LayerParams layerParams;
					std::string type_member = currentLayer["type"].GetString();
					const rapidjson::Value& params_member = currentLayer["params"];

					for (rapidjson::Value::ConstMemberIterator iter = params_member.MemberBegin(); iter != params_member.MemberEnd(); ++iter) {
						layerParams.insert(std::pair<std::string, std::string>(iter->name.GetString(), iter->value.GetString()));
					}

					if (type_member == "input") {
						
					} else if (type_member == "convolutional") {
						//net.add_computational_layer(ComputationalBaseLayerPtr(new nexural::ConvolutionalLayer(layerParams)));
					} else if (type_member == "average_pooling") {
						net.AddComputationalLayer(ComputationalBaseLayerPtr(new nexural::AveragePoolingLayer(layerParams)));
					} else if (type_member == "full_connected") {

					}
				}
			}

		private:
			FILE* _fp;
			rapidjson::Document _document;
		};

	private:
		ComputationalNetworkLayers _computationalNetworkLyers;
		//LossNetworkLayer _lossNetworkLayer;
		InputOpenCVBGRImage _inputNetworkLayer;
	};
}
#endif
